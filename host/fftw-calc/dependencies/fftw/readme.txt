FFTW

(http://www.fftw.org/install/windows.html)

Please download and extract 'fftw-3.3.4-dll32.zip' (MD5sum 757ce6282e7cab2dfa2dd40ba46f1c1f) from:
ftp://ftp.fftw.org/pub/fftw/fftw-3.3.4-dll32.zip

Into this folder.  you should have (at least) the following files here:

06/06/2015  06:44 AM            18,342 COPYING
06/06/2015  06:44 AM               863 COPYRIGHT
06/06/2015  06:44 AM            18,312 fftw3.h
06/06/2015  06:44 AM            23,959 libfftw3-3.def
06/06/2015  06:44 AM         2,228,302 libfftw3-3.dll

In addition, in order to support codeblocks compilation, I used MSVC++ lib command to produce 'libfftw3-3.lib', as I was unsuccessful in using 'dllwrap' from the codeblocks:: 12.11 mingw base (which we are using in windows at the moment).

dos> lib /def:libfftw3-3.def
