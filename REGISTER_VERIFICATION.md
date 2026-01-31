# Register Verification for TM4C123GH6PM

This document verifies that all register addresses and usage match the datasheet.

## Base Addresses (Verified)

### System Control (SYSCTL)
- **Base**: `0x400FE000` ✓
- **RCGCGPIO**: `0x608` offset ✓
- **RCGCADC**: `0x638` offset ✓
- **RCGCUART**: `0x618` offset ✓

### GPIO Ports
- **Port A Base**: `0x40004000` ✓
- **Port E Base**: `0x40024000` ✓
- **Port F Base**: `0x40025000` ✓

### UART0
- **Base**: `0x4000C000` ✓
- **DR**: `0x000` offset ✓
- **FR**: `0x018` offset ✓
- **IBRD**: `0x024` offset ✓
- **FBRD**: `0x028` offset ✓
- **LCRH**: `0x02C` offset ✓
- **CTL**: `0x030` offset ✓

### ADC0
- **Base**: `0x40038000` ✓
- **ACTSS**: `0x000` offset ✓
- **RIS**: `0x004` offset ✓
- **IM**: `0x008` offset ✓
- **ISC**: `0x00C` offset ✓
- **EMUX**: `0x014` offset ✓
- **PSSI**: `0x028` offset ✓
- **SSMUX0**: `0x040` offset ✓
- **SSCTL0**: `0x044` offset ✓
- **SSFIFO0**: `0x048` offset ✓

## GPIO Register Offsets (Verified)

- **DATA** (mask-based): `0x3FC` ✓ (Correct for bit-specific access)
- **DIR**: `0x400` offset ✓
- **AFSEL**: `0x420` offset ✓
- **PCTL**: `0x52C` offset ✓
- **AMSEL**: `0x528` offset ✓
- **DEN**: `0x51C` offset ✓
- **LOCK**: `0x520` offset ✓
- **CR**: `0x524` offset ✓

## Issues Found and Fixed

### 1. ADC Pin Configuration (FIXED)
**Issue**: AFSEL was being set for ADC pin PE3
**Fix**: AFSEL should be cleared (0) for ADC pins. Only AMSEL needs to be set.
**Location**: `src/main_adc.c` line 101

### 2. GPIO DATA Register Usage (VERIFIED)
**Status**: Correct - Using mask-based access at offset 0x3FC
**Usage**: Bit-specific read-modify-write operations are correct

### 3. UART Baud Rate (VERIFIED)
**Status**: Correct for 16MHz UART clock
**Calculation**: IBRD=8, FBRD=44 gives 115200 baud ✓

### 4. ADC Sequencer Configuration (VERIFIED)
**Status**: Correct
- EMUX bits 3:0 = 0 (software trigger) ✓
- SSMUX0 = 0 (channel 0 = AIN0/PE3) ✓
- SSCTL0 = 0x06 (single sample, end of sequence) ✓

## Register Usage Patterns

### GPIO Initialization Sequence (Correct)
1. Enable clock in SYSCTL_RCGCGPIO_R ✓
2. Wait for clock stabilization ✓
3. Unlock port (if needed, e.g., Port F) ✓
4. Set DIR register ✓
5. Set DEN register ✓
6. Use DATA register for I/O ✓

### UART Initialization Sequence (Correct)
1. Enable UART and GPIO clocks ✓
2. Disable UART during configuration ✓
3. Configure baud rate (IBRD, FBRD) ✓
4. Configure line control (LCRH) ✓
5. Configure GPIO pins (AFSEL, PCTL, DEN) ✓
6. Enable UART ✓

### ADC Initialization Sequence (Correct)
1. Enable ADC and GPIO clocks ✓
2. Configure GPIO pin (clear AFSEL, clear DEN, set AMSEL) ✓
3. Disable sequencer during configuration ✓
4. Configure sequencer (EMUX, SSMUX, SSCTL) ✓
5. Enable sequencer ✓

## Constants (Verified)

- **GPIO_LOCK_KEY**: `0x4C4F434B` ✓ (ASCII "LOCK")
- **Clock enable bits**: Correct bit positions ✓

## Summary

All register addresses match the TM4C123GH6PM datasheet. One configuration issue was found and fixed:
- ADC pin configuration now correctly clears AFSEL instead of setting it

All other register usage is correct according to the datasheet.
