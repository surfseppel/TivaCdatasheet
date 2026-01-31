@echo off
REM Windows batch file to build TM4C123GXL ADC example
REM Requires ARM GCC toolchain in PATH

echo Building TM4C123GXL ADC example...

REM Check if ARM GCC is available
where arm-none-eabi-gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: arm-none-eabi-gcc not found in PATH!
    echo Please install ARM GCC toolchain and add it to PATH.
    echo See README.md for instructions.
    exit /b 1
)

REM Create build directory
if not exist build mkdir build

REM Compile source files
echo Compiling main_adc.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/main_adc.c -o build/main_adc.o
if %ERRORLEVEL% NEQ 0 exit /b 1

echo Compiling startup.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/startup.c -o build/startup.o
if %ERRORLEVEL% NEQ 0 exit /b 1

echo Compiling system.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/system.c -o build/system.o
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Link
echo Linking...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -Tsrc/tm4c123gh6pm.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=build/adc_example.map -o build/adc_example.elf build/main_adc.o build/startup.o build/system.o
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Show size
echo.
echo Binary size:
arm-none-eabi-size build/adc_example.elf

REM Create binary
echo Creating binary...
arm-none-eabi-objcopy -O binary build/adc_example.elf build/adc_example.bin
if %ERRORLEVEL% NEQ 0 exit /b 1

echo.
echo Build successful!
echo Output files:
echo   - build/adc_example.elf (ELF executable)
echo   - build/adc_example.bin (Binary for flashing)
echo   - build/adc_example.map (Memory map)
