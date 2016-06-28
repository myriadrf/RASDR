Usage: plotcsv.py <filename.csv> [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -a N, --average=N     Specify the number of spectra to average for each
                        plot; default=1
  -b PATH, --background=PATH
                        Specify how to perform background subtraction;if the
                        word automatic is used, then the background will be
                        takenfrom the average of all lines in the file.
                        Otherwise, it is taken as a file to process.  The file
                        must have the same frequency plan as the foreground
                        file.
  -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
  -d CHAR, --delimiter=CHAR
                        Specify the delimiter character to use; default=","
  -e, --excel, --localtime
                        Indicate that .csv file has timestamps in
                        RASDRviewer's "LocalTime" format
  -k CONST, --calibration=CONST
                        Specify the calibration constant for the system;
                        0.0=uncal, default=0.0
  -l, --line            Perform line-by-line processing instead of loading
                        entire file(s); NOTE: much slower but tolerates low
                        memory better.
  -i, --info            Produce information about a file only; do not generate
                        any plots
  --statistics=PATH     Dump statistical information to a file in comma-
                        separated-values format, default=none
  -v, --verbose         Verbose
  -g, --gui             Create interactive PLOTS
  -s N, --smooth=N      Smooth final plot using a sliding window of N points
  --fcenter=FC          Define the offset for the center frequency in Hz;
                        default=0.0
  --hold                Perform a maximum value HOLD during averaging and plot
                        it as a second line
  --bplot               If using background file, choose whether to plot the
                        background reference in a difffert color;
                        default=False
  --ptype=TYPE          Control plot vertical scale (linear or log);
                        default=log
  --atype=TYPE          Control averaging method (linear or log); default=log
  --format=X.Y.Z        Specify the RASDRviewer .csv output format to
                        interpret; default=1.2.2

NOTES:

Edit the 'go.bat' provided to assign the path to the file and any needed options.  Then double-click the go.bat file.

If you have python installed, you can also run the program with the python interpreter:

dos> python plotcsv.py FFTOut-2msps-500avg-srh77ca.csv -a 120

Should produce the same result as using the pre-compiled program.

Several versions of RASDRviewer had produced different header formats that
need to be parsed differently.  The --format option allows you to specify
this if you are dealing with older data files.  Currently valid options are:
1.0.4, 1.1.1, 1.2.2 (current)


BUGS:

1) the cancel DC option isnt effective as it seems the highest energy is 2 bins away from actual Frequency 0
2) The file formats need to be described
3) The 'append' feature in RASDRviewer that adds a new frequency header to the same file is not supported correctlyUsage: plotcsv.py <filename.csv> [options]
