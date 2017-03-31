import sys
import struct
import os
import sys
import time
import datetime
import logging
import socket, asyncore
import numpy as np
import traceback

from rss2rtlpower import rss,rssx
from spectrogram import Spectrogram

TIMEOUT     = 2 #seconds
DEF_VERSION = '0.2.5.2'     # x.y.z.* to match RASDRproc version

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('rss-power.py -m [print,spectrogram] [options]')
    p.set_description(__doc__)
    p.add_option('-a', '--address', dest='ip', type='str', metavar='A', default='localhost',
        help='Specify the server address; default=%default')
    p.add_option('-p', '--port', dest='port', type='int', metavar='N', default=8888,
        help='Specify the port to connect to; default=%default')
    p.add_option('-i', '--info', dest='info', action='store_true', default=False,
        help='Produce information about the connection only; do not receive/parse scans')
    p.add_option('-e', '--extended', dest='extended', action='store_true', default=True,
        help='Interpret the extended RSS format, default=%default')
    p.add_option('--iso8601', dest='iso8601', action='store_true', default=False,
        help='Emit ISO-8601 Timestamps (YYYY-MM-DDTHH:MM:SS.nnnZ), default=%default')
    p.add_option('--statistics', dest='statistics', action='store_true', default=False,
        help='Dump statistical information to the stderr in comma-separated-values format, default=%default')
    p.add_option('-v', '--verbose', dest='verbose', action='store_true', default=False,
        help='Verbose')
    p.add_option('-q', '--quiet', dest='quiet', action='store_true', default=False,
        help='Do not display a connection message on stderr, default=%default')
    p.add_option('-c','--colormap',dest='colormap',default='gray',  # sorry, I didnt have 'magma' in my colormap
        help='Colormap from matplotlib color maps, default=%default')
    p.add_option('-f','--colormap-file',dest='colormapfile',type='string',default='',
        help='Colormap from file overrrides -c')
    p.add_option('-m', '--mode', dest='mode', type='string', default='spectrogram',
                 help='operation mode print or spectrogram, default=%default')
    p.add_option('-d', '--db-min', dest='db_min', type='int', default=-30,
                 help='minimum dB for color assignment, default=%default')
    p.add_option('-x', '--db-max', dest='db_max', type='int', default=30,
                 help='maximum dB for color assignment, default=%default')
    opts, args = p.parse_args(sys.argv[1:])

    logging.basicConfig(format='%(message)s', level=logging.INFO)
    logger = logging.getLogger(__name__)
    x, y, name = sys.argv[0].replace('\\', '/').rpartition('/')
    name, x, ext = name.rpartition('.')
    handler = logging.FileHandler(name + '.log')
    formatter = logging.Formatter('%(levelname)s:%(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    logger.setLevel(logging.DEBUG if opts.verbose else logging.INFO)

    if not opts.quiet:
        logger.info(' started')
    try:
        c = rssx(opts) if opts.extended else rss(opts)
        print(opts.mode)
        s = None
        if str.lower(opts.mode) == 'spectrogram':
            s = Spectrogram(opts)
            s.open_colormap(opts.colormap,opts.colormapfile)
        c.spectrogram = s
        asyncore.loop(TIMEOUT)
        logger.error(' connection timeout')
    except Exception as e:
        logger.error('rss2rtl-power: ' + str(e), exc_info=True)

