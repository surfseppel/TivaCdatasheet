/*
 * Startup code for TM4C123GXL
 * Initializes stack pointer and calls main()
 */

extern void main(void);
extern void SystemInit(void);
extern unsigned long _estack;

// Reset handler
void Reset_Handler(void) {
    // Initialize data and BSS sections
    SystemInit();
    
    // Call main
    main();
    
    // Infinite loop if main returns
    while(1);
}

// Default interrupt handler
void Default_Handler(void) {
    while(1);
}

// Minimal vector table (first 16 entries required)
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))((unsigned long)&_estack),  // Initial stack pointer
    Reset_Handler,                               // Reset handler
    Default_Handler,                             // NMI
    Default_Handler,                             // Hard fault
    Default_Handler,                             // MPU fault
    Default_Handler,                             // Bus fault
    Default_Handler,                             // Usage fault
    0,                                           // Reserved
    0,                                           // Reserved
    0,                                           // Reserved
    0,                                           // Reserved
    Default_Handler,                             // SVCall
    Default_Handler,                             // Debug monitor
    0,                                           // Reserved
    Default_Handler,                             // PendSV
    Default_Handler                              // SysTick
};
