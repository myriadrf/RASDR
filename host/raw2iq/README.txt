Convert RASDRstreamer raw stream into a I/Q output

Usage:
dist\x86\raw2iq.exe [OPTIONS]
Where:
  -i, --input-file FILE   Full path to file to be read or - for stdin
  -o, --output-file FILE  Full path to file to be written or - for stdout
  --iq-polarity N         Define starting I/Q polarity level
                            (0=I sample first, 1=Q sample first, default=0)
  --pps-polarity N        Define OTM/PPS polarity level
                            (0=active low, 1=active high, default=0)
  --flag-value HEX        Define FLAGs code for valid data
                            (two bits, default=3)
  --flag-mask HEX         Define FLAGs mask (two bits, default=3)
  -v                      Increment verbosity level
  --verbose N             Define verbosity level (0=quiet, 1=info, 2=trace)
  -h, --help              Print this help

Examples:

dist\x86\raw2iq.exe < RASDRviewer.raw > test.dat
Converts the .raw file to a binary interleaved 16-bit signed I/Q format file.

dist\x86\raw2iq.exe < RASDRviewer.raw -o test.csv
Converts the .raw file to an ASCII 16-bit signed I/Q comma separated file.

