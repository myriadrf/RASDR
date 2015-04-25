#import math import time
import sys
import datetime
import logging
import numpy as np
from StringIO import StringIO

DEF_VERSION = '1.2.1.1-dev'     # to match RASDRviewer version
DEF_DELIM   = ','
DEF_AVERAGE = 1
DEF_CALIB   = 0.0           # Paul uses (0.73278^2)/2000 as Qstep^2/ADC impedance

def excel2dt(et):
    # http://stackoverflow.com/questions/1703505/excel-date-to-unix-timestamp
    # http://stackoverflow.com/questions/3682748/converting-unix-timestamp-string-to-readable-date-in-python
    ts = (et - 25569)*86400 # 25569 is days since 1900-01-01
    ts = ts + (4*60*60)     # timezone EST5EDT return
    return datetime.datetime.fromtimestamp(float(ts))

def dt2excel(dt,tz=None):
    import pytz
    # http://stackoverflow.com/questions/9574793/how-to-convert-a-python-datetime-datetime-to-excel-serial-date-number
    # http://stackoverflow.com/questions/4530069/python-how-to-get-a-value-of-datetime-today-that-is-timezone-aware
    dte = datetime.datetime(1899, 12, 30, tzinfo=pytz.timezone(tz)) if tz else datetime.datetime(1899, 12, 29)
    delta = dt - dte    # set w/r/t excel2dt() date; NB: do not know why this must be set 3 days earlier
    return float(delta.days) + (float(delta.seconds) / 86400)

def translate_tz(tz):
    # Paul uses some wierd strings in RASDRviewer to represent timezones
    # FIXME: I am still unhappy with this...  But I need this to make the plots we took in June-July 2014
    tzo=''
    if tz.startswith('UT20'):
        tzo='-0500'
        tz=tz.replace('UT20','UTC')
    elif tz.startswith('US/Eastern'):
        tzo='-0500'
        tz=tz.replace('US/Eastern','UTC')
    elif not tz.startswith('UTC'):  # FIXME: weak...
        tz=tz.replace('UT','UTC')
    return tz, tzo

def open_spectrum_file(filename,opts):
    obj = {}
    if opts.excel:
        # this is Paul's "Excel-optimized" .csv format
        # http://stackoverflow.com/questions/13311471/skip-a-specified-number-of-columns-with-numpy-genfromtxt
        # http://stackoverflow.com/questions/466345/converting-string-into-datetime
        # http://stackoverflow.com/questions/698223/how-can-i-parse-a-time-string-containing-milliseconds-in-it-with-python

        f=open(filename,'r')
        key=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='str')
        d=key[4].replace('"','') if len(key) > 4 else '00/00/00'
        tz=key[6].replace('"','') if len(key) > 7 else 'UTC'
        # translate strange labels from RASDRviewer_W_1_0_5
        tz=translate_tz(tz)
        ## second line: frequency bin information
        freq=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='float')
        freq=freq[1:]           # remove the 1st column, as it is a 'nan' when interpreted as a 'float'
        ## third line-to-end: extract first *column* as text
        t=np.genfromtxt(f,delimiter=opts.delimiter,usecols=[0],dtype='str')
        time = []
        for i in range(1,t.shape[0]):
            # translate HH:MM:SS:ms into HH:MM:SS.ms
            if t[i].count(':') > 2:
                a,x,b = t[i].rpartition(':')
            else:
                a = t[i]
                b = '0'
            ts=a+'.'+b
            time.append(datetime.datetime.strptime(d+'T'+ts, '%m/%d/%yT%H:%M:%S.%f'))
        f.seek(0)               # start over
        f.readline()            # dump the first line
        f.readline()            # dump the second line
        # update the object to return
        obj['file'] = f
        obj['freq'] = freq
        obj['time'] = time
        obj['opts'] = opts
