# raw2iq
A platform-independent command line program to convert the RAW files produced by RASDRstreamer into interleaved 16-bit I,Q data files (binary) or comma-separated format (ascii).

The implementation is intended to show how to use OpenMP to distribute processing tasks among available CPU cores efficiently, be completely platform neutral, as well as being able to handle arbitrarily large files by streaming them into the processing.

## Contents

The directory structure is as follows:

      <project>/src/
          CMakeLists.txt         - CMake configuration
          raw2iq.c               - The program

### How to Compile

Using a shell or command prompt window, create a directory and launch CMake.  It should build an appropriate makefile or project which you can then use to build the software.  Ex:

      mkdir build
      cd build
      cmake ../src
      
To execute on Linux/MinGW/etc:

      make
      ./raw2iq --help

To execute on Windows/MSVC/etc:

      msbuild raw2iq.sln /P:Configuration=Release
      Release\raw2iq --help

### Tested On

MacOS 10.10.5, MACPORTS 2.3.4, LLVM 7.0.2
  - NB: does not support OpenMP

MacOS 10.10.5, MACPORTS 2.3.4, GCC 4.8.5
  - NB: used $ CC=gcc-mp-4.8 CXX=g++-mp-4.8 cmake ../src
  - NB: used $ make

### TODO

- Actually implement the code; this is just a template

### References

- Blaise Barney [OpenMP](https://computing.llnl.gov/tutorials/openMP/)
- Ruud van der Pas [Getting OpenMP Up To Speed](http://www.compunity.org/training/tutorials/4%20OpenMP_and_Performance.pdf)
- Hristo Lliev [OpenMP: for schedule](http://stackoverflow.com/a/10852852/2259515)
- Hristo Lliev [In an OpenMP parallel code, ...](http://stackoverflow.com/a/11579987/2259515)
- Yonghong Yan [Introducton to OpenMP 4.0](http://openmp.org/sc13/OpenMP4.0_Intro_YonghongYan_SC13.pdf)
