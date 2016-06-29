@echo off

@rem Select the build target.  Choices are 'Release|Win32', 'Release|x64' and their Debug counterparts
set BUILD_TARGET=Release
set BUILD_PLATFORM=Win32

@rem Set Various variables to make it easy(-er) to accomodate different developers' environments
set FOLDER=build
set PROJECT=raw2iq.sln
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
    @echo *** Clearing Distribution Folder ... ***
    @if exist "%_DP0%\dist" rmdir /s/q "%_DP0%\dist"
    @if ERRORLEVEL 1 goto stop
    @mkdir "%_DP0%\dist\x86"
    @mkdir "%_DP0%\dist\x64"
    @echo *** Generating Project for MS Visual Studio 12.0... ***
    @if exist "%_DP0%\%FOLDER%" rmdir /s/q "%_DP0%\%FOLDER%"
    @if ERRORLEVEL 1 goto stop
    @mkdir "%_DP0%\%FOLDER%"
    @pushd "%_DP0%\%FOLDER%"
    @cmake ../src
    @if ERRORLEVEL 1 goto stop
    @popd
    @echo *** Building %PROJECT% Release 32-bit... ***
    @MSBuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Clean /p:Configuration=Release /p:Platform=Win32 > nul
    @MSbuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Rebuild /p:Configuration=Release /p:Platform=Win32 >> %LOGF%
    @if ERRORLEVEL 1 goto stop
    @REM TODO: Figure out how to get CMake to build for 64-bit target
    @REM @echo *** Building %PROJECT% Release 64-bit... ***
    @REM @MSBuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Clean /p:Configuration=Release /p:Platform=x64 > nul
    @REM @MSbuild "%_DP0%\%FOLDER%\%PROJECT%" /t:Rebuild /p:Configuration=Release /p:Platform=x64 >> %LOGF%
    @REM @if ERRORLEVEL 1 goto stop
    @copy "%_DP0%\%FOLDER%\Release\*.exe" "%_DP0%\dist\x86"
    @REM @copy "%VCINSTALLDIR%\redist\x86\Microsoft.VC120.CRT\*.dll" "%_DP0%\dist\x86"
    @REM @copy "%_DP0%\%FOLDER%\x64\Release\*.exe" "%_DP0%\dist\x64"
    @REM @copy "%VCINSTALLDIR%\redist\x64\Microsoft.VC120.CRT\*.dll" "%_DP0%\dist\x64"
    @REM @copy /Y "%_DP0%\raw2iq-example.png" "%_DP0%\dist"
    @copy /Y "%_DP0%\readme.txt" "%_DP0%\dist"
    @echo *** DONE.  The release distribution is in the %_DP0%\dist\ ***
    @popd
    goto done
)

@rem Batch build the program
@if not exist "%_DP0%\%FOLDER%" mkdir "%_DP0%\%FOLDER%"
( cd %_DP0%\%FOLDER% & cmake ../src )
@if errorlevel 1 goto done
( cd %_DP0%\%FOLDER% & MSbuild %_DP0%\%FOLDER%\%PROJECT% /t:Rebuild /p:Configuration=%BUILD_TARGET% /p:Platform=%BUILD_PLATFORM% )
@if not errorlevel 1 goto done


:stop
@echo *** STOP.  There was an error in the last command ***
:done
@cd %_DP0%
@pause
