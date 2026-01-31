@echo off
REM Flash script for TM4C123GXL ADC example using OpenOCD

echo Flashing TM4C123GXL ADC example...
echo.

if not exist build\adc_example.bin (
    echo ERROR: build\adc_example.bin not found!
    echo Build the project first: build_adc.bat
    exit /b 1
)

where openocd >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: OpenOCD not found in PATH!
    echo Install from: https://openocd.org/getting-openocd/
    exit /b 1
)

echo Flashing build\adc_example.bin...
openocd -f interface/ti-icdi.cfg -f target/stellaris.cfg -c "program build/adc_example.bin verify reset exit"

if %ERRORLEVEL% EQU 0 (
    echo Flash successful! Connect to serial monitor at 115200 baud.
) else (
    echo Flash failed! Check board connection and drivers.
)
