@echo off
setlocal

echo [🧹] Cleaning old build...
rmdir /s /q build 2>nul
mkdir build
cd build

echo [⚙] Configuring with MinGW Makefiles...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

if errorlevel 1 (
    echo [❌] CMake configuration failed!
    pause
    exit /b 1
)

echo [🔨] Building with mingw32-make...
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
