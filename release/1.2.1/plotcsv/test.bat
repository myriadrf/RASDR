@REM Usage: plotcsv.py <filename.csv> [options]
@REM 
@REM Options:
@REM   --version             show program's version number and exit
@REM   -h, --help            show this help message and exit
@REM   -a AVERAGE, --average=AVERAGE
@REM                         Specify the number of spectra to average for each
@REM                         plot; default=1
@REM   -b BACKGROUND, --background=BACKGROUND
@REM                         Specify a file to treat as background;it has the same
@REM                         format as the foreground file.  The file will be
@REM                         processed according to the same statistics as the
@REM                         foreground file.
@REM   -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
@REM   -d DELIMITER, --delimiter=DELIMITER
@REM                         Specify the delimiter character to use; default=,
@REM   -e, --excel           Indicate that .csv file is in RASDRviewer's "Excel-
@REM                         optimized" format
@REM   -k CALIBRATION, --calibration=CALIBRATION
@REM                         Specify the calibration constant for the system;
@REM                         0.0=uncal, default=0.000000
@REM   -l, --line            Perform line-by-line processing instead of loading
@REM                         entire file(s); NOTE: much slower but tolerates low
@REM                         memory better.
@REM   -v, --verbose         Verbose
@REM   -g, --gui             Create interactive PLOTS
@REM   -s SMOOTH, --smooth=SMOOTH
@REM                         Smooth final plot using a sliding window of N points
@REM   --fcenter=FC          Define the offset for the center frequency in Hz;
@REM                         default=0.000000
plotcsv.exe FFTOut-example.csv -a 3 -g
plotcsv.exe FFTOut-general.csv -s 20 -g
pause
