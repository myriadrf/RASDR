@echo off
@rem *** IMPORTANT ***
@rem It is observed that the build may not succeed if this is run in a user-account.
@rem If you observe errors at the link-stage of the compile of the form:
@rem    undefined reference to `__gxx_personality_sj0'
@rem    undefined reference to `_Unwind_SjLj_Register'
@rem    undefined reference to `_Unwind_SjLj_Unregister'
@rem    undefined reference to `_Unwind_SjLj_Resume'
@rem Then please execute this script by right-clicking the 'make.bat', choose
@rem 'Run as administrator' and provide a suitable password.
@rem
@rem It is not known what causes this behavior.  Somehow, a mis-match in the exception
@rem handling model has occured during the compilation, as described by:
@rem    http://stackoverflow.com/questions/329059/what-is-gxx-personality-v0-for
@rem    http://stackoverflow.com/questions/307610/how-do-exceptions-work-behind-the-scenes-in-c
@rem
@rem At some point in the future, perhaps we may be able to resolve this for the RASDRviewer source.

@rem Select the build target.  Choices are 'Release Win32' and 'Debug Win32'
set BUILD_TARGET=Release Win32

@rem Set Various variables to make it easy(-er) to accomodate different developers' environments
@rem NOTE: codeblocks must be installed in c:\codeblocks at the moment because the project file requires this location
set CODEBLOCKS_ROOT=c:\CodeBlocks
set FOLDER=FFTviewer_src
set PROJECT=RASDRviewer.cbp
set _DP0=%~dp0

@rem Must clear the path of any non-default entries to prevent 'poisoning' of the environment
@rem TODO: path will be different on Windows XP, 7, 8, etc... (probably only the non-existence of the WindowsPowerShell)
set PATH=%SystemRoot%\system32;%SystemRoot%;%SystemRoot%\System32\Wbem;%SystemRoot%\System32\WindowsPowerShell\v1.0\

@rem setup the Code::Blocks variables
call %CODEBLOCKS_ROOT%\MinGW\mingwvars.bat
@if errorlevel 1 goto stop

@rem Batch build the program
( cd %_DP0%\%FOLDER% & %CODEBLOCKS_ROOT%\codeblocks.exe --no-batch-window-close --rebuild --target="%BUILD_TARGET%" %PROJECT% )
@if not errorlevel 1 goto done

:stop
@echo *** STOP.  There was an error in the last command ***
:done
@pause
