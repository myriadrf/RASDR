'''
Script to emulate a Radio Sky Spectrograph client application to verify RSS
output.  The program is used to diagnose and analyze the streaming spectrum.
'''
import sys
import datetime
import logging
import numpy as np

DEF_VERSION = '0.2.3.0'     # x.y.z.* to match RASDRproc version

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('rss-test.py [options]')
    p.set_description(__doc__)
    #p.set_defaults(ip = 'localhost')
    #p.set_defaults(port = 8888)
    p.add_option('-a', '--address', dest='ip', type='str', metavar='ADDR', default='localhost',
        help='Specify the server address; default=%default')
    p.add_option('-p', '--port', dest='port', type='int', metavar='N', default=8888,
        help='Specify the port to connect to; default=%default')

    opts, args = p.parse_args(sys.argv[1:])

    # logging boilerplate (screen+log file)
    logging.basicConfig(format='%(message)s',level=logging.DEBUG)
    logger = logging.getLogger(__name__)
    x,y,name = args[0].replace('\\','/').rpartition('/')
    name,x,ext = name.rpartition('.')
    handler = logging.FileHandler(name+'.log')
    formatter = logging.Formatter('%(levelname)s:%(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    logger.setLevel(logging.DEBUG if opts.verbose else logging.INFO)
    try:
        print 'opts=',opts
        print 'args=',args
    except Exception, e:
        logger.error('rss-test', exc_info=True)
