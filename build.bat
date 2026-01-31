@echo off
REM Windows batch file to build TM4C123GXL project
REM Requires ARM GCC toolchain in PATH

echo Building TM4C123GXL blink project...

REM Check if ARM GCC is available
where arm-none-eabi-gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: arm-none-eabi-gcc not found in PATH!
    echo Please install ARM GCC toolchain and add it to PATH.
    echo See INSTALL.md for instructions.
    exit /b 1
)

REM Create build directory
if not exist build mkdir build

REM Compile source files
echo Compiling main.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/main.c -o build/main.o
if %ERRORLEVEL% NEQ 0 exit /b 1

echo Compiling startup.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/startup.c -o build/startup.o
if %ERRORLEVEL% NEQ 0 exit /b 1

echo Compiling system.c...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -c src/system.c -o build/system.o
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Link
echo Linking...
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -Wall -Wextra -ffunction-sections -fdata-sections -g -Iinc -DTARGET_IS_TM4C123_RB1 -Tsrc/tm4c123gh6pm.ld -nostartfiles -Wl,--gc-sections -Wl,-Map=build/blink.map -o build/blink.elf build/main.o build/startup.o build/system.o
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Show size
echo.
echo Binary size:
arm-none-eabi-size build/blink.elf

REM Create binary
echo Creating binary...
arm-none-eabi-objcopy -O binary build/blink.elf build/blink.bin
if %ERRORLEVEL% NEQ 0 exit /b 1

echo.
echo Build successful!
echo Output files:
echo   - build/blink.elf (ELF executable)
echo   - build/blink.bin (Binary for flashing)
echo   - build/blink.map (Memory map)
