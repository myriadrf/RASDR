Usage: plotcsv.py <filename.csv> [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -a AVERAGE, --average=AVERAGE
                        Specify the number of spectra to average for each
                        plot; default=1
  -b BACKGROUND, --background=BACKGROUND
                        Specify how to perform background subtraction;if the
                        word automatic is used, then the background will be
                        takenfrom the average of all lines in the file.
                        Otherwise, it is takenas a file to process.  The file
                        must have the same frequency plan as the foreground
                        file.
  -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
  -d DELIMITER, --delimiter=DELIMITER
                        Specify the delimiter character to use; default=,
  -e, --excel, --localtime
                        Indicate that .csv file has timestamps in
                        RASDRviewer's "LocalTime" format
  -k CALIBRATION, --calibration=CALIBRATION
                        Specify the calibration constant for the system;
                        0.0=uncal, default=0.000000
  -l, --line            Perform line-by-line processing instead of loading
                        entire file(s); NOTE: much slower but tolerates low
                        memory better.
  -i, --info            Produce information about a file only; do not generate
                        any plots
  -v, --verbose         Verbose
  -g, --gui             Create interactive PLOTS
  -s SMOOTH, --smooth=SMOOTH
                        Smooth final plot using a sliding window of N points
  --fcenter=FC          Define the offset for the center frequency in Hz;
                        default=0.000000
  --hold                Perform a maximum value HOLD during averaging and plot
                        it as a second line
  --format=FORMAT       Specify the RASDRviewer .csv output format to
                        interpret; default=1.2.2

Examples:

This shows how Paul's "LocalTime" format can be processed with averaging

dos> python plotcsv.py FFTOut-format-1.2.2-localtime.csv --localtime -v -a 3
FFTOut-format-1.2.2-localtime.csv.date=05/10/15 ('UTC-4', '') (2015-05-10 10:35:51.512000)
FFTOut-format-1.2.2-localtime.csv.time=4
FFTOut-format-1.2.2-localtime.csv.freq=(127,) (scale=0.001000)
range (MHz)=[-984.375000,984.375000]
zero index=63
frequency bins=127
bandwidth/bin (Hz)=15501968.503937
start=2015-05-10 10:35:51.512000
end  =2015-05-10 10:35:51.714000
inter-frame period=0.069000 sec (14 fr/s)
averaging=3
loading FFTOut-format-1.2.2-localtime.csv...
line 0/4 max@72 val=18.624000
line 1/4 max@72 val=18.454100
line 2/4 max@72 val=18.363900
-> plot min=-1.000000 max=20.000000
Saved spectrum-2015_May_10_10_35_51.png
line 3/4 max@72 val=18.335300
-> plot min=-1.000000 max=20.000000
Saved spectrum-2015_May_10_10_35_51.png

Here is the general format output as another example:

dos> python plotcsv.py FFTout-format-1.2.2-universaltime.csv -v
FFTout-format-1.2.2-universaltime.csv.date=05/10/15 UTC (2015-05-10 14:35:03.537000+00:00)
FFTout-format-1.2.2-universaltime.csv.time=4
FFTout-format-1.2.2-universaltime.csv.freq=(16383,) (scale=0.001000)
range (MHz)=[-0.999878,0.999878]
zero index=8191
frequency bins=16383
bandwidth/bin (Hz)=122.062862
start=2015-05-10 14:35:03.537000+00:00
end  =2015-05-10 14:35:04.220000+00:00
inter-frame period=0.251000 sec (4 fr/s)
averaging=1
loading FFTout-format-1.2.2-universaltime.csv...
line 0/4 max@8192 val=15.054600
-> plot min=-27.000000 max=17.000000
Saved spectrum-2015_May_10_14_35_03.png
line 1/4 max@8192 val=15.017500
-> plot min=-27.000000 max=17.000000
Saved spectrum-2015_May_10_14_35_03.png
line 2/4 max@8192 val=15.003400
-> plot min=-27.000000 max=17.000000
Saved spectrum-2015_May_10_14_35_03.png
line 3/4 max@8192 val=15.019000
-> plot min=-27.000000 max=17.000000
Saved spectrum-2015_May_10_14_35_04.png


NOTES:

You can use the pre-compiled version of the above scripted commands:

dos> plotcsv.exe FFTOut-format-1.2.2-localtime.csv --localtime -a 3
dos> plotcsv.exe FFTout-format-1.2.2-universaltime.csv

Should produce the same result as using the scripted program.

You can also use the 'test.bat' to setup the parameters for the executable
so you can run it from the Windows GUI by clicking it

Several versions of RASDRviewer had produced different header formats that
need to be parsed differently.  The --format option allows you to specify
this if you are dealing with older data files.  Currently valid options are:
1.0.4, 1.1.1, 1.2.2 (current)

BUGS:

1) the cancel DC option isnt effective as it seems the highest energy is 2 bins away from actual Frequency 0
2) The file formats need to be described
3) The 'append' feature in RASDRviewer that adds a new frequency header to the same file is not supported correctly