##    elif opts.datetime:
##        # this is the "Excel-datetime" .csv format (proposed for RASDRviewer_W_1_0_4, but not implemented)
##        f=open(filename,'r')
##        freq = np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='float')
##        t=np.genfromtxt(f,delimiter=opts.delimiter,usecols=[0],dtype='float')
##        time = []
##        for i in range(len(t)):
##            time.append(excel2dt(t[i]))
##        f.seek(0)               # start over
##        f.readline()            # dump the first line
##        f.readline()            # dump the second line
##        # update the object to return
##        obj['file'] = f
##        obj['freq'] = freq
##        obj['time'] = time
##        obj['opts'] = opts
    else:
        # this is the "Extended" .csv format produced by RASDRviewer_W_1_2_1
        from dateutil import parser

        f=open(filename,'r')
        ## first line: key-value pairs
        key=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='str',comments='\\')
        if len(np.atleast_1d(key)) < 2:
            raise Exception('unable to parse %s -- check first line'%filename)
        d=key[4].replace('"','') if len(key) > 4 else '00/00/00'
        tz=key[6].replace('"','') if len(key) > 7 else 'UTC'
        # translate strange labels from RASDRviewer_W_1_0_5
        tz,tzo=translate_tz(tz)
        ## RASDRViewer 1.2.x, Paul "adds" a specifier to the 2nd line and moves the rest of the lines down
        key=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='str')
        dumplines = 1
        fscale = 1.0
        if len(np.atleast_1d(key)) < 2:
            tag = str(key).lower()
        else:
            tag = str(key[0]).lower()
        if tag.find('hz')>0:
            if tag.startswith('khz'):
                fscale = 0.001
            elif tag.startswith('ghz'):
                fscale = 1000.0
            # need to dump an extra line later
            dumplines = dumplines + 1
        f.seek(0)
        for i in range(dumplines):
            f.readline()    # dump the first line, so we are back to our 2nd/3rd line
        ## second/third line: frequency bin information
        freq=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='float')
        freq=freq[1:]           # remove the 1st column, as it is a 'nan' when interpreted as a 'float'
        ## third line-to-end: extract first *column* as text
        t=np.genfromtxt(f,delimiter=opts.delimiter,usecols=[0],dtype='str')                # 1st column are *almost* ISO-8601 datetime strings
        time = []
        for i in range(1,t.shape[0]):
            a,x,b = t[i].rpartition(':')  # deal with Paul's 'YYYY-MM-DDTHH:MM:SS:sssZ' format in RASDRviewer_W_1_0_5
            if a.find('T')>0:
                time.append(parser.parse(a+'.'+b+tzo))
            else:
                time.append(parser.parse(d+'T'+a+'.'+b+tzo))
        f.seek(0)
        for i in range(dumplines):
            f.readline()    # dump the first line, so we are back to our 2nd/3rd line
        # update the object to return
        obj['file'] = f
        obj['freq'] = freq*fscale
        obj['time'] = time
        obj['opts'] = opts
    
    if opts.verbose:
        log = logging.getLogger(__name__)
        x,y,name = f.name.replace('\\','/').rpartition('/')
        log.info('%s.date=%s (%s)'%(name,d+' '+tz,str(obj['time'][0])))
        log.info('%s.time=%d'%(name,len(obj['time'])))
        log.info('%s.freq=%s (scale=%f)'%(name,str(obj['freq'].shape),fscale))
    return obj

def read_spectrum_line(obj):
    opts = obj['opts']
    f    = obj['file']
##    if opts.datetime:
##        data = np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter)
##        data = data[1:]
##    else:
    freq = obj['freq']
    data = np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,usecols=range(1,freq.shape[0]+1),dtype='float')
    return data         # spectral information in colums 1..N-2 (last column is junk)

def read_spectrum_array(obj):
    opts = obj['opts']
    f    = obj['file']
##    if opts.datetime:
##        data = np.genfromtxt(f,delimiter=opts.delimiter)
##        data = data[1:,1:]
##    else:
    freq = obj['freq']
    data = np.genfromtxt(f,delimiter=opts.delimiter,usecols=range(1,freq.shape[0]+1),dtype='float')
    return data         # spectral information in colums 1..N-2 (last column is junk)

