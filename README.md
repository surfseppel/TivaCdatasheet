# TM4C123GXL Tiva C Launchpad - Direct Development

This is a bare-metal development project for the TM4C123GXL Tiva C Launchpad using direct register access. No SDK or framework required - just the datasheet and ARM GCC toolchain.

## Hardware

- **Board**: TM4C123GXL Launchpad
- **Microcontroller**: LPTM4C123GH6PM (ARM Cortex-M4)
- **Frequency**: 80MHz
- **Flash**: 256KB
- **RAM**: 32KB
- **LEDs**: 
  - Red LED on PF1
  - Blue LED on PF2
  - Green LED on PF3

## Project Structure

```
.
├── build.bat             # Build script for blink example
├── build_adc.bat          # Build script for ADC example
├── flash.bat              # Flash script for blink example
├── flash_adc.bat          # Flash script for ADC example
├── src/
│   ├── main.c            # Blink example
│   ├── main_adc.c        # ADC and serial example
│   ├── startup.c         # Startup code and vector table
│   ├── system.c          # System initialization
│   └── tm4c123gh6pm.ld   # Linker script
├── inc/
│   └── tm4c123gh6pm.h    # Register definitions
└── docs/
    └── tm4c123gh6pm.pdf  # Datasheet
```

---

## Windows Setup (One-Time)

### Step 1: Install ARM GCC Toolchain

1. **Download**: Go to https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
2. **Download**: **Windows (mingw-w64-x86_64)** → `arm-gnu-toolchain-15.2.rel1-mingw-w64-x86_64-arm-none-eabi.msi`
   - For 32-bit Windows, use `mingw-w64-i686` version
3. **Install**: Run the installer (use default settings)
4. **Add to PATH**:
   - Open **System Properties** → **Environment Variables**
   - Under **User variables**, select **Path** → **Edit** → **New**
   - Add: `C:\Program Files\Arm\GNU Toolchain\arm-none-eabi\15.2.rel1\bin`
     - *(Or wherever the installer put it - look for the `bin` folder with `arm-none-eabi-gcc.exe`)*
   - Click **OK** on all dialogs
   - **Restart VS Code** (or your terminal)

5. **Verify**: Open PowerShell and run:
   ```powershell
   arm-none-eabi-gcc --version
   ```
   You should see version information.

### Step 2: Install OpenOCD (for Flashing)

1. **Download**: Go to https://openocd.org/getting-openocd/
   - Or use Chocolatey: `choco install openocd`
2. **Install**: Extract to a folder (e.g., `C:\openocd`)
3. **Add to PATH**: Add the `bin` folder to your PATH (same way as Step 1)
   - Example: `C:\openocd\bin`
4. **Verify**: 
   ```powershell
   openocd --version
   ```

### Step 3: Install Visual Studio Code (Optional)

1. **Download**: https://code.visualstudio.com/
2. **Install Extensions**:
   - **C/C++** (by Microsoft)
   - **Make** (any Make extension)

---

## Examples

### Example 1: Blink LED

Simple LED blinking example.

**Build:**
```powershell
.\build.bat
```

**Flash:**
```powershell
.\flash.bat
```

**Result**: Red LED (PF1) blinks every 500ms

### Example 2: ADC and Serial Monitor

Reads analog input and sends to serial monitor.

**Hardware Setup:**
- Connect a potentiometer or analog sensor to **PE3 (AIN0)**
- Connect one end to 3.3V, other end to GND, wiper to PE3

**Build:**
```powershell
.\build_adc.bat
```

**Flash:**
```powershell
.\flash_adc.bat
```

**View Serial Output:**
1. Open a serial monitor (e.g., PuTTY, Tera Term, or VS Code Serial Monitor extension)
2. Set baud rate to **115200**
3. Select the COM port (check Device Manager for "Stellaris Virtual COM Port")
4. You should see ADC values (0-4095) printed every second

**Result**: ADC values printed to serial monitor every second

## Building

### Using build.bat (Easiest - No Make Required)

1. **Open PowerShell** in the project folder
2. **Add ARM GCC to PATH** (if not permanently added):
   ```powershell
   $env:Path += ";C:\Program Files\Arm\GNU Toolchain\arm-none-eabi\15.2.rel1\bin"
   ```
   *(Adjust path to match your installation)*

3. **Build**:
   ```powershell
   .\build.bat          # For blink example
   .\build_adc.bat      # For ADC example
   ```

4. **Output**: Files will be in `build/` folder:
   - `build/blink.bin` or `build/adc_example.bin` - Ready to flash

### Using Visual Studio Code

1. **Open project**: `code .`
2. **Build**: Press **Ctrl+Shift+B**
3. **Or use terminal**: Press **Ctrl+`** and run `.\build.bat`

---

## Flashing

### Prerequisites

1. **Connect board**: Plug TM4C123GXL into USB
2. **Wait**: Windows should auto-install drivers
3. **Check**: Open Device Manager, look for "Stellaris In-Circuit Debug Interface"

### Flash the Board

1. **Make sure you built the project first** (see Building section)

2. **Run flash script**:
   ```powershell
   .\flash.bat          # For blink example
   .\flash_adc.bat      # For ADC example
   ```

3. **Done!** 
   - Blink example: Red LED should start blinking
   - ADC example: Connect to serial monitor to see ADC values

### If Flash Fails

- **Board not detected**: Install drivers from https://www.ti.com/tool/STELLARIS_ICDI_DRIVERS
- **OpenOCD not found**: Make sure OpenOCD is installed and in PATH
- **Try again**: Unplug and replug the USB cable, then run `.\flash.bat` again

---

## What the Examples Do

**Example 1 (Blink)**: Toggles the on-board red LED (PF1) every 500 milliseconds using direct register access.

**Example 2 (ADC)**: Reads analog input from PE3 (AIN0) every second and sends the value (0-4095) to the serial monitor at 115200 baud.

---

## Troubleshooting

**"arm-none-eabi-gcc not found"**
- ARM GCC is not in PATH
- Add it to PATH (see Setup Step 1) and restart VS Code/terminal

**"build/blink.bin not found"**
- Build the project first: `.\build.bat`

**"OpenOCD not found"**
- Install OpenOCD and add to PATH (see Setup Step 2)

**Board not detected**
- Install TI-ICDI drivers from TI's website
- Check Device Manager for the board

**LED doesn't blink**
- Press the reset button on the board
- Verify flash completed successfully

---

## Customization

To use different LEDs, modify `src/main.c`:

**Blue LED (PF2):**
```c
GPIO_PORTF_DIR_R |= (1 << 2);   // Set PF2 as output
GPIO_PORTF_DEN_R |= (1 << 2);   // Enable digital function
GPIO_PORTF_DATA_R |= (1 << 2);  // Turn on
```

**Green LED (PF3):**
```c
GPIO_PORTF_DIR_R |= (1 << 3);   // Set PF3 as output
GPIO_PORTF_DEN_R |= (1 << 3);   // Enable digital function
GPIO_PORTF_DATA_R |= (1 << 3);  // Turn on
```

---

## Reference

- **Datasheet**: See `docs/tm4c123gh6pm.pdf` for complete register map and peripheral details
- **Register definitions**: See `inc/tm4c123gh6pm.h` for hardware register addresses
