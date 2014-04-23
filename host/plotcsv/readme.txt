Usage: plotcsv.py <filename.csv> [options]

Options:
  -h, --help            show this help message and exit
  -a AVERAGE, --average=AVERAGE
                        Specify the number of spectra to average for each
                        plot; default=1
  -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
  -d DELIMITER, --delimiter=DELIMITER
                        Specify the delimiter character to use; default=,
  -p, --paul            Indicate that .csv file is in Paul's format
  -v, --verbose         Verbose

Examples:

This shows how Paul's format can be processed with averaging

dos> python plotcsv.py FFTOut-example.csv -p -v -a 3
spectra= 3
range (MHz) =[ -5.0 , 5.0 ]
zero index= 8183
frequency bins= 16383
start= 2014-03-13 07:02:27
end  = 2014-03-13 07:02:29
seconds between samples= 1
averaging= 3
Saved spectrum-2014_Mar_13_07_02_29.png

The below shows how the alternate format can be processed (without averaging):

dos> python plotcsv.py FFTOut-datetime.csv -v
spectra= 3
range (MHz) =[ -4.998779297 , 5.0 ]
zero index= 8190
frequency bins= 16383
start= 2014-03-13 07:02:27.000004
end  = 2014-03-13 07:02:29
seconds between samples= 1
averaging= 1
Saved spectrum-2014_Mar_13_07_02_27.png
Saved spectrum-2014_Mar_13_07_02_27.png
Saved spectrum-2014_Mar_13_07_02_29.png


NOTES:

You can use the pre-compiled version of the above scripted commands:

dos> plotcsv.exe FFTOut-example.csv -p -a 3
dos> plotcsv.exe FFTOut-datetime.csv

Should produce the same result as using the scripted program.

You can also use the 'test.bat' to setup the parameters for the executable
so you can run it from the Windows GUI by clicking it


BUGS:

1) the cancel DC option isnt effective as it seems the highest energy is 2 bins away from actual Frequency 0
2) when run from the executable, the verbose option doesnt seem to produce an output
