@REM select how the program is started.  Choices are: 'python plotcsv.py', 'plotcsv.exe'
@set PLOTCSV=python plotcsv.py
@if "%1" == "gui" ( set GUI=-g ) else ( set GUI= )

@REM Original Formats since RASDRviewer 1.0.4
%PLOTCSV% FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-localtime.csv --localtime --format=1.0.4 -a 5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.0.4-universaltime.csv --format=1.0.4 -a 5 --background=automatic --smooth=5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault

@REM Format change in RASDRviewer 1.1.1
%PLOTCSV% FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 %GUI%  --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 %GUI%  --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-localtime.csv --localtime --format=1.1.1 -a 5 %GUI%  --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.1.1-universaltime.csv --format=1.1.1 -a 5 --background=automatic --smooth=5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault

@REM Format change in RASDRviewer 1.2.2
%PLOTCSV% FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-localtime.csv --localtime --format=1.2.2 -a 5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --info
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=automatic --smooth=5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault

@REM Test option to also show background waveform in alternate color (red)
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --bplot
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --bplot --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --bplot --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-background.csv --smooth=5 %GUI% --bplot --atype=log --ptype=linear

@REM Test a degenerate condition of using the same file as its background
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 %GUI%
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 %GUI% --atype=linear --ptype=log
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 %GUI% --atype=linear --ptype=linear
@if ERRORLEVEL 1 goto fault
%PLOTCSV% FFTOut-format-1.2.2-universaltime.csv --format=1.2.2 -a 5 --background=FFTOut-format-1.2.2-universaltime.csv --smooth=5 %GUI% --atype=log --ptype=linear
@if ERRORLEVEL 1 goto fault

@REM got here all is OK
@echo **************************
@echo *** TESTS COMPLETED OK ***
@echo **************************
@goto done

:fault
@echo *********************
@echo *** TESTS FAILED  ***
@echo *********************

:done
