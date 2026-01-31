/*
 * Blink example for TM4C123GXL Tiva C Launchpad
 * Direct register access - no SDK required
 * 
 * This example blinks the on-board Red LED (PF1)
 * The LED is connected to Port F, Pin 1
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Simple delay function (approximate, not calibrated)
void delay(uint32_t count) {
    volatile uint32_t i;
    for (i = 0; i < count * 10000; i++);
}

int main(void) {
    // Enable clock to Port F
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    
    // Wait for clock to stabilize (dummy read)
    volatile uint32_t dummy = SYSCTL_RCGCGPIO_R;
    (void)dummy;  // Suppress unused variable warning
    
    // Unlock Port F (required for PF0)
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R = 0x1F;  // Allow changes to PF0-PF4
    
    // Configure PF1 (Red LED) as output
    GPIO_PORTF_DIR_R |= (1 << 1);   // Set PF1 as output
    GPIO_PORTF_DEN_R |= (1 << 1);   // Enable digital function on PF1
    // Initialize LED off (using mask-based access at offset 0x3FC)
    GPIO_PORTF_DATA_R &= ~(1 << 1);
    
    // Main loop - blink LED
    while (1) {
        // Turn LED on (set PF1 high)
        GPIO_PORTF_DATA_R |= (1 << 1);
        delay(500);
        
        // Turn LED off (set PF1 low)
        GPIO_PORTF_DATA_R &= ~(1 << 1);
        delay(500);
    }
    
    return 0;
}
