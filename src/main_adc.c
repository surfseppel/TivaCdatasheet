/*
 * ADC and UART example for TM4C123GXL Tiva C Launchpad
 * Reads analog input (PE3/AIN0) every second and sends to serial monitor
 * 
 * Hardware:
 * - ADC input: PE3 (AIN0) - connect potentiometer or analog sensor
 * - UART: UART0 on PA0 (RX) and PA1 (TX) - USB serial port
 * - Serial settings: 115200 baud, 8N1
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

// Simple delay function (approximate, ~1 second at 80MHz)
void delay_1s(void) {
    volatile uint32_t i;
    for (i = 0; i < 8000000; i++);  // Approximate 1 second delay
}

// Initialize UART0 for serial communication
void UART0_Init(void) {
    // Enable clocks for UART0 and Port A
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    
    // Wait for clocks to stabilize
    volatile uint32_t dummy = SYSCTL_RCGCUART_R;
    dummy = SYSCTL_RCGCGPIO_R;
    (void)dummy;
    
    // Disable UART0 during configuration
    UART0_CTL_R &= ~0x00000001;
    
    // Configure baud rate: 115200 (assuming 16MHz UART clock)
    // IBRD = 16,000,000 / (16 * 115200) = 8.6805...
    // FBRD = round(64 * 0.6805) = 44
    // Note: UART clock is typically 16MHz by default (before PLL configuration)
    UART0_IBRD_R = 8;
    UART0_FBRD_R = 44;
    
    // Configure line control: 8 bits, 1 stop bit, no parity, FIFO enabled
    UART0_LCRH_R = 0x00000070;
    
    // Configure Port A pins 0 and 1 for UART
    GPIO_PORTA_AFSEL_R |= 0x03;      // Enable alternate function on PA0 and PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;  // UART function
    GPIO_PORTA_DEN_R |= 0x03;        // Enable digital function
    
    // Enable UART0
    UART0_CTL_R |= 0x00000001;
}

// Send a character via UART0
void UART0_SendChar(char data) {
    // Wait until transmit FIFO is not full
    while (UART0_FR_R & 0x00000020);
    UART0_DR_R = data;
}

// Send a string via UART0
void UART0_SendString(const char *str) {
    while (*str) {
        UART0_SendChar(*str);
        str++;
    }
}

// Convert number to string and send via UART
void UART0_SendNumber(uint32_t num) {
    char buffer[12];
    int i = 0;
    
    if (num == 0) {
        UART0_SendChar('0');
        return;
    }
    
    // Convert to string (reverse order)
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    // Send in correct order
    while (i > 0) {
        UART0_SendChar(buffer[--i]);
    }
}

// Initialize ADC0
void ADC0_Init(void) {
    // Enable clocks for ADC0 and Port E
    SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    
    // Wait for clocks to stabilize
    volatile uint32_t dummy = SYSCTL_RCGCADC_R;
    dummy = SYSCTL_RCGCGPIO_R;
    (void)dummy;
    
    // Configure PE3 (AIN0) for ADC
    // For ADC: disable digital, enable analog, AFSEL not needed
    GPIO_PORTE_AFSEL_R &= ~0x08;     // Clear alternate function (not needed for ADC)
    GPIO_PORTE_DEN_R &= ~0x08;       // Disable digital function on PE3
    GPIO_PORTE_AMSEL_R |= 0x08;      // Enable analog function on PE3
    
    // Disable ADC0 sequencer 0 during configuration
    ADC0_ACTSS_R &= ~0x0001;
    
    // Configure sequencer 0 for single sample
    ADC0_EMUX_R &= ~0x000F;          // Software trigger
    ADC0_SSMUX0_R = 0x0000;          // Sample channel 0 (AIN0/PE3)
    ADC0_SSCTL0_R = 0x0006;          // Single sample, end of sequence
    
    // Enable ADC0 sequencer 0
    ADC0_ACTSS_R |= 0x0001;
}

// Read ADC value (0-4095 for 12-bit ADC)
uint32_t ADC0_Read(void) {
    // Start conversion
    ADC0_PSSI_R |= 0x0001;
    
    // Wait for conversion to complete
    while ((ADC0_RIS_R & 0x0001) == 0);
    
    // Read result
    uint32_t result = ADC0_SSFIFO0_R & 0xFFF;
    
    // Clear interrupt flag
    ADC0_ISC_R |= 0x0001;
    
    return result;
}

int main(void) {
    // Initialize UART for serial communication
    UART0_Init();
    
    // Initialize ADC
    ADC0_Init();
    
    // Send startup message
    UART0_SendString("\r\nADC Example Started\r\n");
    UART0_SendString("Reading analog input on PE3 (AIN0)...\r\n");
    UART0_SendString("Values (0-4095):\r\n");
    
    // Main loop: read ADC and send to serial every second
    while (1) {
        // Read ADC value
        uint32_t adc_value = ADC0_Read();
        
        // Send to serial monitor
        UART0_SendString("ADC: ");
        UART0_SendNumber(adc_value);
        UART0_SendString("\r\n");
        
        // Wait 1 second
        delay_1s();
    }
    
    return 0;
}
