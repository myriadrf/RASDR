Inter-Process Communication (IPC) via TCP/IP socket in a cross-platform header
==============================================================================

Release 1.0 - Aug 1, 2015

This is a small client/server test suite to explore basic implementation of IPC
mechanisms available on Windows and Unix systems, and to produce a cross-platform
header that can be used to quickly add such functionality to several programs.

The basic principle is to use socket- IPC mechanisms as described in
references such as:
http://www.catb.org/esr/writings/taoup/html/ch07s02.html
http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html

The purpose was to explore the implementation issues of three common IPC
mechanisms on a variety of systems including RHEL5, Ubuntu and MacOS X.  There
were some, and they were incorporated into the code where necessary.
Specifically, the ability to start a client or server on a resource in any order
and have the two self-synchronize was of interest, as well as the ability to
transparently communicate between machine nodes via available streaming
protocols, such as TCP/IP.

This code can be used as a starting point for implementing libraries for IPC
between processes.
