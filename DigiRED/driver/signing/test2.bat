@echo off
@set BASE=C:\temp\cyusb3_v1_2_3_14_WHQL_Certified_signed
@set CERT=Z:\sw-rasdr\certificates\RASDR-signing.cer
@set NAME="RASDR Software Development and Testing"
@set STMP=http://timestamp.verisign.com/scripts/timestamp.dll
@set DEBUG=
@set PATH="C:\Program Files\Windows Kits\10\bin\x86";%PATH%

@rem alternate SignTool(s)
@rem SignTool sign /debug /v /ac %CERT% /s root /n %NAME% /t http://timestamp.verisign.com/scripts/timestamp.dll cyusb3.cat
@rem SignTool sign /debug /v /ac %CERT% /s root /n %NAME% /t http://timestamp.globalsign.com/scripts/timstamp.dll cyusb3.cat

:setup
@pushd %BASE%

:vista
cd %BASE%\vista\x86
inf2cat /v /driver:%BASE%\vista\x86 /os:Vista_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\vista\x64
inf2cat /v /driver:%BASE%\vista\x64 /os:Vista_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

:win7
cd %BASE%\win7\x86
inf2cat /v /driver:%BASE%\win7\x86 /os:7_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\win7\x64
inf2cat /v /driver:%BASE%\win7\x64 /os:7_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

:win8
cd %BASE%\win8\x86
inf2cat /v /driver:%BASE%\win8\x86 /os:8_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\win8\x64
inf2cat /v /driver:%BASE%\win8\x64 /os:8_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

:win8.1
cd %BASE%\win8.1\x86
inf2cat /v /driver:%BASE%\win8.1\x86 /os:8_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\win8.1\x64
inf2cat /v /driver:%BASE%\win8.1\x64 /os:8_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

:win10
cd %BASE%\win10\x86
inf2cat /v /driver:%BASE%\win10\x86 /os:10_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\win10\x64
inf2cat /v /driver:%BASE%\win10\x64 /os:10_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

:wxp
cd %BASE%\wxp\x86
inf2cat /v /driver:%BASE%\wxp\x86 /os:XP_X86
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop
cd %BASE%\wxp\x64
inf2cat /v /driver:%BASE%\wxp\x64 /os:XP_X64
SignTool sign %DEBUG% /v /ac %CERT% /s root /n %NAME% /t %STMP% cyusb3.cat
@if errorlevel 1 goto stop

@popd
@goto done

:stop
@pause
:done
