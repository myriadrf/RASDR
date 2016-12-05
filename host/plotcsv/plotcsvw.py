from __future__ import print_function
import sys
import logging
from gooey import Gooey, GooeyParser
from plotcsv import execute, DEF_VERSION, DEF_AVERAGE, DEF_DELIM, DEF_CALIB

@Gooey(advanced=True)
def main():
    p = GooeyParser(
        description='Post-Process RASDRviewer/RASDRproc spectrum data output files')
    p.add_argument(      "--version", action='version', version='%(prog)s '+DEF_VERSION)
    # NB: need to order these with the most used options first
    # http://stackoverflow.com/questions/20165843/argparse-how-to-handle-variable-number-of-arguments-nargs
    p.add_argument(      "file", widget="FileChooser")
    p.add_argument('-b', '--background', type=str, metavar='PATH', default='', widget="FileChooser",
        help='Specify how to perform background subtraction;'+
             'if the word automatic is used, then the background will be taken'+
             'from the average of all lines in the file.  Otherwise, it is taken'+
             'as a file to process.  The file must have the same frequency plan as the foreground file.')
    p.add_argument('-a', '--average', type=int, metavar='N', default=DEF_AVERAGE,
        help='Specify the number of spectra to average for each plot')
    p.add_argument('-s', '--smooth', type=int, metavar='N', default=0,
        help='Smooth final plot using a sliding window of N points')
    p.add_argument('--fcenter', dest='fc', type=float, default=0.0,
        help='Define the offset for the center frequency in Hz')  #default=%f'%0.0)
    p.add_argument('--statistics', type=str, metavar='PATH', default=None, widget="FileChooser",
        help='Dump statistical information to a file in comma-separated-values format')
    p.add_argument('-i', '--info', action='store_true', default=False,
        help='Produce information about a file only; do not generate any plots')
    p.add_argument('-g', '--gui', action='store_true', default=False,
        help='Create interactive PLOTS')
    g = p.add_mutually_exclusive_group()
    g.add_argument("-v", "--verbose", default=False, help="Turn on verbose output", action="store_true")
    g.add_argument("-q", "--quiet", default=False, help='Suppress progress messages', action="store_true")
    # call matplotlib.use() only once
    p.set_defaults(matplotlib_use = False)
    p.add_argument('-c', '--cancel-dc', dest='canceldc', action='store_true', default=False,
        help='Cancel out component at frequency bin for 0Hz')
    p.add_argument('-d', '--delimiter', type=str, metavar='CHAR', default=DEF_DELIM,
        help='Specify the delimiter character to use"')
    p.add_argument('-e', '--localtime', action='store_true', default=False,
        help='Indicate that .csv file has timestamps in RASDRviewer\'s "LocalTime" format')
    p.add_argument('-k', '--calibration', type=float, metavar='CONST', default=DEF_CALIB,
        help='Specify the calibration constant for the system; 0.0=uncal')    #default=%f'%DEF_CALIB)
    p.add_argument('-l', '--line', action='store_true', default=False,
        help='Perform line-by-line processing instead of loading entire file(s); NOTE: much slower but tolerates low memory better.')
##    p.add_argument('-m', '--milliwatt', dest='dbm', action='store_true', default=False,
##        help='Plot in decibels referenced to 1mW (dBm/Hz)')
##    p.add_argument('-t', '--datetime', action='store_true', default=False,
##        help='Indicate that timestamps in the .csv file are in Excel\'s datetime format')
    p.add_argument('--debug', action='store_true', default=False,
        help='Drop into ipython shell at predefined point(s) to debug the script')
    p.add_argument('--hold', action='store_true', default=False,
        help='Perform a maximum value HOLD during averaging and plot it as a second line')
    p.add_argument('--bplot', action='store_true', default=False,
        help='If using background file, choose whether to plot the background reference in a difffert color')
    p.add_argument('--ptype', type=str, metavar='TYPE', default='log',
        help='Control plot vertical scale (linear or log)')
    p.add_argument('--atype', type=str, metavar='TYPE', default='log',
        help='Control averaging method (linear or log)')
        # http://www.dtic.mil/dtic/tr/fulltext/u2/657404.pdf
    ## for handling RASDRviewer versions
    v = DEF_VERSION.split('.')
    ver = v[0]+'.'+v[1]+'.'+v[2]
    p.add_argument('--format', type=str, metavar='X.Y.Z', default=ver,
        help='Specify the RASDRviewer .csv output format to interpret')

    opts = p.parse_args(sys.argv)
    execute(opts)

if __name__ == '__main__':
    main()