def generate_spectrum_plots(filename,opts):
    log = logging.getLogger(__name__)
    if len(opts.background) > 0:
        if opts.background.lower() == 'automatic':
            bg = open_spectrum_file(filename,opts)
        else:
            bg = open_spectrum_file(opts.background,opts)
        lastrow = len(bg['time'])-1
        bkg = np.zeros(len(bg['freq']))
        acc = np.zeros(len(bg['freq']))
        n   = 0
        log.info('loading %s...'%bg['file'].name)
        if not opts.line:
            s = read_spectrum_array(bg)
        for fr in range(len(bg['time'])):
            n = n+1
            if opts.line:
                s = read_spectrum_line(bg)
                log.debug('bg %d/%d mean=%f dB'%(fr,len(bg['time']),s.mean()))
                acc += s
            else:
                acc += s[fr]
        bkg += acc / float(n)
        log.info('background %d samples=[%f,%f] mean=%f',n,bkg.min(),bkg.max(),bkg.mean())
        if opts.background.lower() == 'automatic':
            # distribute mean value of to all frequency bins to construct a total average over all samples
            # this is needed if doing a 'self' background correction
            bkg = np.ones(len(bg['freq'])) * bkg.mean()
        if not opts.line:
            del s
        fg = open_spectrum_file(filename,opts)
        if not len(fg['freq'])==len(bg['freq']):
            raise Exception('background file must have same number of frequency bins as the foreground file')
        if not np.array_equal(fg['freq'],bg['freq']):
            log.warn('background file does not specify the same frequency bins as the foreground file')
        del bg
    else:
        fg = open_spectrum_file(filename,opts)
        bkg = np.zeros(len(fg['freq']))

    ts_a = fg['time']
    fMHz = fg['freq']+opts.fc
    zidx = np.searchsorted(fMHz,0)
    nbin = len(fMHz)
    lastrow = len(ts_a)-1
    bw   = (fMHz.max() - fMHz.min())*1e6/nbin
    if opts.calibration > 0.0:
        dbm = 10.0 * np.log10( opts.calibration * bw * 0.001 )  # power referenced to 1mW
    else:
        dbm = 0.0

    log.info('range (MHz)=[%f,%f]',fMHz.min(),fMHz.max())
    log.info('zero index=%d',zidx)
    log.info('frequency bins=%d',nbin)
    log.info('bandwidth/bin (Hz)=%f',bw)
    if lastrow > 0:
        delta = ts_a[lastrow] - ts_a[lastrow-1]
        log.info('start=%s',str(ts_a[0]))
        log.info('end  =%s',str(ts_a[lastrow]))
        s = (float(delta.seconds)+(float(delta.microseconds)/1e6))
        if s > 0.0:
            log.info('inter-frame period=%f sec (%.0f fr/s)',s,1.0/s)
    log.info('averaging=%s',str(opts.average))

    if not opts.line:
        log.info('loading %s...',fg['file'].name)
        s_a = read_spectrum_array(fg)
    acc = np.zeros(nbin)
    n   = 0
    for fr in range(len(ts_a)):
        dt = ts_a[fr]
        if opts.line:
            s = read_spectrum_line(fg)
        else:
            s = s_a[fr]
        s = s - bkg
        if opts.canceldc:
            log.debug('Cancel DC: frq %s',str(fMHz[zidx-4:zidx+5]))
            log.debug('Cancel DC: b4 %s',str(s[zidx-4:zidx+5]))
            a = (s[zidx-1] + s[zidx+1])/2.0
            if a < s[zidx]:
                s[zidx] = a
            log.debug('Cancel DC: ftr %s',str(s[zidx-4:zidx+5]))
        log.debug('line %d/%d max@%d val=%f',fr,len(ts_a),s.argmax(),s.max())
        if n == 0:
            tstart = dt.strftime('%Y-%m-%dT%H:%M:%S%z')
        n    = n+1
        acc += s
        if n >= opts.average or fr == lastrow:
            s   = acc / float(n)    # vector/scalar
            s   = s - dbm           # vector-scalar
            #s   = s - bkg           # vector-vector
            min = np.floor(s.min())-1.0
            max = np.ceil(s.max())+1.0
            tstop = dt.strftime('%Y-%m-%dT%H:%M:%S%z')
            if n > 1:
                title = 'Collected between %s and %s\nAveraged over %d frames'%(tstart,tstop,n)
            else:
                title = 'Collected at %s'%tstart
            if len(opts.background) > 0:
                title = title + ', with background subtraction'
            if opts.background.lower() == 'automatic':
                title = title + ' (automatic, %.2f dB)'%bkg.mean()
            else:
                title = title + ' (file)'
