'''
Script to emulate a Radio Sky Spectrograph client application to verify RSS
output.  The program is used to diagnose and analyze the streaming spectrum.
'''
import struct
import os
import sys
import time
import datetime
import logging
import socket
import numpy as np

DEF_VERSION = '0.2.5.0'     # x.y.z.* to match RASDRproc version

UNIX_EPOCH  = 518400    # 00:00 GMT January 6, 1970 
PKT_FMT     = '!dfffII'
PKT_SZ      = struct.calcsize(PKT_FMT)
PKT_DTYPE   = np.dtype( [('timestamp','>f8'),('hz_low','>f4'),('hz_high','>f4'),('hz_step','>f4'),('samples','>u4'),('channels','>u4')] )

def rss(s,opts,csv=None):
    '''Interpret the stream using the standard RSS format defined at
    http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html
    @param s        - socket just successfully connected to the RSS server
    @param opts     - options object from OptionParser
    '''
    # receive connection string and some amount of spectral data
    p  = s.recv(1024)
    ts = time.time()
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
    
    # calculate frequency parameters like rtl-power
    # http://kmkeen.com/rtl-power/
    hz_low  = (conf['F'] - conf['S']/2) + conf['O']
    hz_step = int(float(conf['S']) / float(conf['C']))
    hz_high = hz_low + conf['C'] * hz_step
    hz_hdr = 'Hz low, Hz high, Hz step, samples'
    hz_msg = '%d,%d,%d,' % \
        (hz_low, hz_high, hz_step)
    if not ( abs(hz_high - (hz_low + conf['S'])) < (hz_step/2) ): # CHECK: how good is this?
        sys.stderr.write('conf='+str(conf)+os.linesep)
        sys.stderr.write(hz_hdr+'='+hz_msg+os.linesep)
        sys.stderr.write("not abs(hz_high - (hz_low + conf['S'])) < (hz_step/2)"+os.linesep)
        sys.stderr.write('*** would have asserted and exit ***'+os.linesep+os.linesep)
    # build out complete scans from this first buffer
    data = d[2].strip()
    extra = scanlen - (len(data) % scanlen)
    if extra > 0:
        data += s.recv(extra)
        ts = time.time()
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
    if csv is not None:
        csv.write('TS,'+hdr+os.linesep)
    sys.stdout.write('TS,'+hz_hdr+','+hdr+os.linesep)

    while psd.shape[0] > 0 and psd.shape[1] == channels+1:
        assert(psd[0][channels] == eos_marker)  # End of scan marker
        scan = psd[0][0:channels]
        stats['n']   += 1
        stats['min']  = scan.min() # if scan.min() < stats['min'] else stats['min']
        stats['max']  = scan.max() # if scan.max() > stats['max'] else stats['max']
        # http://stackoverflow.com/questions/19391149/numpy-mean-and-variance-from-single-function
        stats['mean'] = scan.mean()
        c = scan-stats['mean']
        stats['var']  = np.dot(c,c)/scan.size
        
        # compute timestamp
        dt = datetime.datetime.fromtimestamp(ts)

        # display stats
        msg = '%d,%.1f,%.1f,%.1f,%.1f' % \
            (stats['n'], stats['min'], stats['max'], stats['mean'], stats['var'])
        if csv is not None:
            csv.write(dt.isoformat()+','+msg+os.linesep)
        msg = dt.isoformat()+','+hz_msg+','+msg
        if len(msg) > 77:
            msg = msg[0:77]+'*'
        # http://stackoverflow.com/questions/517127/how-do-i-write-output-in-same-place-on-the-console
        sys.stdout.write(msg+' \r')
        sys.stdout.flush()

        if psd.shape[0] > 1:
            # this is the initial case where we read in several scans
            psd = np.delete(psd, (0), axis=0)
        else:
            # this is the typical case where we read in the next scan from the network
            data = s.recv(scanlen)
            ts   = time.time()
            b    = np.frombuffer(data,dtype=opts.dtype)
            psd = np.reshape(b, (-1,channels+1))

def _readall(s,data,scanlen):
    '''read from socket until complete length is obtained or 0 is read indicating EOS'''
    extra = scanlen - (len(data) % scanlen) if len(data)<scanlen else 0
    while extra > 0:
        more = s.recv(extra)
        if len(more)==0:
            return []
        data += more
        extra = scanlen - (len(data) % scanlen) if len(data)<scanlen else 0
    return data
        
