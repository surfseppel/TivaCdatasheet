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
├── Makefile              # Build configuration
├── src/
│   ├── main.c           # Main application code
│   ├── startup.c        # Startup code and vector table
│   ├── system.c         # System initialization
│   └── tm4c123gh6pm.ld  # Linker script
├── inc/
│   └── tm4c123gh6pm.h   # Register definitions
└── docs/
    └── tm4c123gh6pm.pdf # Datasheet
```

## Prerequisites

1. **ARM GCC Toolchain**
   - Download from: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain
   - Or install via package manager:
     - Windows: Use MSYS2 or install ARM GCC manually
     - Linux: `sudo apt-get install gcc-arm-none-eabi`
     - macOS: `brew install arm-none-eabi-gcc`

2. **Make** (usually pre-installed on Linux/macOS)
   - Windows: Install via MSYS2 or use `mingw32-make`

3. **OpenOCD** (optional, for flashing)
   - Download from: http://openocd.org/
   - Or install via package manager

## Building

1. **Build the project**:
   ```bash
   make
   ```

2. **Clean build files**:
   ```bash
   make clean
   ```

3. **View help**:
   ```bash
   make help
   ```

The build process will create:
- `build/blink.elf` - ELF executable
- `build/blink.bin` - Binary file for flashing
- `build/blink.map` - Memory map

## Flashing

### Prerequisites

1. **Connect your board**: Plug the TM4C123GXL into your computer via USB
2. **Install drivers**: Windows should auto-install, but if not, download TI-ICDI drivers from TI's website

### Option 1: Using OpenOCD (Recommended)

If you have OpenOCD installed:

**Using Make:**
```bash
make flash
```

**Using batch file (Windows):**
```powershell
.\flash.bat
```

**Manual command:**
```bash
openocd -f interface/ti-icdi.cfg -f target/stellaris.cfg -c "program build/blink.bin verify reset exit"
```

### Option 2: Using LM Flash Programmer

1. Download from: https://www.ti.com/tool/LMFLASHPROGRAMMER
2. Connect your board via USB
3. Load `build/blink.bin` and click "Program"

### Option 3: Using Code Composer Studio

1. Import the project into CCS
2. Build and flash using the built-in debugger

## What This Example Does

The blink example toggles the on-board red LED (PF1) every 500 milliseconds using direct register access. The code:

1. Enables the clock to Port F
2. Configures PF1 as an output
3. Toggles the LED in a loop

## Understanding the Code

### Register Access

All hardware registers are accessed directly through memory-mapped I/O. The register definitions in `inc/tm4c123gh6pm.h` are based on the datasheet memory map.

### Key Registers Used

- `SYSCTL_RCGCGPIO_R`: System control register to enable GPIO port clocks
- `GPIO_PORTF_DIR_R`: GPIO direction register (input/output)
- `GPIO_PORTF_DEN_R`: GPIO digital enable register
- `GPIO_PORTF_DATA_R`: GPIO data register (read/write pin state)

### Using the Datasheet

Refer to `docs/tm4c123gh6pm.pdf` for:
- Complete register map and bit definitions
- Peripheral configuration details
- Memory map
- Clock configuration
- Interrupt vectors

## Customization

To use different LEDs or pins:

1. Check the datasheet for the pin's port and bit number
2. Modify the register access in `main.c`
3. Enable the appropriate port clock in `SYSCTL_RCGCGPIO_R`

Example for Blue LED (PF2):
```c
GPIO_PORTF_DIR_R |= (1 << 2);   // Set PF2 as output
GPIO_PORTF_DEN_R |= (1 << 2);   // Enable digital function
GPIO_PORTF_DATA_R |= (1 << 2);  // Turn on
```

## Troubleshooting

- **Build fails**: Check that ARM GCC is in your PATH
- **Flash fails**: Ensure board is connected and drivers are installed
- **LED doesn't blink**: Check connections and verify the correct pin is configured
- **Linker errors**: Verify the linker script matches your memory layout

## Next Steps

- Add more peripherals (UART, SPI, I2C, timers, etc.)
- Configure system clock to 80MHz
- Add interrupt handlers
- Implement more complex functionality

Refer to the datasheet for detailed register descriptions and peripheral configurations.
