@REM Usage: plotcsv.exe <filename.csv> [options]
@REM 
@REM Options:
@REM   --version             show program's version number and exit
@REM   -h, --help            show this help message and exit
@REM   -a AVERAGE, --average=AVERAGE
@REM                         Specify the number of spectra to average for each
@REM                         plot; default=1
@REM   -b BACKGROUND, --background=BACKGROUND
@REM                         Specify how to perform background subtraction;if the
@REM                         word automatic is used, then the background will be
@REM                         takenfrom the average of all lines in the file.
@REM                         Otherwise, it is taken as a file to process.  The file
@REM                         must have the same frequency plan as the foreground
@REM                         file.
@REM   -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
@REM   -d CHAR, --delimiter=CHAR
@REM                         Specify the delimiter character to use; default=","
@REM   -e, --excel, --localtime
@REM                         Indicate that .csv file has timestamps in
@REM                         RASDRviewer's "LocalTime" format
@REM   -k CONST, --calibration=CONST
@REM                         Specify the calibration constant for the system;
@REM                         0.0=uncal, default=0.0
@REM   -l, --line            Perform line-by-line processing instead of loading
@REM                         entire file(s); NOTE: much slower but tolerates low
@REM                         memory better.
@REM   -i, --info            Produce information about a file only; do not generate
@REM                         any plots
@REM   --statistics=PATH     Dump statistical information to a file in comma-
@REM                         separated-values format, default=none
@REM   -v, --verbose         Verbose
@REM   -g, --gui             Create interactive PLOTS
@REM   -s SMOOTH, --smooth=SMOOTH
@REM                         Smooth final plot using a sliding window of N points
@REM   --fcenter=FC          Define the offset for the center frequency in Hz;
@REM                         default=0.0
@REM   --hold                Perform a maximum value HOLD during averaging and plot
@REM                         it as a second line
@REM   --bplot               If using background file, choose whether to plot the
@REM                         background reference in a difffert color;
@REM                         default=False
@REM   --ptype=PTYPE         Control plot vertical scale (linear or log);
@REM                         default=log
@REM   --atype=ATYPE         Control averaging method (linear or log); default=log
@REM   --format=FORMAT       Specify the RASDRviewer .csv output format to
@REM                         interpret; default=1.2.2

@REM select how the program is started.  Choices are: 'python plotcsv.py', 'plotcsv.exe'
@set PLOTCSV=python plotcsv.py

@REM define files
@set FOREGROUND="FFTOut-2msps-500avg-srh77ca.csv"
@set BACKGROUND=automatic
@set OPTIONS=--smooth=5 --fcenter=407.5

%PLOTCSV% %FOREGROUND% %OPTIONS% -a 120 --info
%PLOTCSV% %FOREGROUND% %OPTIONS% -a 120 --background=%BACKGROUND% -g
@pause
