From: Michel Tossaint
To: Paul Oxley; David Fields
Sent: Thursday, April 30, 2015 10:01 AM
Subject: Re: Fw: wxWidgets compilation recipe ver 2

Revision History: May 8, 2015 Bogdan Vacaliuc
                     Added links to download files and Appendix
                     Tested with RASDRviewer 1.0.5 Source
                  May 9, 2015 Bogdan Vacaliuc
                     Added instructions using 'make.bat'
                     Tested with RASDRviewer 1.2.2 Source


Compile instructions RASDRviewer on Windows
===========================================

PREPARATIONS BEFORE COMPILING
-----------------------------

Use the following two setup files (not any other version or file…):

http://sourceforge.net/projects/codeblocks/files/Binaries/12.11/Windows/
codeblocks-12.11mingw-setup.exe

1)  Install codeblocks 12.11  in 
        c:\codeblocks

http://sourceforge.net/projects/wxwindows/files/2.9.5/
wxWidgets-2.9.5.zip

2)  Install wxWidgets 2.9.5 library in
        c:\libraries\wxWidgets-2.9.5\

3)  In c:\libraries\wxWidgets-2.9.5\build\msw\config.gcc change the following lines:
        BUILD ?= release
        DEBUG_FLAG ?= 0
        RUNTIME_LIBS ?= static

4)  Run command prompt as Administrator and execute this command (this will setup required variables for current command prompt sesion):
        c:\CodeBlocks\MinGW\mingwvars.bat 

5)  Execute this command in command prompt: 
        cd c:\libraries\wxWidgets-2.9.5\build\msw\

6)  Execute this command in command prompt:
        mingw32-make SHELL=CMD.exe -f makefile.gcc

7) Test wxWidget installation as follows:

    Execute this command in command prompt: 
        cd c:\libraries\wxWidgets-2.9.5\samples\minimal
    Execute this command in command prompt: 
        mingw32-make SHELL=CMD.exe -f makefile.gcc
    Execute this command in command prompt:
        c:\libraries\wxWidgets-2.9.5\samples\minimal\gcc_mswu\minimal.exe
    GUI should appear.

8) RASDRViewer

OPTION #1 - compile within the IDE Environment
----------------------------------------------

    a. Unzip files from RASDRviewer_Source_X_Y_Z_W.zip in any folder
    b. Using the command prompt you started above (administrator/mingwvars.bat), or equivalent, cd to the folder that contains the RASDRviewer.cbp file
    c. Start c:\codeblocks\codeblocks.exe from this folder
    d. Choose 'open existing project' and open the RASDRViewer.cbp project file within code::blocks
    e. Set the Build target: Release Win32  -or- Debug Win32
    f. choose Build->Rebuild

The executable program will be created in .\ReleaseWin32\ or .\DebugWin32\ respectively.
You may use the RED '>' on the GUI to start the program, or just double click it.

OPTION #2 - automatic build
---------------------------

Use the 'make.bat' script to build either the Release or Debug build (Release is default as distributed).
See 'make.bat' for instructions on switching between one and the other.
The Debug build causes RASDRviewer to open a companion console with additional diagnostic information output during program execution.

*** IMPORTANT ***
For some users, compiling in their user account may not succeed.  If this is your case, then please right-click the batch file and choose 'Run as administrator' to compile.  This is similar to step #4 above.  See 'make.bat' for additional details and also the Appendix section below.

The executable program will be created in .\ReleaseWin32\ or .\DebugWin32\ respectively.
You can double-click the program to start it.

NOTES on EXECUTION
------------------

The first time you run RASDRviewer from one of the above builds, it my complain that it cannot open 'RASDR.cfg'.  That is OK, it will generate this file with internal defaults.  The binary release of RASDRviewer comes with an initial 'RASDR.cfg' that satisfies the program and is used subsequently for changes in parameters made by the user.


APPENDIX
========

