@echo off
setlocal

REM Go to build directory
cd /d "%~dp0build\bin"

REM Run the program if it exists
if exist shader-playground.exe (
    echo [🚀] Launching shader-playground.exe...
    start "" shader-playground.exe
) else (
    echo [❌] shader-playground.exe not found in build\bin
    pause
)

endlocal