def rssx(s,opts,csv=None):
    '''Interpret the stream using the exttended RSS format defined at
    https://github.com/myriadrf/RASDR/issues/16
    @param s        - socket just successfully connected to the RSSx server
    @param opts     - options object from OptionParser
    '''
    # receive connection string
    p  = _readall(s,'',1024)
    ts = time.time()
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
    assert(conf.has_key('CenterFrequencyHertz'))
    assert(conf.has_key('BandwidthHertz'))
    assert(conf.has_key('OffsetHertz'))
    assert(conf.has_key('NumberOfChannels'))

    # display key/values and stop if thats all they want
    msg  = 'CenterFrequencyHertz=%d\n'%conf['CenterFrequencyHertz']
    msg += 'BandwidthHertz=%d\n'%conf['BandwidthHertz']
    msg += 'OffsetHertz=%d\n'%conf['OffsetHertz']
    msg += 'NumberOfChannels=%d\n'%conf['NumberOfChannels']
    if True:    # diagnostic connection message
        # http://stackoverflow.com/questions/13218506/how-to-get-system-timezone-setting-and-pass-it-to-pytz-timezone
        from dateutil.tz import tzlocal
        
        dt = datetime.datetime.fromtimestamp(ts,tzlocal())
        hz_low  = float((conf['CenterFrequencyHertz'] - conf['BandwidthHertz']/2) + conf['OffsetHertz'])
        hz_step = float(conf['BandwidthHertz']) / float(conf['NumberOfChannels'])
        hz_high = hz_low + float(conf['NumberOfChannels']) * hz_step
        msg += 'Connect @%s\n'%dt.isoformat()

        hz_hdr = 'Hz low, Hz high, Hz step='
        hz_msg = '%.0f,%.0f,%.0f' % \
            (hz_low, hz_high, hz_step)
        msg += hz_hdr+hz_msg+'\n'

    logger.info(msg)
    if opts.info:
        return

    # determine parameters that affect the size of spectral buffers
    dtyp = np.dtype(opts.dtype)
    assert( dtyp.itemsize == 4 )        # RSSx requires 4-byte floats

    # interpret the scans until stopped
    stats = {}
    stats['n']    = 0
    stats['min']  = 4096
    stats['max']  = -370
    stats['mean'] = 0.0
    stats['var']  = 0.0

    hdr = 'N,MIN,MAX,MEAN,VAR'
    if csv is not None:
        csv.write('TS,'+hdr+os.linesep)
    sys.stdout.write('TS,'+hdr+os.linesep)

    while True:
        # build out complete scans from hdr/payload
        # http://kmkeen.com/rtl-power/
        hdr = _readall(s,'',PKT_SZ)
        assert(len(hdr)>0)
        ts, hz_low, hz_high, hz_step, samples, channels = struct.unpack(PKT_FMT, hdr)
        hz_hdr = 'Hz low, Hz high, Hz step, samples'
        hz_msg = '%.0f,%.0f,%.0f,%d' % \
            (hz_low, hz_high, hz_step, samples)

        scanlen = (channels)*dtyp.itemsize
        payload = _readall(s,'',scanlen)
        assert(len(payload)>0)
        b = np.frombuffer(payload,dtype=dtyp)
        psd = np.reshape(b, (-1,channels))

        scan = psd[0][0:channels]
        
        #DEBUG
        if opts.dtype=='<u4':
            sys.stdout.write('PACKET '+str(stats['n'])+os.linesep)
            sys.stdout.write(hz_hdr+os.linesep+hz_msg+os.linesep)
            sys.stdout.write(','.join(format(x, '08x') for x in psd[0]))
            sys.stdout.write(os.linesep)

        stats['n']   += 1
        stats['min']  = scan.min() # if scan.min() < stats['min'] else stats['min']
        stats['max']  = scan.max() # if scan.max() > stats['max'] else stats['max']
        # http://stackoverflow.com/questions/19391149/numpy-mean-and-variance-from-single-function
        stats['mean'] = scan.mean()
        c = scan-stats['mean']
        stats['var']  = np.dot(c,c)/scan.size
        
        # compute timestamp
        dt = datetime.datetime.fromtimestamp(ts)

        # display stats
        msg = '%d,%.1f,%.1f,%.1f,%.1f' % \
            (stats['n'], stats['min'], stats['max'], stats['mean'], stats['var'])
        if csv is not None:
            csv.write(dt.isoformat()+','+msg+os.linesep)
        msg = dt.isoformat()+','+msg
        if len(msg) > 77:
            msg = msg[0:77]+'*'
        # http://stackoverflow.com/questions/517127/how-do-i-write-output-in-same-place-on-the-console
        sys.stdout.write(msg+' \r')
        sys.stdout.flush()

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
    p.add_option('-t', '--dtype', dest='dtype', type='str', metavar='T', default=None,
        help='Specify the datatype to interpret the stream as; default=%default')

    opts, args = p.parse_args(sys.argv[1:])

    # logging boilerplate (screen+log file)
    logging.basicConfig(format='%(message)s',level=logging.DEBUG)
    logger = logging.getLogger(__name__)
    x,y,name = sys.argv[0].replace('\\','/').rpartition('/')
    name,x,ext = name.rpartition('.')
    handler = logging.FileHandler(name+'.log')
    formatter = logging.Formatter('%(levelname)s:%(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    logger.setLevel(logging.DEBUG if opts.verbose else logging.INFO)
    logger.info('*** STARTED ***')
    csv = open(opts.statistics,'w') if opts.statistics is not None else None
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((opts.ip, opts.port))
        if opts.extended:
            opts.dtype = '>f4' if opts.dtype is None else opts.dtype
            rssx(s,opts, csv=csv)
        else:
            opts.dtype = '<i2' if opts.dtype is None else opts.dtype
            rss(s,opts, csv=csv)
    except Exception, e:
        logger.error('rss-test', exc_info=True)
    finally:
        if csv is not None:
            csv.close()