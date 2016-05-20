@echo off

@rem Select the build target.  Choices are 'Release|Win32', 'Release|x64' and their Debug counterparts
set BUILD_TARGET=Release
set BUILD_PLATFORM=Win32

@rem Set Various variables to make it easy(-er) to accomodate different developers' environments
set FOLDER=.
set PROJECT=RASDRstreamer.sln
set _DP0=%~dp0
set LOGF=build.log

@rem Must clear the path of any non-default entries to prevent 'poisoning' of the environment
@rem TODO: path will be different on Windows XP, 7, 8, etc... (probably only the non-existence of the WindowsPowerShell)
@rem set PATH=%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%SystemRoot%\System32\WindowsPowerShell\v1.0\

@REM configure environment for VS build
@REM NOTE: if you keep calling 'vsvars32.bat' it keeps adding stuff to the PATH
@REM       and eventually you will overload the string buffer
@if not "%VSINSTALLDIR%"=="" goto skip
@call "C:\Program Files\Microsoft Visual Studio 12.0\Common7\Tools\vsvars32.bat" >> %LOGF%
:skip

@rem Build automation for release engineering
@if "%1" == "release" @(
    @pushd "%_DP0%"
    @if exist "%_DP0%\dist" rmdir /s/q "%_DP0%\dist"
    @if ERRORLEVEL 1 goto stop
    @mkdir "%_DP0%\dist\x86"
    @mkdir "%_DP0%\dist\x64"
    @echo *** Building RASDRstreamer Release 32-bit... ***
    @MSBuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Clean /p:Configuration=Release /p:Platform=Win32 > nul
    @MSbuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Rebuild /p:Configuration=Release /p:Platform=Win32 >> %LOGF%
    @if ERRORLEVEL 1 goto stop
    @echo *** Building RASDRstreamer Release 64-bit... ***
    @MSBuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Clean /p:Configuration=Release /p:Platform=x64 > nul
    @MSbuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Rebuild /p:Configuration=Release /p:Platform=x64 >> %LOGF%
    @if ERRORLEVEL 1 goto stop
    @copy "%_DP0%\%FOLDER%\x86\Release\*.exe" "%_DP0%\dist\x86"
    @copy "%VCINSTALLDIR%\redist\x86\Microsoft.VC120.CRT\*.dll" "%_DP0%\dist\x86"
    @copy "%_DP0%\%FOLDER%\x64\Release\*.exe" "%_DP0%\dist\x64"
    @copy "%VCINSTALLDIR%\redist\x64\Microsoft.VC120.CRT\*.dll" "%_DP0%\dist\x64"
    @copy /Y "%_DP0%\RASDRstreamer-example.png" "%_DP0%\dist"
    @copy /Y "%_DP0%\readme.txt" "%_DP0%\dist"
    @echo *** DONE.  The release distribution is in the %_DP0%\dist\ ***
    @popd
    goto done
)

@rem Batch build the program
( cd %_DP0%\%FOLDER% & MSbuild %_DP0%\%FOLDER%\%PROJECT% /t:Rebuild /p:Configuration=%BUILD_TARGET% /p:Platform=%BUILD_PLATFORM% )
@if not errorlevel 1 goto done

:stop
@echo *** STOP.  There was an error in the last command ***
:done
@pause
