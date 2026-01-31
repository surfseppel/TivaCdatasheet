@echo off
REM Flash script for TM4C123GXL using OpenOCD

echo Flashing TM4C123GXL...
echo.

if not exist build\blink.bin (
    echo ERROR: build\blink.bin not found!
    echo Build the project first: build.bat
    exit /b 1
)

where openocd >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: OpenOCD not found in PATH!
    echo Install from: https://openocd.org/getting-openocd/
    exit /b 1
)

echo Flashing build\blink.bin...
openocd -f interface/ti-icdi.cfg -f target/stellaris.cfg -c "program build/blink.bin verify reset exit"

if %ERRORLEVEL% EQU 0 (
    echo Flash successful! LED should start blinking.
) else (
    echo Flash failed! Check board connection and drivers.
)
