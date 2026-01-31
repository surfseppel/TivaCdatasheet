/*
 * System initialization for TM4C123GXL
 * Basic system setup functions
 */

#include <stdint.h>

// External symbols from linker script
extern unsigned long _sidata;  // Start of initialized data in FLASH
extern unsigned long _sdata;   // Start of data section in RAM
extern unsigned long _edata;   // End of data section in RAM
extern unsigned long _sbss;   // Start of BSS section
extern unsigned long _ebss;    // End of BSS section

// Initialize data section (copy from flash to RAM)
void SystemInit(void) {
    unsigned long *src, *dst;
    
    // Copy initialized data from flash to RAM
    src = &_sidata;
    dst = &_sdata;
    while (dst < &_edata) {
        *dst++ = *src++;
    }
    
    // Zero out BSS section
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }
}
