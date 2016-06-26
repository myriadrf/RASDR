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
2) Load RASDRviewer 1.2.2.2 or RASDRproc, and configure it to the acquisition parameters you wish to use.  { sample rate, samples/frame, bandwidth, gain settings, etc. }
   a. Please note that when using USB2, 10 MS/s is the practical limit
3) Ensure that you are taking data the way you want it by using RASDRviewer to START and STOP capturing samples.
4) Start RASDRstreamer.exe (x86 or x64) and select the RASDR device in the Connected Devices List
   a. This may either be "(0x1D50 - 0x6099) RASDR Radio Astronomy SDR..."
   b. Or it may be "(0x04B4 - 0x00F1) Cypress FX3 USB StreamerExample..." (if you are using the CYFX3KIT hardware for testing)
   c. Select the "BULK IN ..." Endpoint
5) Select the 'Samples/Frame', 'Rate (MHz)' and 'Integration Time (ms)' fields to match what RASDRviewer was set to.
   a. These settings only define the packetization parameters, the actual transfer rate was defind by the RASDRviewer configuration of the LMS6002D chip.
6) Decide you wish to save RAW data or not by ticking the check box
   a. When using USB3 and writing .raw file, you will observe a rate reduction when the in-memory file system buffers fill up.
7) Press START.

![RASDRstreamer-example](https://github.com/myriadrf/RASDR/tree/master/host/RASDRstreamer/RASDRstreamer-example.png)
*RASDRstreamer GUI showing steps 4-7 and example progress output*

You will observe successful packets accumulating, the actual transfer rate in KiB/s reported in the GUI.  In the text box below the transfer rate, you will see the packetization parameter and the expected transfer rate based on the selection above.  If you chose to save RAW data, it will also tell you the filename it chose to use.

The program does not overwrite an existing file, rather it adds a '#NNN' suffix to create a unique filename each time.  The files will always have the form 'RASDRstreamer#NNN.raw' as described in the GUI and will always be in the location in the filesystem that the .exe is started from [as of v0.1].

The format of the data are interleaved I and Q 16-bit samples encoded as described in Appendix E of the RASDR User Manual pg. 67-68.  That is, the control bits for I/Q, FIFO flags and PPS are encoded and must be removed in post-processing to interpret the ADC data.  The I/Q streams will also need to be de-interleaved and aligned.  If the HOST PC data acquisition system cannot keep up with the actual data rate (as calculated) then correct interpretation of the I/Q data may require flipping of bits and re-synchronizing to the PPS signal bit.

NOTE:  As per Microsofts documentation:
https://msdn.microsoft.com/en-us/windows-drivers/develop/using_the_microsoft_c_runtime_with_user_mode_drivers_and_apps

The VC re-distributable components are provided with the application file.  They can also be downloaded here:
https://www.microsoft.com/en-us/download/details.aspx?id=40784

==============================================================================
    BUGS
==============================================================================

1) RASDR2 Firmware prior to June 2016 (Device Descriptor BcdDevice="00 03" or earlier) had issues with USB3 operation on certain computers (lower specification) that caused glitches and failed transports.  With Firmware BcdDevice="00 04", this has been *partially mitigated* by eliminating the burst mode when using USB3 SuperSpeed mode.  The change does not eliminate the glitch, but reduces its liklihood considerably.

The workaround is a software close and re-open of the USB device.  For RASDRstreamer, this can be accomplished by restarting the program or stopping the transfer and re-selecting the device, then pressing START.

2) v0.1.2 and below of RASDRstreamer has a threading issue in the ::Display() call that leads to random exceptions.  Particularly if there is an early failure in the USB immediately upon pressing the START button.

3) If you get 'Xfer request rejected. NTSTATUS = c0000001' when trying to START, this means that the firmware has entered an invalid state, and the device must be disconnected and reconnected.  (The Firmware BcdDevice="00 04" is only *partially mitigated*) 
 
==============================================================================
    CHANGELOG
==============================================================================

v0.2.0 - Unreleased

  Refactor buffers in XferLoop() to be conducive to restart operation
  Keep success/failure count persistent across XferLoop() starts/stops

v0.1.3 - Unreleased

  Add queued string output to prevent crashes
  Add temporary workaround 'CheckForIllegalCrossThreadCalls=false' for calling UI components from thread functions

<rant>Why does *every* example software have such bad UI thread issues?  Its crushing how much code is written like this.  It works for simple cases, and then as soon as you start to extend it...  boom, crash, game over.  Its such a waste of time.  You were much better off starting from scratch.  But then...  you will have invested so much time in the code that any rational human being will want to get some compensation for it, and you will close the source and keep it secret.  Well, I am not rational, so I hope that my (insignificant) efforts at repairing these will help some poor soul stuck with the same problems in the code they have to deal with.</rant>

v0.1.2 - Unreleased

  Add vertical scrollbar to diagnostic output
  Fix bug not using 'rb' when writing .raw files that leads to files getting premature EOF

v0.1.1 - First Public Distribution

  Track when transfer rate is not close to what is expected
  Color the transfer rate bar if the expected/actual data rate differs by more than 3% and 10%
  Fix bug when closing if raw output file is not opened

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
