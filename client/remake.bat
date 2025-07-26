@echo off
setlocal

:: Set the build directory
set BUILD_DIR=build

:: Create build directory if it doesn't exist
if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

:: Run CMake (only configures if needed)
echo [CMake] Configuring...
cmake -S . -B %BUILD_DIR% || goto :error

:: Build incrementally
echo [Build] Compiling only changed files...
cmake --build %BUILD_DIR% -- -j %NUMBER_OF_PROCESSORS% || goto :error

echo [Success] Build completed.
exit /b 0

:error
echo [Error] Build failed.
exit /b 1
