#!/usr/bin/env python
'''
Script to emulate a Radio Sky Spectrograph client application.

The program captures spectrograph output from a streaming server and writes it in an ASCII .csv format as described by rtl-power.  Two stream protocols are implemented:

Basic Radio Sky Spectrograph (http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html)
Binary rtl-power/Extended RSS Spectrograph (https://github.com/myriadrf/RASDR/issues/16)
'''
import struct
import os
import sys
import time
import datetime
import logging
import socket, asyncore
import numpy as np
import traceback
# http://stackoverflow.com/questions/13218506/how-to-get-system-timezone-setting-and-pass-it-to-pytz-timezone
from dateutil.tz import tzlocal

DEF_VERSION = '0.2.5.1'     # x.y.z.* to match RASDRproc version

UNIX_EPOCH  = 518400    # 00:00 GMT January 6, 1970 
PKT_FMT     = '!dfffII'
PKT_SZ      = struct.calcsize(PKT_FMT)
PKT_DTYPE   = np.dtype( [('timestamp','>f8'),('hz_low','>f4'),('hz_high','>f4'),('hz_step','>f4'),('samples','>u4'),('channels','>u4')] )

# http://stackoverflow.com/questions/16867347/step-by-step-debugging-with-ipython
# https://github.com/ipython/ipython/wiki/Cookbook%3a-Updating-code-for-use-with-IPython-0.11-and-later
def _ipsh():
    from IPython.frontend.terminal.embed import InteractiveShellEmbed
    from IPython.config.loader import Config
    import inspect
    ipshell = InteractiveShellEmbed(config=Config(), 
        banner1='*** STOP\nCTRL-D to exit', exit_msg='Resume...')
    frame = inspect.currentframe().f_back
    msg   = 'Stopped at {0.f_code.co_filename} at line {0.f_lineno}'.format(frame)
    # Go back one level! 
    # This is needed because the call to ipshell is inside the function ipsh()
    ipshell(msg,stack_depth=2)

class connection(asyncore.dispatcher):
    pktlen = 1024
    data = b''
    state = 'Disconnected'
    partial = False
    def __init__(self,ip,port,name='connection'):
        """
        Handle connection to RSS(x) servers providing histograms.
        
        @param ip: ip address of server, use '' for localhost
        @param port: port that server listens on
        @option name: descriptive identification for this connection object
        """
        asyncore.dispatcher.__init__(self)
        self.name = name
        self.OnPacketReceived = self.packetDiscard
        self.OnConnectReceived = self.connectionReceived
        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connect((ip,port))

    def packetDiscard(self,_buf):
        """Drop remaining bytes in connection object."""
        self.data = b''
        
    def parseConnectionString(self,buf):
        """
        Interpret buffer as a connection string from an RSS(x) server.
        
        @param buf: bytes received in connection string
        @return: a dictionary with key/value pairs interpreted from buf
        """
        d  = buf.decode('ascii', errors='ignore').rpartition('|')
        connect = d[0].split('|')
        # parse key/value pairs in connection string
        conf = {}
        for kw in connect:
            kv = kw.split(' ')
            conf[kv[0]] = int(kv[1])
        return conf

    def connectionReceived(self,buf):
        """Default connection handler that drops the connection."""
        self.close()
        self.state = 'Disconnected'
        return {}
        
    def readable(self):
        return not self.state.startswith('Disconnected')

    def handle_error(self):
        traceback.print_exc(file=sys.stderr)
        self.close()
    
    def handle_connect(self):
        self.state = 'Connecting'
        self.pktlen = 1024
    
    def handle_close(self):
        self.close()

    def handle_write(self):
        pass
    
    def handle_read(self):
        """
        Determine if more data is needed from socket and perform callbacks.
        """
        extra = self.pktlen - (len(self.data) % self.pktlen) if len(self.data)<self.pktlen else 0
        logger.debug('%s:%s:handle_read().extra=%d'%(self.name,self.state,extra))
        if extra > 0:
            more = self.recv(extra)
            if len(more)==0:
                self.close()
                return
            self.data += more
        if self.partial or len(self.data)==self.pktlen:
            logger.debug('%s:%s:handle_read().len(self.data)=%d'%(self.name,self.state,len(self.data)))
            if self.state.startswith('Connecting'):
                self.state = 'Connected'
                self.OnConnectReceived(self.data)
            else:
                self.OnPacketReceived(self.data)

