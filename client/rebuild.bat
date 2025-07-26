@echo off
setlocal

echo [🔨] Building with mingw32-make...
cd build
mingw32-make

if errorlevel 1 (
    echo [❌] Build failed!
    pause
    exit /b 1
)

echo [✅] Build succeeded!

REM Run the executable if it exists
cd bin
if exist shader-playground.exe (
    echo [🚀] Running shader-playground.exe...
    start "" shader-playground.exe
) else (
    echo [⚠] shader-playground.exe not found in /bin
)

endlocal
