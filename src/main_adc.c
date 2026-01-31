/*
 * ADC and UART example for TM4C123GXL
 * Reads analog input (PE3/AIN0) every second and sends to serial monitor
 * Hardware: PE3 (AIN0) for ADC, PA0/PA1 for UART, 115200 baud
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"

void delay_1s(void) {
    volatile uint32_t i;
    for (i = 0; i < 8000000; i++);
}

void UART0_Init(void) {
    // Enable clocks
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    volatile uint32_t dummy = SYSCTL_RCGCUART_R;
    (void)dummy;
    
    // Configure UART: 115200 baud, 8N1
    UART0_CTL_R &= ~0x01;           // Disable during config
    UART0_IBRD_R = 8;                // Baud rate divisor
    UART0_FBRD_R = 44;
    UART0_LCRH_R = 0x70;             // 8 bits, 1 stop, no parity, FIFO
    UART0_CTL_R |= 0x01;             // Enable UART
    
    // Configure PA0/PA1 for UART
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x11;
    GPIO_PORTA_DEN_R |= 0x03;
}

void UART0_SendChar(char c) {
    while (UART0_FR_R & 0x20);       // Wait for TX ready
    UART0_DR_R = c;
}

void UART0_SendString(const char *s) {
    while (*s) UART0_SendChar(*s++);
}

void UART0_SendNumber(uint32_t n) {
    char buf[12];
    int i = 0;
    
    if (n == 0) {
        UART0_SendChar('0');
        return;
    }
    
    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }
    
    while (i > 0) UART0_SendChar(buf[--i]);
}

void ADC0_Init(void) {
    // Enable clocks
    SYSCTL_RCGCADC_R |= SYSCTL_RCGCADC_R0;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;
    volatile uint32_t dummy = SYSCTL_RCGCADC_R;
    (void)dummy;
    
    // Configure PE3 (AIN0) for ADC
    GPIO_PORTE_AFSEL_R &= ~0x08;
    GPIO_PORTE_DEN_R &= ~0x08;
    GPIO_PORTE_AMSEL_R |= 0x08;
    
    // Configure ADC sequencer 0
    ADC0_ACTSS_R &= ~0x01;           // Disable during config
    ADC0_EMUX_R &= ~0x0F;            // Software trigger
    ADC0_SSMUX0_R = 0;               // Channel 0 (AIN0)
    ADC0_SSCTL0_R = 0x06;            // Single sample, end
    ADC0_ACTSS_R |= 0x01;            // Enable sequencer
}

uint32_t ADC0_Read(void) {
    ADC0_PSSI_R |= 0x01;             // Start conversion
    while ((ADC0_RIS_R & 0x01) == 0); // Wait for done
    uint32_t result = ADC0_SSFIFO0_R & 0xFFF;
    ADC0_ISC_R |= 0x01;               // Clear flag
    return result;
}

int main(void) {
    UART0_Init();
    ADC0_Init();
    
    UART0_SendString("\r\nADC Example Started\r\n");
    UART0_SendString("Reading PE3 (AIN0)...\r\n");
    
    while (1) {
        UART0_SendString("ADC: ");
        UART0_SendNumber(ADC0_Read());
        UART0_SendString("\r\n");
        delay_1s();
    }
    
    return 0;
}