##            if opts.calibration:
##                title = title + ', cal=%.1f'%opts.calibration
            if opts.smooth > 0:
                title = title + ' and %d point smoothing'%opts.smooth
                ll = len(s)
                hh = opts.smooth/2
                ss = np.zeros(ll)
                for xx in range(hh):
                    ss[xx]      = s[xx]
                    ss[ll-xx-1] = s[ll-xx-1]
                for xx in range(ll-opts.smooth+1):
                    ss[hh+xx] = np.mean(s[xx:xx+opts.smooth])
                s = ss

            # http://stackoverflow.com/questions/6352740/matplotlib-label-each-bin
            from matplotlib.pyplot import figure, plot, axis, xlabel, ylabel, savefig, subplots
            from matplotlib.pyplot import title as _title
            from matplotlib.ticker import FormatStrFormatter

            fig, ax = subplots()
            plot(fMHz,s,hold=True,color='b')
            axis([fMHz[0],fMHz[nbin-1],min,max])
            ax.xaxis.set_major_formatter(FormatStrFormatter('%4.1f'))
            xlabel('frequency (MHz)')
##            if opts.dbm != 0.0:
##                ylabel('spectral power (dBm/Hz)')
            if len(opts.background) > 0:
                ylabel('spectral power (dB relative to background)')
                plot(fMHz,bkg,color='r')
            else:
                ylabel('spectral power (arbitrary unit)')
            _title(title)

            name = 'spectrum-%s.png'%dt.strftime('%Y_%b_%d_%H_%M_%S')
            savefig(name)
            log.info('Saved '+name)

            acc = np.zeros(nbin)
            n   = 0
            del fig, ax

def dump_spectrum_info(filename,opts):
    log = logging.getLogger(__name__)
    fg = open_spectrum_file(filename,opts)
    ts_a = fg['time']
    fMHz = fg['freq']
    zidx = np.searchsorted(fMHz,0)
    nbin = len(fMHz)
    lastrow = len(ts_a)-1
    bw   = (fMHz.max() - fMHz.min())*1e6/nbin

    log.info('range (MHz)=[%f,%f]',fMHz.min(),fMHz.max())
    log.info('zero index=%d',zidx)
    log.info('frequency bins=%d',nbin)
    log.info('bandwidth/bin (Hz)=%f',bw)

    tstart = ts_a[0].strftime('%Y-%m-%dT%H:%M:%S')
    if lastrow > 0:
        delta = ts_a[lastrow] - ts_a[lastrow-1]
        log.info('start=%s',str(ts_a[0]))
        log.info('end  =%s',str(ts_a[lastrow]))
        deltaT = dt = float(delta.seconds)+(float(delta.microseconds)/1e6)
        if len(ts_a) > 0:
            deltaT = ts_a[lastrow] - ts_a[0]
            deltaT = float(deltaT.seconds)+(float(deltaT.microseconds)/1e6)
            deltaT = deltaT / len(ts_a)
        tstop  = ts_a[lastrow].strftime('%Y-%m-%dT%H:%M:%S')
        log.info('seconds between records=%f (avg=%f)',dt,deltaT)
        title  = 'Collected between %s and %s'%(tstart,tstop)
        deltaT = min(dt,deltaT)
    else:
        title  = 'Collected at %s'%tstart
        deltaT = 0.0

    log.info('Analyzing records...  acceptable inter-frame time is [%f,%f] sec',deltaT-(deltaT*0.5),deltaT+(deltaT*0.5))
    d0  = ts_a[0]
    dX  = 0.0
    for fr in range(len(ts_a)):
        if fr == 0:
            continue
        log.debug('  d0=%s ts_a[%d]=%s',str(d0),fr,str(ts_a[fr]))
        dt = ts_a[fr] - d0
        dt = float(dt.seconds)+(float(dt.microseconds)/1e6)
        log.debug('    dt=%.6f abs(dt - deltaT)=%.6f',dt,abs(dt - deltaT))
        if dt < 1e-6:
            log.info('*** DUPLICATE: frame %d -> %d delta %f sec, expected %f+/-%f (@%s)',fr-1,fr,dt,deltaT,(deltaT*0.5),d0.strftime('%Y-%m-%dT%H:%M:%S.%f'))
        elif ts_a[fr] < d0:
            log.info('*** REGRESSION: frame %d -> %d has earlier timestamp (%s) than (@%s)',fr-1,fr,ts_a[fr].strftime('%Y-%m-%dT%H:%M:%S.%f'),d0.strftime('%Y-%m-%dT%H:%M:%S.%f'))
        elif abs(dt - deltaT) > (deltaT*0.5):
            log.info('*** SKIP: frame %d -> %d delta %f sec, expected %f+/-%f (@%s)',fr-1,fr,dt,deltaT,(deltaT*0.5),d0.strftime('%Y-%m-%dT%H:%M:%S.%f'))
            dX = dX + (dt - deltaT)
        d0 = ts_a[fr]
    if dX > 0.0:
        d0 = ts_a[0]
        dN = ts_a[-1]
        dt = dN - d0
        dt = float(dt.seconds)+(float(dt.microseconds)/1e6)
        if dt > 0.0:
            log.info('*** %f sec unaccounted for in %f sec capture (%.3f%%)',dX,dt,(dX*100.0/dt))
        else:
            log.info('*** %f sec unaccounted for but total capture length appears to be 0.0',dX)

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('plotcsv.py <filename.csv> [options]')
    p.set_description(__doc__)
    # call matplotlib.use() only once
    p.set_defaults(matplotlib_use = False)
    p.add_option('-a', '--average', dest='average', type='int', default=DEF_AVERAGE,
        help='Specify the number of spectra to average for each plot; default=%d'%DEF_AVERAGE)
    p.add_option('-b', '--background', dest='background', type='str', default='',
        help='Specify how to perform background subtraction;'+
             'if the word automatic is used, then the background will be taken'+
             'from the average of all lines in the file.  Otherwise, it is taken'+
             'as a file to process.  The file must have the same frequency plan as the foreground file.')
    p.add_option('-c', '--cancel-dc', dest='canceldc', action='store_true', default=False,
        help='Cancel out component at frequency bin for 0Hz')
    p.add_option('-d', '--delimiter', dest='delimiter', type='str', default=DEF_DELIM,
        help='Specify the delimiter character to use; default=%s'%DEF_DELIM)
    p.add_option('-e', '--excel', dest='excel', action='store_true', default=False,
        help='Indicate that .csv file is in RASDRviewer\'s "Excel-optimized" format')
    p.add_option('-k', '--calibration', dest='calibration', type='float', default=DEF_CALIB,
        help='Specify the calibration constant for the system; 0.0=uncal, default=%f'%DEF_CALIB)
    p.add_option('-l', '--line', dest='line', action='store_true', default=False,
        help='Perform line-by-line processing instead of loading entire file(s); NOTE: much slower but tolerates low memory better.')
