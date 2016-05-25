Convert RASDRstreamer raw stream into a I/Q output

Usage:
./raw2iq [OPTIONS]
Where:
  -i, --input-file FILE   Full path to file to be read or - for stdin
  -o, --output-file FILE  Full path to file to be written or - for stdout
  -h, --help              Print this help

Examples:

./raw2iq < RASDRviewer.raw > test.dat
Converts the .raw file to a binary interleaved 16-bit signed I/Q format file.

./raw2iq < RASDRviewer.raw -o test.csv
Converts the .raw file to an ASCII 16-bit signed I/Q comma separated file.
