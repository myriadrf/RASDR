Usage: plotcsv.py <filename.csv> [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -a AVERAGE, --average=AVERAGE
                        Specify the number of spectra to average for each plot; default=1
  -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
  -d DELIMITER, --delimiter=DELIMITER
                        Specify the delimiter character to use; default=,
  -e, --excel           Indicate that .csv file is in RASDRviewer's "Excel-optimized" format
  -t, --datetime        Indicate that timestamps in the .csv file are in
                        Excel's datetime format
  -v, --verbose         Verbose

Examples:

This shows how Paul's "Excel" format can be processed with averaging

dos> python plotcsv.py FFTOut-example.csv -e -v -a 3
time= (2,)
freq= (127,)
spec= (2, 127)
spectra= 2
range (MHz) =[ -4.922 , 4.922 ]
zero index= 63
frequency bins= 127
averaging= 3
Saved spectrum-2014_Apr_24_22_31_37.png

The below shows how the alternate format can be processed (without averaging):

dos> python plotcsv.py FFTOut-datetime.csv -t -v
time= (3,)
freq= (16383,)
spec= (3, 16383)
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

Here is the general format output as another example:

dos> python plotcsv.py FFTOut-general.csv -v
time= (2,)
freq= (65535,)
spec= (2, 65535)
spectra= 2
range (MHz) =[ -4.981 , 4.981 ]
zero index= 32764
frequency bins= 65535
averaging= 1
Saved spectrum-2014_Apr_26_03_11_54.png
Saved spectrum-2014_Apr_26_03_11_55.png


NOTES:

You can use the pre-compiled version of the above scripted commands:

dos> plotcsv.exe FFTOut-example.csv -e -a 3
dos> plotcsv.exe FFTOut-datetime.csv -t
dos> plotcsv.exe FFTOut-general.csv

Should produce the same result as using the scripted program.

You can also use the 'test.bat' to setup the parameters for the executable
so you can run it from the Windows GUI by clicking it


BUGS:

1) the cancel DC option isnt effective as it seems the highest energy is 2 bins away from actual Frequency 0
2) when run from the executable, the verbose option doesnt seem to produce an output
3) The '-e' and '-t' options do not work together as they should, '-e' takes priority
4) The file formats need to be described
5) The 'append' feature in RASDRviewer that adds a new frequency header to the same file is not supported correctly
