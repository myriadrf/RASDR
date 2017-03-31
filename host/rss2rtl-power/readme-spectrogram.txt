rss-power.py is the master program for both rss2rtl.py and spectrogram.py.
The spectrogram display will be started by default--to disable it, specify -m print.

Dependencies:
 -- Python 3.5+ (well actually, python 2.7.5+ also works)
 -- Numpy 1.11.1 (well actually, numpy 1.7.1+ also works)
 -- Pygame 1.9.1
 -- Matplotlib 1.5.1
 -- rasdrproc 0.2.5.4+ (extended RSS producer, with fixed frequency plan)

The spectrogram uses the extended RSS format, which is enabled by default.
The spectrogram displays 3 temporal streams, left to right;
  a) realtime, where a row is a received scan
  b) 10x, where a row represents the average of 10 scans
  c) 100x, where a row represents the average of 100 scans

If the streams generator is producing 64 frames a second, for example, then 600 rows (the default) in the 100x stream represents about 15 1/2 minutes
and the 10x stream about 94 seconds.

Mouse pointer hovering over any stream where there are rendered pixels results in the frequency of that channel, the amplitude (PSD), and the SNR displayed below the 
color key.  The SNR calculation is a quick estimate using the average of the two lowest values from the 3 channels above and below the channel of interest as the noise
value ( SNR = signal - noise).

The color key uses built in Matplotlib color maps or .csv colormaps (-f colormapfile.csv) to visualize amplitudes; if users do not specify anything, the default colormap is magma.
If the range of amplitudes is small, users may specify min and max db values using -d and -x respectively to better highlight differences. 

Perceptually uniform color maps (files) obtained from two sources below.
Matplotlib has a set of colormaps from which to choose, see spectrogram.assign_matplotlib_colormap() for perceptually uniform colormaps and all colormaps.

http://peterkovesi.com/projects/colourmaps/
isoluminant_cgo_70_c39_rgb_256.csv

http://www.kennethmoreland.com/color-advice/
extended-black-body-0128.csv
smooth-cool-warm-table-byte-0256.csv

Inovcation and usage:
python rss-power.py --help
Usage: rss-power.py -m [print,spectrogram] [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -a A, --address=A     Specify the server address; default=localhost
  -p N, --port=N        Specify the port to connect to; default=8888
  -i, --info            Produce information about the connection only; do not
                        receive/parse scans
  -e, --extended        Interpret the extended RSS format, default=True
  --iso8601             Emit ISO-8601 Timestamps (YYYY-MM-DDTHH:MM:SS.nnnZ),
                        default=False
  --statistics          Dump statistical information to the stderr in comma-
                        separated-values format, default=False
  -v, --verbose         Verbose
  -q, --quiet           Do not display a connection message on stderr,
                        default=False
  -c, --colormap        Colormap from matplotlib color maps, default=magma
  -f COLORMAPFILE, --colormap-file=COLORMAPFILE
                        Colormap from file overrrides -c
  -m MODE, --mode=MODE  operation mode print or spectrogram,
                        default=spectrogram
  -d DB_MIN, --db-min=DB_MIN
                        minimum dB for color assignment, default=-30
  -x DB_MAX, --db-max=DB_MAX
                        maximum dB for color assignment, default=30
						
Example invocation:
python rss-power.py -f smooth-cool-warm-table-byte-0256.csv -d -5 -x 5

TO DO:
1.  Trigger record on threshold similar to rasdrproc
2.  Allow graphic manipulation of min and max db
3.  In addition to displaying dB and SNR, show the min and max dB found in the row where the mouse is pointing
