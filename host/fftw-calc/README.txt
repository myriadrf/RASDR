Usage:
fftw-calc.exe [N [FS [WIN [EST]]]]
Where:
	N:	FFT length in points (default 1024)
	FS:	Sampling frequency in Hz (default 1e6/1MHz)
	WIN:	Overlap Window in % (default 0%/no overlap)
	EST:	Estimate(1) or Measure(0) (default 0/measure)

Examples:

fftw-calc.exe 32768 28e6 0.1 1
Calculates the FFT plan and estimates operations for a spectrum analyzer
operating at 28MHz (complex samples) with an FFT size of 32K and 10% overlap.

fftw-calc.exe 32K 28MHz 0.1 0
Similar to above, but illustrates the use of the suffixes, and forces measurement

