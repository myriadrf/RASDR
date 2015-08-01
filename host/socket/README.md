# SOCKET

This repository contains a platform-independent command line program implement a TCP/IP client and server.

It is intended to use as a tool to embed a common performing networking support with reduced effort into C,C++ programs with no external library dependencies.
The client/server code is explicitly tolerant of server- or client- side connecting in any order.

## Contents

The directory structure is as follows:

    <project>/src/
        client.c            - test program for the initiator of the connection
        CMakeLists.txt      - CMake configuration
        inet_ntop.c         - for Win32 which lacks this function
        server.c            - test program for the acceptor of the connection(s)
        socket.h            - the platform-independent API
        stristr.c           - case insensitive substring search
        strlcpy.c           - for Win32, a dependency of inet_ntop.c

### How to Compile

Using a shell or command prompt window, create a directory and launch CMake.  It should build an appropriate makefile or project which you can then use to build the software.  Ex:

      mkdir build
      cd build
      cmake ../src
      make

### How to execute

In two different shells or command prompt, execute the server or client in any order.  For example:

shell 1$ server 127.0.0.1:3500 0 persist=0
server: listening on 127.0.0.1,3500 ipv4...
server: connect from 127.0.0.1,49340 ...
407568 records in; min=4 max=16384 avg=15225
^C

shell 2$ client 127.0.0.1:3500 16384 400000 ipv4
client: connected to 127.0.0.1,3500 ...
client: using 16384 block size
400000+0+0 records out; bs=16384

### Tested On

Win7 32-bit, MinGW 3.20
  - NB: used cmd> cmake -G "MinGW Makefiles" ../src
  - NB: used cmd> mingw32-make
Win7  32-bit, MSVC++ Express 2013
  - NB: used cmd> cmake ../src
  - NB: used cmd> msbuild socket.sln /P:Configuration=Release
  - NB: beware, after I installed MSVC++ Express 2013, the commandline for 2010 broke but I could still build in the GUI -- cmake finds registry entries?
  - NB: there are alot of hassles with _CRT_SECURE_NO_WARNINGS and the xxx_s()'s.  Not dealing with it right now.
Win7 32-bit, Code::Blocks 12.11/MinGW 3.20
  - NB: used cmd> cmake -G "CodeBlocks - MinGW Makefiles" ../src
  - NB: used cmd> c:\codeblocks\codeblocks.exe --rebuild --target=all --no-batch-window-close socket.cbp

### TBD:

Linux/CentOS 6, GCC 4.4.7

MacOS 10.8.5, MACPORTS, GCC 4.7.3
  - NB: used $ CC=gcc-mp-4.7 CXX=g++-mp-4.7 cmake ../src
  - NB: used $ make

WinXP 32-bit, MSVS 8 2005

### TODO

- Explore use of [mingw-w64](http://mingw-w64.org/doku.php)

### References

- Pau Garcia i Quiles [Learning CMake](http://www.elpauer.org/stuff/learning_cmake.pdf)
- [rf-sampler](http://sourceforge.net/p/rf-sampler/code/HEAD/tree/trunk/software/socket/)
