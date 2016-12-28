Usage: rss2rtl-power.py [options]

 Script to emulate a Radio Sky Spectrograph client application to capture
spectrograph output from a streaming server and write it in an ASCII .csv
format as described by rtl-power.  Two stream protocols are offered: Basic
Radio Sky Spectrograph(http://cygnusa.blogspot.com/2015/07/how-to-talk-to-
radio-sky-spectrograph.html) Binary rtl-power/Extended RSS
Spectrograph(https://github.com/myriadrf/RASDR/issues/16)

Options:
  --version          show program's version number and exit
  -h, --help         show this help message and exit
  -a A, --address=A  Specify the server address; default=localhost
  -p N, --port=N     Specify the port to connect to; default=8888
  -i, --info         Produce information about the connection only; do not
                     receive/parse scans
  -e, --extended     Interpret the extended RSS format
  --iso8601          Emit ISO-8601 Timestamps (YYYY-MM-DDTHH:MM:SS.nnnZ),
                     default=False
  --statistics       Dump statistical information to the stderr in comma-
                     separated-values format, default=False
  -v, --verbose      Verbose
  -q, --quiet        Do not display a connection message on stderr

 
Examples:

dos> rss2rtl-power.exe > standard.csv

This will start the client, connect to localhost:8888, emit the connection
string and begin reading 'standard' RSS protocol.  It will perform a local
timestamp and write the results to the file standard.csv.

dos> rss2rtl-power.exe -e --statistics > extended.csv

This will start the client, connect to localhost:8888, emit the connection
string and begin reading the 'extended' RSS protocol.  This protocol provides
the timestamp in the packet header and higher precision on the power spectral
density output.  Statistics will be calculated and emitted on the stderr while
the program runs (not in the output file).  The results will be written to the
file 'extended.csv'.


Notes:

The 'standard' RSS protocol is described here:
http://cygnusa.blogspot.com/2015/07/how-to-talk-to-radio-sky-spectrograph.html

The 'extended' RSS protocol is described here:
https://github.com/myriadrf/RASDR/issues/16

If you have python installed, you can also run the program with the python interpreter:

dos> python rss2rtl-power.py > output.csv

Should produce the same result as using the pre-compiled program.
