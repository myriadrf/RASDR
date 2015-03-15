RASDRviewer_W_1_2_1_0 Release 1 February 2015

This folder contains the release of RASDRviewer_W_1_2_1.0

This is a Windows release however it will run using Boot Camp on a MAC OS-X machine. It has not been tested on Windows 8.1
due to the unvailbility of a SARA signed driver. It has been tested on Windows 7 with the SARA signed driver. Likewise it
has not been tested using USB3 since the user's only machine with USB3 operates on Windows 8.1.

This release allows the use of either the SARA firmware image files. It is issued as a minor
feature addition since in contains the code necessary for variable power integration times and the abiliy to select a range of frequency bins
on the FFT display and recorded outputs.


The releasse has been tested on Windows 7 X64, and it should run (untested) on a MAC OS Mavericks with
a boot camp loaded with Windows 8.1 X64. It will also run on a Windows XP earlier version system with NIVIDIA graphics
card. It will not work on earlier (prior to 2006) that use the Intel chip set for the graphics display. When the program attempts
to load on these early systems, it fails due to the incompatability with Open GL charting that is used in the program. Some of
these systems may work with the retrofit of a NIVIDIA graphics card. The driver for the NIVIDIA card needs to be the latest available
from NIVIDIA. It will not work with the latest Microsoft Driver for the NIVIDIA card. It is necessary to disable the automatic Miscrosoft
driver update to avoid the installation of the earlier Microsoft driver.

This release is based on RASDRviewer_W_1_2.0.0 and should include all previous releases and patches.

To install the release on a Windows machine:
1. Open the file RASDRviewer_1_2_1_0_W_exe zip with WinZip or equivalent.
2. Extract all of the files in the zip folder to a folder of your choice. (i.e. c:\RASDRviewer)
3. Create a shortcut to the executable in the folder ReleaseWin32, drag or copy the shortcut to your desktop.
4. Execute the program by double clicking the shortcut.

System Requirements:

1. Windows (2000 or Later) X86 capable machine. Sincle Core machines will work but a dual(or larger) core system is recommended.
2. Lime Microsystems/Myriad RF - Digi-Red board with Myriad RF board
3. USB 2 or USB 3 port (USB3 (untested) is preferred but to obtain maximum performance)
4. SARA "RASDR Radio Astronomy SDR Rx Interface" driver. The SARA driver will not work on Windows 8. 
The Cypress Streamer Example driver will likely work on Windows 8 but is untested.


Known Issues :  On the multiple file outputs, the system produces an additional file with only the header populated.

Report any additional isssues to Paul Oxley 770-887-3493 oxleys@att.net

Your RASDR Team