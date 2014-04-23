@REM Usage: plotcsv <filename.csv> [options]
@REM 
@REM Options:
@REM   -h, --help            show this help message and exit
@REM   -a AVERAGE, --average=AVERAGE
@REM                         Specify the number of spectra to average for each
@REM                         plot; default=1
@REM   -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
@REM   -d DELIMITER, --delimiter=DELIMITER
@REM                         Specify the delimiter character to use; default=,
@REM   -p, --paul            Indicate that .csv file is in Paul's format
@REM   -v, --verbose         Verbose
@REM 
plotcsv FFTOut-example.csv -p -v -a 3
pause
