# fftw-calc

This repository contains a platform-independent command line program to estimate the number of FLOPS (floating-point operations per second) required to compute streaming FFT (Fast Fourier Transform) according to sample rate.  It can be useful to determine of the computer system you wish to use for SDR (Software Defined Radio) is capable of handling the processing you wish to do.

The project was originally started as a learning exercise into setting up the CMake build system.

## Contents

The directory structure is as follows:

      <project>/src/
          CMakeLists.txt         - CMake configuration
          cpuid.{c,h}            - Alexander Yee's CPU capabilities code (modified)
          fftw-calc.c            - The program

### How to Compile

Using a shell or command prompt window, create a directory and launch CMake.  It should build an appropriate makefile or project which you can then use to build the software.  Ex:

      mkdir build
      cd build
      cmake ../src
      make
      ./fftw-calc --help

### Tested On

Linux/CentOS 6, FFTW 3.3.3, GCC 4.4.7
  - NB: this just worked as above
MacOS 10.8.5, MACPORTS, FFTW 2.1.5, GCC 4.7.3
  - NB: used $ CC=gcc-mp-4.7 CXX=g++-mp-4.7 cmake ../src
  - NB: used $ make
Win7  32-bit, FFTW 3.3.3, MSVC++ Express 2013
Win7  32-bit, FFTW 3.3.3, MSVC++ Express 2010
WinXP 32-bit, FFTW 3.3.3, MSVS 8 2005
  - NB: ran 'lib /def:libfftw3-3.def' in the ../dependencies/fftw
  - NB: used cmd> cmake ../src
  - NB: used cmd> msbuild fftwcalc.sln /P:Configuration=Release
  - NB: beware, after I installed MSVC++ Express 2013, the commandline for 2010 broke but I could still build in the GUI -- cmake finds registry entries?
Win7 32-bit, FFTW 3.3.3, MinGW 3.20
  - NB: used cmd> cmake -G "MinGW Makefiles" ../src
  - NB: used cmd> mingw32-make
Win7 32-bit, FFTW 3.3.3, Code::Blocks 12.11/MinGW 3.20
  - NB: used cmd> cmake -G "CodeBlocks - MinGW Makefiles" ../src
  - NB: used cmd> c:\codeblocks\codeblocks.exe --rebuild --target=fftw-calc --no-batch-window-close fftwcalc.cbp
  - NB: depending on your environment variables and path settings, you may also need to do something like:
  -     cmd> cmake -G "CodeBlocks - MinGW Makefiles" -DCMAKE_C_COMPILER=c:/codeblocks/MinGW/bin/gcc.exe -DCMAKE_CXX_COMPILER=c:/codeblocks/MinGW/bin/g++.exe -DCMAKE_MAKE_PROGRAM=c:/codeblocks/MinGW/bin/mingw32-make.exe ../src
  -     with 'c:\codeblocks\' being where I installed Code::Blocks 12:11
  -     in this case, the compiler had OpenMP disabled (it wouldnt recognize it)

### TODO

- Explore use of [mingw-w64](http://mingw-w64.org/doku.php)

### References

- Matteo Frigo and Steven G. Johnson. [FFTW](http://www.fftw.org/fftw3_doc/Using-Plans.html#Using-Plans)
- Pioneer Hill Software, LLC [FFT Overlap Processing](https://www.spectraplus.com/DT_help/overlap_percentage.htm)
- jonolafur [cli-fft](http://sourceforge.net/projects/cli-fft/)
- Pau Garcia i Quiles [Learning CMake](http://www.elpauer.org/stuff/learning_cmake.pdf)
- Alexander J. Yee [FLOPS Project](https://github.com/Mysticial/Flops)
- [rf-sampler](http://sourceforge.net/p/rf-sampler/code/HEAD/tree/trunk/software/fftw-calc/)
