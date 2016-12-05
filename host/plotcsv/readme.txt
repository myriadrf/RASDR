usage: plotcsv.py [-h] [--version] [-v | -q] [-a N] [-b PATH] [-c] [-d CHAR]
                  [-e] [-k CONST] [-l] [-i] [--statistics PATH] [--debug] [-g]
                  [-s N] [--fcenter FC] [--hold] [--bplot] [--ptype TYPE]
                  [--atype TYPE] [--format X.Y.Z]
                  [file [file ...]]

Post-Process RASDRviewer/RASDRproc spectrum data output files

positional arguments:
  file

optional arguments:
  -h, --help            show this help message and exit
  --version             show program's version number and exit
  -v, --verbose         Turn on verbose output
  -q, --quiet           Suppress progress messages
  -a N, --average N     Specify the number of spectra to average for each plot
  -b PATH, --background PATH
                        Specify how to perform background subtraction;if the
                        word automatic is used, then the background will be
                        takenfrom the average of all lines in the file.
                        Otherwise, it is takenas a file to process. The file
                        must have the same frequency plan as the foreground
                        file.
  -c, --cancel-dc       Cancel out component at frequency bin for 0Hz
  -d CHAR, --delimiter CHAR
                        Specify the delimiter character to use"
  -e, --localtime       Indicate that .csv file has timestamps in
                        RASDRviewer's "LocalTime" format
  -k CONST, --calibration CONST
                        Specify the calibration constant for the system;
                        0.0=uncal
  -l, --line            Perform line-by-line processing instead of loading
                        entire file(s); NOTE: much slower but tolerates low
                        memory better.
  -i, --info            Produce information about a file only; do not generate
                        any plots
  --statistics PATH     Dump statistical information to a file in comma-
                        separated-values format
  --debug               Drop into ipython shell at predefined point(s) to
                        debug the script
  -g, --gui             Create interactive PLOTS
  -s N, --smooth N      Smooth final plot using a sliding window of N points
  --fcenter FC          Define the offset for the center frequency in Hz
  --hold                Perform a maximum value HOLD during averaging and plot
                        it as a second line
  --bplot               If using background file, choose whether to plot the
                        background reference in a difffert color
  --ptype TYPE          Control plot vertical scale (linear or log)
  --atype TYPE          Control averaging method (linear or log)
  --format X.Y.Z        Specify the RASDRviewer .csv output format to
                        interpret

NOTES:

Edit the 'go.bat' provided to assign the path to the file and any needed options.  Then double-click the go.bat file.

If you have python installed, you can also run the program with the python interpreter:

dos> python plotcsv.py FFTOut-2msps-500avg-srh77ca.csv -a 120

Should produce the same result as using the pre-compiled program.

Several versions of RASDRviewer had produced different header formats that
need to be parsed differently.  The --format option allows you to specify
this if you are dealing with older data files.  Currently valid options are:
1.0.4, 1.1.1, 1.2.2 (current)

The file 'environment.yml' provides an easy way to generate a python virtual environment that has the needed dependencies.  Using Anaconda, execute:

$ conda env create -f environment.yml
$ source activate rasdr
-or-
dos> activate rasdr

See: https://docs.continuum.io/anaconda/install.html
See also: http://conda.pydata.org/docs/using/envs.html#use-environment-from-file

BUGS:

1) the cancel DC option isnt effective as it seems the highest energy is 2 bins away from actual Frequency 0
2) The file formats need to be described
3) The 'append' feature in RASDRviewer that adds a new frequency header to the same file is not supported correctlyUsage: plotcsv.py <filename.csv> [options]
