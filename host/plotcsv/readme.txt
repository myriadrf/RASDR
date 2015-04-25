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
  -e, --excel           Indicate that .csv file is in RASDRviewer's "Excel-
                        optimized" format
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

Examples:

This shows how Paul's "Excel" format can be processed with averaging

dos> python plotcsv.py FFTOut-example.csv -e -v -a 3
range (MHz)=[-4.922000,4.922000]
zero index=63
frequency bins=127
bandwidth/bin (Hz)=77511.811024
start=2014-04-23 22:31:37.527000
end  =2014-04-23 22:31:37.567000
inter-frame period=0.040000 sec (25 fr/s)
averaging=3
loading FFTOut-example.csv...
Saved spectrum-2014_Apr_23_22_31_37.png

Here is the general format output as another example:

dos> python plotcsv.py FFTOut-general.csv -v
range (MHz)=[-4.981000,4.981000]
zero index=32764
frequency bins=65535
bandwidth/bin (Hz)=152.010376
start=2014-04-25 03:11:54.535000+00:00
end  =2014-04-25 03:11:55.404000+00:00
inter-frame period=0.869000 sec (1 fr/s)
averaging=1
loading FFTOut-general.csv...
Saved spectrum-2014_Apr_25_03_11_54.png
Saved spectrum-2014_Apr_25_03_11_55.png


NOTES:

You can use the pre-compiled version of the above scripted commands:

dos> plotcsv.exe FFTOut-example.csv -e -a 3
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