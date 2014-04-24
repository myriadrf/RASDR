#import math import time
import sys
import datetime
import pytz
import numpy as np
from matplotlib import pyplot as plt

DEF_VERSION = '1.0.5'	# to match RASDRviewer version
DEF_DELIM   = ','
DEF_AVERAGE = 1

def excel2dt(et):
    # http://stackoverflow.com/questions/1703505/excel-date-to-unix-timestamp
    # http://stackoverflow.com/questions/3682748/converting-unix-timestamp-string-to-readable-date-in-python
    ts = (et - 25569)*86400 # 25569 is days since 1900-01-01
    ts = ts + (4*60*60)     # timezone EST5EDT return
    return datetime.datetime.fromtimestamp(float(ts))

def dt2excel(dt,tz=None):
    # http://stackoverflow.com/questions/9574793/how-to-convert-a-python-datetime-datetime-to-excel-serial-date-number
    # http://stackoverflow.com/questions/4530069/python-how-to-get-a-value-of-datetime-today-that-is-timezone-aware
    dte = datetime.datetime(1899, 12, 29, tzinfo=pytz.timezone(tz)) if tz else datetime.datetime(1899, 12, 29)
    delta = dt - dte    # set w/r/t excel2dt() date; NB: do not know why this must be set 3 days earlier
    return float(delta.days) + (float(delta.seconds) / 86400)

def generate_spectrum_plots(filename,opts):
    if opts.excel:
        # this is Paul's "Excel-optimized" .csv format
        # http://stackoverflow.com/questions/13311471/skip-a-specified-number-of-columns-with-numpy-genfromtxt
        # http://stackoverflow.com/questions/466345/converting-string-into-datetime
        # http://stackoverflow.com/questions/698223/how-can-i-parse-a-time-string-containing-milliseconds-in-it-with-python
        #
        # yes, I know it is very silly to go into a datetime, then down into an excel datetime
        # only to go back to a datetime to plot everything.

        from StringIO import StringIO

        f=open(filename,'r')
        key=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='str')
        d=key[4].replace('"','') if len(key) > 4 else '00/00/00'
        tz=key[6].replace('"','') if len(key) > 7 else 'UTC'
        # translate strange labels from RASDRviewer_W_1_0_5
        tz=tz.replace('UT20','US/Eastern')
        tz=tz.replace('UT','UTC')
        ## second line: frequency bin information
        freq=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='float')
        freq=freq[1:]           # remove the 1st column, as it is a 'nan' when interpreted as a 'float'
        ## third line-to-end: extract first *column* as text
        t=np.genfromtxt(f,delimiter=opts.delimiter,usecols=[0],dtype='str')
        f.seek(0)               # start over
        f.readline()            # dump the first line
        f.readline()            # dump the second line
        ## third line-to-end: extract data set
        data = np.genfromtxt(f,delimiter=opts.delimiter,usecols=range(0,freq.shape[0]+1),dtype='float') # last column is junk
        for i in range(1,t.shape[0]):
            # translate HH:MM:SS:ms into HH:MM:SS.ms
            if t[i].count(':') > 2:
                a,x,b = t[i].rpartition(':')
            else:
                a = t[i]
                b = '0'
            ts=a+'.'+b
            data[i,0] = dt2excel(datetime.datetime.strptime(d+'T'+ts, '%m/%d/%yT%H:%M:%S.%f'))
        time = data[1:,0]       # datetime values
        spec = data[1:,1:]      # spectral information
    elif opts.datetime:
        # this is the "Excel-datetime" .csv format (proposed for RASDRviewer_W_1_0_4, but not implemented)
        data = np.genfromtxt(filename,delimiter=opts.delimiter)
        freq = data[0,1:]       # frequency bins
        time = data[1:,0]       # datetime values
        spec = data[1:,1:]      # spectral information
    else:
        # this is the "Extended" .csv format produced by RASDRviewer_W_1_0_5
        from StringIO import StringIO
        from dateutil import parser

        f=open(filename,'r')
        ## first line: key-value pairs
        key=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='str')
        d=key[4].replace('"','') if len(key) > 4 else '00/00/00'
        tz=key[6].replace('"','') if len(key) > 7 else 'UTC'
        # translate strange labels from RASDRviewer_W_1_0_5
        tz=tz.replace('UT20','US/Eastern')
        tz=tz.replace('UT','UTC')
        ## second line: frequency bin information
        freq=np.genfromtxt(StringIO(f.readline()),delimiter=opts.delimiter,dtype='float')
        freq=freq[1:]           # remove the 1st column, as it is a 'nan' when interpreted as a 'float'
        ## third line-to-end: extract first *column* as text
        t=np.genfromtxt(f,delimiter=opts.delimiter,usecols=[0],dtype='str')                # 1st column are *almost* ISO-8601 datetime strings
        f.seek(0)               # start over
        f.readline()            # dump the first line
        f.readline()            # dump the second line
        ## third line-to-end: extract data set
        data = np.genfromtxt(f,delimiter=opts.delimiter,usecols=range(0,freq.shape[0]+1),dtype='float') # last column is junk
        for i in range(1,t.shape[0]):
            a,x,b = t[i].rpartition(':')  # deal with Paul's 'YYYY-MM-DDTHH:MM:SS:sssZ' format in RASDRviewer_W_1_0_5
            data[i,0] = dt2excel(parser.parse(a+'.'+b),tz=tz)
        time = data[1:,0]       # datetime values
        spec = data[1:,1:]      # spectral information

    print 'time=',time.shape
    print 'freq=',freq.shape
    print 'spec=',spec.shape

    s_a  = spec
    ts_a = time
    fMHz = freq
    zidx = np.searchsorted(fMHz,0)
    nbin = len(fMHz)
    lastrow = s_a.shape[0]-1

    if opts.verbose:
        print 'spectra=',s_a.shape[0]
        print 'range (MHz)','=[',fMHz.min(),',',fMHz.max(),']'
        print 'zero index=',zidx
        print 'frequency bins=',nbin
        if s_a.shape[0] > 2:
            delta = excel2dt(ts_a[lastrow]) - excel2dt(ts_a[lastrow-1])
            print 'start=',excel2dt(ts_a[0])
            print 'end  =',excel2dt(ts_a[lastrow])
            print 'seconds between samples=',delta.seconds
        print 'averaging=',opts.average

    acc = np.zeros(nbin)
    n   = 0
    for fr in range(np.shape(s_a)[0]):
        dt = excel2dt(ts_a[fr])
        s = s_a[fr]
        if opts.canceldc:
            if opts.verbose:
                print 'Cancel DC: frq',fMHz[zidx-4:zidx+5]
                print 'Cancel DC: b4 ',s[zidx-4:zidx+5]
            a = (s[zidx-1] + s[zidx+1])/2.0
            if a < s[zidx]:
                s[zidx] = a
            if opts.verbose:
                print 'Cancel DC: ftr',s[zidx-4:zidx+5]
        if n == 0:
            tstart = dt.strftime('%Y-%m-%dT%H:%M:%S')
        n    = n+1
        acc += s_a[fr]
        if n >= opts.average or fr == lastrow:
            s   = acc / float(n)
            min = np.floor(s.min())-1.0
            max = np.ceil(s.max())+1.0
            tstop = dt.strftime('%Y-%m-%dT%H:%M:%S')
            if n > 1:
                title = 'Collected between %s and %s\nAveraged over %d frames'%(tstart,tstop,n)
            else:
                title = 'Collected at %s'%tstop

            plt.plot(fMHz,s,hold=False)
            plt.axis([fMHz[0],fMHz[nbin-1],min,max])
            plt.xlabel('frequency (MHz)')
            plt.ylabel('spectral power (arbitrary unit)')
            plt.title(title)

            name = 'spectrum-%s.png'%dt.strftime('%Y_%b_%d_%H_%M_%S')
            plt.savefig(name)
            print 'Saved '+name

            acc = np.zeros(nbin)
            n   = 0

