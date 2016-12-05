#!/bin/sh
PLOTCSV="python plotcsv.py"

function usage {
	cat << 'EOF'
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
EOF
}

# Original Formats since RASDRviewer 1.0.4
${PLOTCSV} FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 --info
${PLOTCSV} FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 -g
${PLOTCSV} FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 -g --atype=log --ptype=linear
${PLOTCSV} FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --info
${PLOTCSV} FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 -g
${PLOTCSV} FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 -g --atype=log --ptype=linear

# Format change in RASDRviewer 1.1.1
${PLOTCSV} FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 --info
${PLOTCSV} FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 -g
${PLOTCSV} FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 -g  --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 -g  --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 -g  --atype=log --ptype=linear
${PLOTCSV} FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --info
${PLOTCSV} FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 -g
${PLOTCSV} FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 -g --atype=log --ptype=linear

# Format change in RASDRviewer 1.2.2
${PLOTCSV} FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 --info
${PLOTCSV} FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 -g
${PLOTCSV} FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 -g --atype=log --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --info
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 -g
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 -g --atype=log --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --atype=log --ptype=linear
# Test option to also show background waveform in alternate color (red)
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --bplot
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --bplot --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --bplot --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 -g --bplot --atype=log --ptype=linear
# Test a degenerate condition of using the same file as its background
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 -g
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 -g --atype=linear --ptype=log
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 -g --atype=linear --ptype=linear
${PLOTCSV} FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 -g --atype=log --ptype=linear
