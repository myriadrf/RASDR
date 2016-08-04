'''
Script to emulate a Radio Sky Spectrograph client application to verify RSS
output.  The program is used to diagnose and analyze the streaming spectrum.
'''
import os
import sys
import datetime
import logging
import socket
import numpy as np

DEF_VERSION = '0.2.3.1'     # x.y.z.* to match RASDRproc version

def rss(s,opts):
    '''Interpret the stream using the standard RSS format defined at
    http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html
    @param s        - socket just successfully connected to the RSS server
    @param opts     - options object from OptionParser
    '''
    # receive connection string and some amount of spectral data
    p = s.recv(1024)
    if len(p) < 1:
        return
    d = p.rpartition('|')
    connect = d[0].split('|')

    # parse key/value pairs in connection string
    conf = {}
    for kw in connect:
        kv = kw.split(' ')
        conf[kv[0]] = int(kv[1])

    # ensure canonical connection string
    assert(conf.has_key('F'))
    assert(conf.has_key('S'))
    assert(conf.has_key('O'))
    assert(conf.has_key('C'))

    # display key/values and stop if thats all they want
    msg  = 'CenterFrequencyHertz=%d\n'%conf['F']
    msg += 'BandwidthHertz=%d\n'%conf['S']
    msg += 'OffsetHertz=%d\n'%conf['O']
    msg += 'NumberOfChannels=%d\n'%conf['C']
    logger.info(msg)
    if opts.info:
        return

    # determine parameters that affect the size of spectral buffers
    channels = conf['C']
    dt       = np.dtype(opts.dtype)
    assert( dt.itemsize == 2 )          # RSS requires 2-byte integers
    scanlen  = (channels+1)*dt.itemsize # two-byte integers plus one 0xFEFE scan marker

    # determine an EOS marker according to the dtype we selected
    data = '\xFE\xFE'
    eos_marker = np.frombuffer(data,dtype=opts.dtype)

    # build out complete scans from this first buffer
    data = d[2].strip()
    extra = scanlen - (len(data) % scanlen)
    if extra > 0:
        data += s.recv(extra)
    b = np.frombuffer(data,dtype=opts.dtype)
    psd = np.reshape(b, (-1,channels+1))

    # interpret the scans until stopped
    stats = {}
    stats['n']    = 0
    stats['min']  = 4096
    stats['max']  = 0
    stats['mean'] = 0.0
    stats['var']  = 0.0

    hdr = 'N,MIN,MAX,MEAN,VAR'
    if opts.statistics is not None:
        opts['csv'].write(hdr+os.linesep)
    sys.stdout.write(hdr+os.linesep)

    while psd.shape[0] > 0 and psd.shape[1] == channels+1:
        assert(psd[0][channels] == eos_marker)  # End of scan marker
        scan = psd[0][0:channels]
        stats['n']   += 1
        stats['min']  = scan.min() if scan.min() < stats['min'] else stats['min']
        stats['max']  = scan.max() if scan.max() > stats['max'] else stats['max']
        # http://stackoverflow.com/questions/19391149/numpy-mean-and-variance-from-single-function
        stats['mean'] = scan.mean()
        c = scan-stats['mean']
        stats['var']  = np.dot(c,c)/scan.size

        # display stats
        msg = '%d,%.3f,%.3f,%.3f,%.3f' % \
            (stats['n'], stats['min'], stats['max'], stats['mean'], stats['var'])
        if opts.statistics is not None:
            opts['csv'].write(msg+os.linesep)

        # http://stackoverflow.com/questions/517127/how-do-i-write-output-in-same-place-on-the-console
        sys.stdout.write(msg+'      \r')
        sys.stdout.flush()

        if psd.shape[0] > 1:
            # this is the initial case where we read in several scans
            psd = np.delete(psd, (0), axis=0)
        else:
            # this is the typical case where we read in the next scan from the network
            b = np.frombuffer(s.recv(scanlen),dtype=opts.dtype)
            psd = np.reshape(b, (-1,channels+1))

def rssx(s,opts):
    '''Interpret the stream using the extended RSS format
    @param s        - socket just successfully connected to the RSS server
    @param opts     - options object from OptionParser
    '''
    raise Exception('Extended RSS interpretation is not implemented')

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('rss-test.py [options]')
    p.set_description(__doc__)
    p.add_option('-a', '--address', dest='ip', type='str', metavar='A', default='localhost',
        help='Specify the server address; default=%default')
    p.add_option('-p', '--port', dest='port', type='int', metavar='N', default=8888,
        help='Specify the port to connect to; default=%default')
    p.add_option('-i', '--info', dest='info', action='store_true', default=False,
        help='Produce information about the connection only; do not receive/parse scans')
    p.add_option('-e', '--extended', dest='extended', action='store_true', default=False,
        help='Interpret the extended RSS format')
    p.add_option('--statistics', dest='statistics', type='str', metavar='PATH', default=None,
        help='Dump statistical information to a file in comma-separated-values format, default=%default')
    p.add_option('-v', '--verbose', dest='verbose', action='store_true', default=False,
        help='Verbose')
    p.add_option('-t', '--dtype', dest='dtype', type='str', metavar='T', default='<i2',
        help='Specify the datatype to interpret the stream as; default=%default')

    opts, args = p.parse_args(sys.argv[1:])

    # logging boilerplate (screen+log file)
    logging.basicConfig(format='%(message)s',level=logging.DEBUG)
    logger = logging.getLogger(__name__)
    x,y,name = sys.argv[0].replace('\\','/').rpartition('/')
    name,x,ext = name.rpartition('.')
    handler = logging.FileHandler(name+'.log')
    logger.setLevel(logging.DEBUG if opts.verbose else logging.INFO)
    logger.info('*** STARTED ***')
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((opts.ip, opts.port))
        if opts.statistics is not None:
            opts['csv'] = open(opts.statistics,'w')
        if opts.extended:
            rssx(s,opts)
        else:
            rss(s,opts)
    except Exception, e:
        logger.error('rss-test', exc_info=True)

    if opts.statistics is not None:
        opts['csv'].close()