class statistics(object):
    stats = {}
    dt = None
    def __init__(self):
        """
        Compute statistics on a variety of buffers.
        
        To use, instantiate a statistics object, call the update() and
        obtain the string representation of the object to get formatted output.
        """
        super(statistics,self).__init__()
        self.stats['n']    = 0
        self.stats['min']  = 4096
        self.stats['max']  = -370
        self.stats['mean'] = 0.0
        self.stats['var']  = 0.0
        ts = time.time()
        self.dt = datetime.datetime.fromtimestamp(ts,tzlocal())

    def header(self):
        """Return a string that represents the column headings of the statistics."""
        return 'TS,N,MIN,MAX,MEAN,VAR'

    def update(self,dt,elements):
        """
        Update the statistics.
        
        @param dt: A datetime object representing the timestamp from this element set.
        @param elements: An numpy array of numbers to compute statistics on.
        @return: nothing
        """
        self.dt = dt
        self.stats['n']   += 1
        self.stats['min']  = elements.min() # if elements.min() < stats['min'] else stats['min']
        self.stats['max']  = elements.max() # if elements.max() > stats['max'] else stats['max']
        # http://stackoverflow.com/questions/19391149/numpy-mean-and-variance-from-single-function
        self.stats['mean'] = elements.mean()
        c = elements-self.stats['mean']
        self.stats['var']  = np.dot(c,c)/elements.size

    def __str__(self):
        msg = '%d,%.1f,%.1f,%.1f,%.1f' % \
            (self.stats['n'], self.stats['min'], self.stats['max'], \
             self.stats['mean'], self.stats['var'])
        return self.dt.isoformat()+','+msg        
 
class rss(object):
    name = 'rss'
    dtyp = np.dtype('<i2')
    header = ''
    channels = 0
    eos_marker = None
    opts = None
    stats = None

    def __init__(self,opts):        
        """
        Implement a client to the RSS protocol.
        
        @param opts: A dictionary containing various switches and selections.
            The following are required:
            - ip: The address of the server to connect to
            - port: The port that the server listens to
            - iso8601: a boolean to produce ISO-8601 timestamps in the output.  The RTL-POWER
              tools have trouble with this format, so it is not the default.
            - statistics: A boolean to capture and emit statistics on stderr while operating.
            - quiet: A boolean to produce no runtime output on stderr while operating.
            - info: A boolean to choose to only display the connection string and close the connection.
            
        Following the creation of the class, enter into the asyncore.loop() to
        allow the program to operate.  The class implements the necessary callback
        functions and state machine to interpret the stream from the server and produce
        an 'rtl-power' compatible output file suitable for use with plotting tools
        as provided by: http://kmkeen.com/rtl-power/
        
        The protocol is described here:
        http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html
        """
        super(rss,self).__init__()
        self.conn = connection(opts.ip,opts.port,self.name+'.connection')
        self.conn.OnPacketReceived = self.OnPacketReceived
        self.conn.OnConnectReceived = self.OnConnectReceived
        self.conn.pktlen = 1024
        self.conn.partial = True
        self.eos_marker = np.frombuffer(b'\xFE\xFE',dtype=self.dtyp)
        self.opts = opts

    def OnPacketReceived(self,buf):
        """Implement the callback when a spectrogram packet is received."""
        import binascii
        logger.debug('%s:%s:OnPacketReceived().len(buf)=%d:\n%s'%(self.name,self.conn.state,len(buf),binascii.hexlify(buf)))
        if self.conn.state.startswith('Payload'):
            # RSS timestamp @reception of payload
            ts = time.time()
            dt = datetime.datetime.fromtimestamp(ts,tzlocal())
            if self.opts.iso8601:
                tstamp = dt.isoformat()+', '
            else:
                tstamp = dt.strftime('%Y-%m-%d, %H:%M:%S, ')
            # parse payload as RSS would
            b = np.frombuffer(buf,dtype=self.dtyp)
            psd = np.reshape(b, (-1,self.channels+1))
            logger.debug('%s:%s:OnPacketReceived().psd[0][%d]=%d ? %d'%(self.name,self.conn.state,self.channels,psd[0][self.channels],self.eos_marker))
            assert(psd[0][self.channels] == self.eos_marker)
            scan = psd[0][0:self.channels]
            db = ', '.join(format(x,'d') for x in scan)
            # handle statistics option (produce header to stderr)
            if self.opts.statistics:
                self.stats.update(dt,scan)
                sys.stderr.write(str(self.stats)+' \r')
                sys.stderr.flush()
            # emit rtl-power string (with frequency info captured in header)
            sys.stdout.write(tstamp+self.header+db+os.linesep)
            self.conn.packetDiscard(buf)
            return
        else:
            self.conn.close()

    def OnConnectReceived(self,buf):
        """Implement the callback when a connection to the server is made."""
        ts = time.time()
        conf = self.conn.parseConnectionString(buf)

        logger.debug('%s:%s:OnConnectReceived().conf=%s'%(self.name,self.conn.state,str(conf)))

        # ensure canonical connection string
        assert('F' in conf.keys())
        assert('S' in conf.keys())
        assert('O' in conf.keys())
        assert('C' in conf.keys())

        hz_low  = float((conf['F'] - conf['S']/2) + conf['O'])
        hz_step = float(conf['S']) / float(conf['C'])
        hz_high = hz_low + float(conf['C']) * hz_step
        self.header = '%.0f, %.0f, %.0f, 1, ' % (hz_low, hz_high, hz_step) # NB: samples is not provided, so use '1'
        self.channels = conf['C']

        if not self.opts.quiet:    # diagnostic connection message
            msg  = 'CenterFrequencyHertz=%d\n'%conf['F']
            msg += 'BandwidthHertz=%d\n'%conf['S']
            msg += 'OffsetHertz=%d\n'%conf['O']
            msg += 'NumberOfChannels=%d\n'%conf['C']
            dt = datetime.datetime.fromtimestamp(ts,tzlocal())
            msg += 'Connect @%s\n'%dt.isoformat()
            hz_hdr = 'Hz low, Hz high, Hz step='
            msg += hz_hdr+self.header+'\n'
            logger.info(msg)

        # handle case where they only wanted to get connection metadata
        if self.opts.info:
            self.conn.close()
            return
        # handle statistics option (produce header to stderr)
        if self.opts.statistics:
            self.stats = statistics()
            sys.stderr.write(self.stats.header()+os.linesep)
        # consume (variable) connection buffer leaving payload
        d  = buf.decode('ascii', errors='ignore').rpartition('|')
        try:
            self.conn.data = bytes(d[2].strip(),'utf-8')
        except TypeError as e:
            # Python2 throws TypeError
            if str(e).startswith('str()'):
                self.conn.data = bytes(d[2].strip())
            else:
                raise
        # state to receive payloads
        self.conn.pktlen  = (self.channels+1)*self.dtyp.itemsize
        self.conn.partial = False
        self.conn.state   = 'Payload'
        # process any full payloads contained in the connection
        while len(self.conn.data) > self.conn.pktlen:
            buf = self.conn.data
            logger.debug('%s:%s:OnConnectReceived().loop.len(buf2)=%d'%(self.name,self.conn.state,len(buf)))
            self.OnPacketReceived(buf[0:self.conn.pktlen])   # NB: discards self.conn.data
            self.conn.data = buf[self.conn.pktlen:]
            logger.debug('%s:%s:OnConnectReceived().loop.len(buf3)=%d'%(self.name,self.conn.state,len(self.conn.data)))
        # after this, the async system kicks in to give us packets
        import binascii
        logger.debug('%s:%s:OnConnectReceived().loop.len(buf)=%d:\n%s'%(self.name,self.conn.state,len(self.conn.data),binascii.hexlify(self.conn.data)))

