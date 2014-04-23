@rem del /q build
@rem del /q dist
setup.py py2exe
@if not ERRORLEVEL 1 GOTO ok
@echo.
@echo *** FAILURE ***
@goto done
:ok
@echo.
@echo *** Your application is built in dist/
:done
@pause
