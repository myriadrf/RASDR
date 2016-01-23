==============================================================================
    APPLICATION : RASDRstreamer Project
==============================================================================

This project is derived from the CYPRESS FX3 Development Kit project, "C++ Streamer".  It can be used to collect RAW data from a RASDR device.

The Cypress program, "C++ Streamer" was useful for evaluating USB2/USB3 performance of the FX3 chips.  The original program source is provided at:
"C:\Program Files\Cypress\EZ-USB FX3 SDK\1.3\application\cpp\streamer"

I have updated the program to compile with Microsoft Visual Studio Express 2013 for Windows Desktop, to accept the RASDR VID/PID and to build for X86 and X64 windows archicectures.  Additionally, I have added the ability for it to write data out to a file.  The source code to the program is provided at:
https://github.com/myriadrf/RASDR/tree/master/host/RASDRstreamer

To use the Program, perform the following steps:

1) insert RASDR device to a USB2 or USB3 port
2) Load RASDRviewer 1.2.2.2, and configure it to the acquisition parameters you wish to use.  { sample rate, samples/frame, bandwidth, gain settings, etc. }
   a. Please note that when using USB2, 10 MS/s is the practical limit
3) Ensure that you are taking data the way you want it by using RASDRviewer to START and STOP capturing samples.
4) Start RASDRstreamer.exe (x86 or x64) and select the RASDR device in the Connected Devices List
   a. This may either be "(0x1D50 - 0x6099) RASDR Radio Astronomy SDR..."
   b. Or it may be "(0x04B4 - 0x00F1) Cypress FX3 USB StreamerExample..." (if you are using the CYFX3KIT hardware for testing)
   c. Select the "BULK IN ..." Endpoint
5) Select the 'Samples/Frame', 'Rate (MHz)' and 'Integration Time (ms)' fields to match what RASDRviewer was set to.
   a. These settings only define the packetization parameters, the actual transfer rate was defind by the RASDRviewer configuration of the LMS6002D chip.
6) Decide you wish to save RAW data or not by ticking the check box
7) Press START.

![RASDRstreamer-example](https://github.com/myriadrf/RASDR/tree/master/host/RASDRstreamer/RASDRstreamer-example.png)
*RASDRstreamer GUI showing steps 4-7 and example progress output*

You will observe successful packets accumulating, the actual transfer rate in KiB/s reported in the GUI.  In the text box below the transfer rate, you will see the packetization parameter and the expected transfer rate based on the selection above.  If you chose to save RAW data, it will also tell you the filename it chose to use.

The program does not overwrite an existing file, rather it adds a '#NNN' suffix to create a unique filename each time.  The files will always have the form 'RASDRstreamer#NNN.raw' as described in the GUI and will always be in the location in the filesystem that the .exe is started from [as of v0.1].

The format of the data are interleaved I and Q 16-bit samples encoded as described in Appendix E of the RASDR User Manual pg. 67-68.  That is, the control bits for I/Q, FIFO flags and PPS are encoded and must be removed in post-processing to interpret the ADC data.  The I/Q streams will also need to be de-interleaved and aligned.  If the HOST PC data acquisition system cannot keep up with the actual data rate (as calculated) then correct interpretation of the I/Q data may require flipping of bits and re-synchronizing to the PPS signal bit.

==============================================================================
    CHANGELOG
==============================================================================

v0.1 - First Source Code Release

  Evaluates expected/actual data rate received, handles (recoverable) USB3 glitches gracefully.  Saves .raw files not overwriting the previous sequence number if it exists.

==============================================================================
    FILE SUMMARY
==============================================================================

This is a summary of what you will find in each of the files that make up the Streams application which uses cypress C++ library CyAPI.lib.

RASDRstreamer.vcproj/.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard. 
    It contains information about the version of Visual C++ that generated the file, and 
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

RASDRstreamer.cpp
    This is the main application source file (boilerplate).

RASDRstreamer.h
    Contains the implementation of the program, according to .NET style.

AssemblyInfo.cpp
    Contains custom attributes for modifying assembly metadata.

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Win32.pch and a precompiled types file named StdAfx.obj.