##    p.add_option('-m', '--milliwatt', dest='dbm', action='store_true', default=False,
##        help='Plot in decibels referenced to 1mW (dBm/Hz)')
##    p.add_option('-t', '--datetime', dest='datetime', action='store_true', default=False,
##        help='Indicate that timestamps in the .csv file are in Excel\'s datetime format')
    p.add_option('-i', '--info', dest='info', action='store_true', default=False,
        help='Produce information about a file only; do not generate any plots')
    p.add_option('-v', '--verbose', dest='verbose', action='store_true', default=False,
        help='Verbose')
    p.add_option('-g', '--gui', dest='gui', action='store_true', default=False,
        help='Create interactive PLOTS')
    p.add_option('-s', '--smooth', dest='smooth', type='int', default=0,
        help='Smooth final plot using a sliding window of N points')
    p.add_option('--fcenter', dest='fc', type='float', default=0.0,
        help='Define the offset for the center frequency in Hz; default=%f'%0.0)
    opts, args = p.parse_args(sys.argv[1:])

    logging.basicConfig(format='%(message)s',level=logging.DEBUG)
    if args==[]:
        logging.getLogger(__name__).critical('Please specify a filename. Run with the -h flag to see all options.')
    else:
        # logging boilerplate (screen+log file)
        logger = logging.getLogger(__name__)
        x,y,name = args[0].replace('\\','/').rpartition('/')
        name,x,ext = name.rpartition('.')
        handler = logging.FileHandler(name+'.log')
        formatter = logging.Formatter('%(levelname)s:%(message)s')
        handler.setFormatter(formatter)
        logger.addHandler(handler)
        logger.setLevel(logging.DEBUG if opts.verbose else logging.INFO)
        try:
            if opts.gui:
                from platform import system
                if not opts.matplotlib_use and system().startswith('Windows'):
                    from matplotlib import use
                    use('wxagg')
                    opts.matplotlib_use = True
            if opts.info:
                dump_spectrum_info(args[0],opts)
            else:
                generate_spectrum_plots(args[0],opts)
            if opts.gui:
                from pylab import show
                print '=== Display interactive graphs ==='
                show()
        except Exception, e:
            logger.error('generate_spectrum_plots', exc_info=True)
