@REM Usage: plotcsv.py <filename.csv> [options]
@REM 
@REM Options:
@REM   --version             show program's version number and exit
@REM   -h, --help            show this help message and exit
@REM   -a AVERAGE, --average=AVERAGE
@REM                         Specify the number of spectra to average for each plot; default=1
@REM   -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
@REM   -d DELIMITER, --delimiter=DELIMITER
@REM                         Specify the delimiter character to use; default=,
@REM   -e, --excel           Indicate that .csv file is in RASDRviewer's "Excel-optimized" format
@REM   -t, --datetime        Indicate that timestamps in the .csv file are in
@REM                         Excel's datetime format
@REM   -v, --verbose         Verbose
@REM
@REM If neither the -e or -t option is given, the program uses RASDRviewer's "General" format
plotcsv.exe FFTOut-example.csv -e -a 3
plotcsv.exe FFTOut-datetime.csv -t
plotcsv.exe FFTOut-general.csv
pause