Before RASDRviewer_W.exe can execute, certain .dll files must exist in the folder that RASDRviewer_W.exe was created.   The 'RASDRviewer.cbp' file has defined Post-Build steps to perform these copies from the .\Logic\dependencies folder so that you may execute the programs from within the Code::Blocks IDE or from the file explorer or shortcut.  The steps are (continuing from the list in step #8 above):

    g. copy .\Logic\dependencies\fftw-3.3.3\libfftw3f-3.dll to .\ReleaseWin32
    h. copy .\Logic\dependencies\pthreads-w32-2-9-1-release\Pre-built.2\dll\x86\pthreadGCE2.dll to .\ReleaseWin32
    i. copy .\Logic\dependencies\MinGW\bin\libgcc_s_dw2-1.dll to .\ReleaseWin32
    j. copy .\Logic\dependencies\MinGW\bin\libstdc++-6.dll to .\ReleaseWin32

Because of the Post-Build step, you can also use the Build target: Debug Win32, as you like.

*** IMPORTANT NOTE: it is good to perform step 8.b) above using the administrator user because the compilation is *EXTREMELY SENSITIVE* to environment variables.  If your environment is setup for some other compiler, Code::Blocks will readily pull in files from this other area and create a failed compilation.  Starting with a minimial shell and running as Administrator helps ensure that this doesn't happen.

If instead you try to use the DLLs from the MinGW compiler:

    copy C:\CodeBlocks\MinGW\bin\libgcc_s_dw2-1.dll to .\ReleaseWin32
    copy C:\CodeBlocks\MinGW\bin\libstdc++-6.dll to .\ReleaseWin32

You will get additional errors about missing .dlls so I also had to:

    copy C:\CodeBlocks\MinGW\bin\libgcc_s_sjlj-1 to .\ReleaseWin32

Afterwhich I got the following:

X The procedure entry point __gxx_personality_v0 could not be located in the dynamic link library libstdc++6.dll

So...  No go for using 'RASDRviewer_W_1_0_5' source.  However, in comparing these, I see that 'libgcc_s_dw2-1.dll' and 'libstdc++-6.dll' are *different* for the release of RASDRviewer_W_1_0_5 (whose source I have) than RASDRViewer1_21W (whose source I do not have).  The above procedure has .dll that match the RASDRviewer1_21W release, so it is a good bet that Paul and Michel's compile match.

*THEN* I decided to simply *copy* the .dll's from RASDRviewer_W_1_0_5 release in to the folder where the RASDRviewer_W.exe was built.  Upon launching this program, RASDRviewer *DID* execute correctly.  Therefore, I think if the two MinGW .dll's are archived in the dependencies and used to update the folder where the executable is produced, then a workable solution may exist for folks trying to build this program.

For a discussion on copying dependent .dll into the program folder, please see:
http://forums.codeblocks.org/index.php?topic=2651.0;prev_next=prev

More thoughts:

in .\Logic\dependencies\CyAPI\, there is a file 'libCyAPI_fx3_GCC.a' which is a dependency of RASDRviewer source build.  It is *likely* that this library introduces a ABI-incompatibility.  A little research on the '__gxx_personality_v0' error turned up the following links:

http://stackoverflow.com/questions/18668003/the-procedure-entry-point-gxx-personality-v0-could-not-be-located-in-the-dnyam
http://stackoverflow.com/questions/17410718/the-procedure-entry-point-gxx-personality-v0-could-not-be-located-in-the-dynami
http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for
http://forums.codeblocks.org/index.php?topic=20246.0

Generally speaking, the links discuss mismatches between exeception handling models available (setjmp/longjmp, "sjlj") and (DWARF, "dw"), the location of same-named .dlls somewhere else in the system and compiler/linker options in codeblocks.  Since I had to do step 8.k. above, I'm leaning toward the exception handling system as being the culprit -- and hence its solution being to check the compiler options in use.

Discussions on the exception model here are informative:

http://www.rioki.org/2013/10/16/mingw-w64.html
http://stackoverflow.com/questions/15670169/what-is-difference-between-sjlj-vs-dwarf-vs-seh

From what I've gathered, the exception handling is *built-in* to the compiler when it is, well, compiled.  Choosing the compiler and configuring it is something that Rioki posted very well.  It may be prudent for the RASDRviewer project to consider using a mingw-w64 compiler (which can handle windows 32-bit and 64-bit compiles, despite the suggestive project name), and *not* the compiler that is packaged with Code::Blocks.  Care must be taken with the static library 'libCyAPI_fx3_GCC.a'.  The fact is, that the '.\Logic\dependencies\CyAPI\CyAPI.cpp' is the source code for the 'libCyAPI_fx3_GCC.a' library, so there really is not need to have a static library for this, when it could be added as a library like the Logic or GUI libraries are.
 
In anycase, for now, I've added Post-build steps to perform the copy of the existing dependences and added two dependencies from the compiler to a .\Logic\dependencies\MinGW\ folder, so that the post-build steps will do the right thing as part of the compile process.   This is documented in:
http://www.codeblocks.org/docs/main_codeblocks_en3.html#x3-80001.6