if __name__ == '__main__':
    from optparse import OptionParser

    p = OptionParser(version=DEF_VERSION)
    p.set_usage('plotcsv.py <filename.csv> [options]')
    p.set_description(__doc__)
    p.add_option('-a', '--average', dest='average', type='int', default=DEF_AVERAGE,
        help='Specify the number of spectra to average for each plot; default=%d'%DEF_AVERAGE)
    p.add_option('-c', '--cancel-dc', dest='canceldc', action='store_true', default=False,
        help='Cancel out component at frequency bin for 0Hz')
    p.add_option('-d', '--delimiter', dest='delimiter', type='str', default=DEF_DELIM,
        help='Specify the delimiter character to use; default=%s'%DEF_DELIM)
    p.add_option('-e', '--excel', dest='excel', action='store_true', default=False,
        help='Indicate that .csv file is in RASDRviewer\'s "Excel-optimized" format')
    p.add_option('-t', '--datetime', dest='datetime', action='store_true', default=False,
        help='Indicate that timestamps in the .csv file are in Excel\'s datetime format')
    p.add_option('-v', '--verbose', dest='verbose', action='store_true', default=False,
        help='Verbose')
    opts, args = p.parse_args(sys.argv[1:])

    if args==[]:
        print 'Please specify a filename. Run with the -h flag to see all options.\n'
    else:
        generate_spectrum_plots(args[0],opts)