class rssx(object):
    name = 'rssx'
    dtyp = np.dtype('>f4')
    dt = None
    header = ''
    channels = 0
    opts = None
    stats = None

    def __init__(self,opts):
        """
        Implement a client to an 'Extended' RSS protocol.
        
        @param opts: A dictionary containing various switches and selections.
            The following are required:
            - ip: The address of the server to connect to
            - port: The port that the server listens to
            - iso8601: a boolean to produce ISO-8601 timestamps in the output.  The RTL-POWER
              tools have trouble with this format, so it is not the default.
            - statistics: A boolean to capture and emit statistics on stderr while operating.
            - quiet: A boolean to produce no runtime output on stderr while operating.
            - info: A boolean to choose to only display the connection string and close the connection.
            
        Following the creation of the class, enter into the asyncore.loop() to
        allow the program to operate.  The class implements the necessary callback
        functions and state machine to interpret the stream from the server and produce
        an 'rtl-power' compatible output file suitable for use with plotting tools
        as provided by: http://kmkeen.com/rtl-power/
        
        The protocol is described here:
        https://github.com/myriadrf/RASDR/issues/16
        """
        super(rssx,self).__init__()
        self.conn = connection(opts.ip,opts.port,self.name+'.connection')
        self.conn.OnPacketReceived = self.OnPacketReceived
        self.conn.OnConnectReceived = self.OnConnectReceived
        self.conn.pktlen = 1024
        self.conn.partial = False
        self.opts = opts

    def OnPacketReceived(self,buf):
        """Implement the callback when a spectrogram packet is received."""
        import binascii
        logger.debug('%s:%s:OnPacketReceived().len(buf)=%d:\n%s'%(self.name,self.conn.state,len(buf),binascii.hexlify(buf)))
        if self.conn.state.startswith('Header'):
            ts, hz_low, hz_high, hz_step, samples, self.channels = struct.unpack(PKT_FMT, buf)
            self.dt = datetime.datetime.fromtimestamp(ts)
            if self.opts.iso8601:
                self.header = self.dt.isoformat()+', '
            else:
                self.header = self.dt.strftime('%Y-%m-%d, %H:%M:%S, ')
            self.header += '%.0f, %.0f, %.0f, %d, '%(hz_low, hz_high, hz_step, samples)
            self.conn.packetDiscard(buf)
            self.conn.pktlen = (self.channels)*self.dtyp.itemsize
            self.conn.state = 'Payload'
            return
        elif self.conn.state.startswith('Payload'):
            b = np.frombuffer(buf,dtype=self.dtyp)
            psd = np.reshape(b, (-1,self.channels))
            # handle statistics option (produce header to stderr)
            if self.opts.statistics:
                self.stats.update(self.dt,psd[0])
                sys.stderr.write(str(self.stats)+' \r')
                sys.stderr.flush()
            db = ', '.join(format(x,'.4f') for x in psd[0])
            sys.stdout.write(self.header+db+os.linesep)
            self.conn.packetDiscard(buf)
            self.conn.pktlen = PKT_SZ
            self.conn.state = 'Header'
            return
        else:
            self.conn.close()

    def OnConnectReceived(self,buf):
        """Implement the callback when a connection to the server is made."""
        ts = time.time()
        conf = self.conn.parseConnectionString(buf)

        # ensure canonical connection string
        assert('CenterFrequencyHertz' in conf.keys())
        assert('BandwidthHertz' in conf.keys())
        assert('OffsetHertz' in conf.keys())
        assert('NumberOfChannels' in conf.keys())

        if not self.opts.quiet:    # diagnostic connection message
            msg  = 'CenterFrequencyHertz=%d\n'%conf['CenterFrequencyHertz']
            msg += 'BandwidthHertz=%d\n'%conf['BandwidthHertz']
            msg += 'OffsetHertz=%d\n'%conf['OffsetHertz']
            msg += 'NumberOfChannels=%d\n'%conf['NumberOfChannels']
            dt = datetime.datetime.fromtimestamp(ts,tzlocal())
            hz_low  = float((conf['CenterFrequencyHertz'] - conf['BandwidthHertz']/2) + conf['OffsetHertz'])
            hz_step = float(conf['BandwidthHertz']) / float(conf['NumberOfChannels'])
            hz_high = hz_low + float(conf['NumberOfChannels']) * hz_step
            msg += 'Connect @%s\n'%dt.isoformat()
            hz_hdr = 'Hz low, Hz high, Hz step='
            hz_msg = '%.0f,%.0f,%.0f' % (hz_low, hz_high, hz_step)
            msg += hz_hdr+hz_msg+'\n'
            logger.info(msg)

        # dispose of this buffer
        self.conn.packetDiscard(buf)
        # handle case where they only wanted to get connection metadata
        if self.opts.info:
            self.conn.close()
            return
        # handle statistics option (produce header to stderr)
        if self.opts.statistics:
            self.stats = statistics()
            sys.stderr.write(self.stats.header()+os.linesep)
        # setup to receive a header next
        self.conn.pktlen = PKT_SZ
        self.conn.state = 'Header'

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('rss2rtl-power.py [options]')
    p.set_description(__doc__)
    p.add_option('-a', '--address', dest='ip', type='str', metavar='A', default='localhost',
        help='Specify the server address; default=%default')
    p.add_option('-p', '--port', dest='port', type='int', metavar='N', default=8888,
        help='Specify the port to connect to; default=%default')
    p.add_option('-i', '--info', dest='info', action='store_true', default=False,
        help='Produce information about the connection only; do not receive/parse scans')
    p.add_option('-e', '--extended', dest='extended', action='store_true', default=False,
        help='Interpret the extended RSS format')
    p.add_option('--iso8601', dest='iso8601', action='store_true', default=False,
        help='Emit ISO-8601 Timestamps (YYYY-MM-DDTHH:MM:SS.nnnZ), default=%default')
    p.add_option('--statistics', dest='statistics', action='store_true', default=False,
        help='Dump statistical information to the stderr in comma-separated-values format, default=%default')
    p.add_option('-v', '--verbose', dest='verbose', action='store_true', default=False,
        help='Verbose')
    p.add_option('-q', '--quiet', dest='quiet', action='store_true', default=False,
        help='Do not display a connection message on stderr')

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
    if not opts.quiet:
        logger.info('*** STARTED ***')
    try:
        c = rssx(opts) if opts.extended else rss(opts)
        asyncore.loop(timeout=2)
    except Exception as e:
        logger.error('rss2rtl-power: '+str(e), exc_info=True)
