/*
 * Register definitions for TM4C123GH6PM
 * Based on datasheet and TivaWare register definitions
 */

#ifndef TM4C123GH6PM_H
#define TM4C123GH6PM_H

#include <stdint.h>

/* System Control Registers */
#define SYSCTL_BASE           0x400FE000
#define SYSCTL_RCGCGPIO_R     (*((volatile uint32_t *)(SYSCTL_BASE + 0x608)))
#define SYSCTL_RCGCADC_R      (*((volatile uint32_t *)(SYSCTL_BASE + 0x638)))
#define SYSCTL_RCGCUART_R     (*((volatile uint32_t *)(SYSCTL_BASE + 0x618)))

/* GPIO Port A Registers (UART0) */
#define GPIO_PORTA_BASE       0x40004000
#define GPIO_PORTA_AFSEL_R    (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x420)))
#define GPIO_PORTA_PCTL_R     (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x52C)))
#define GPIO_PORTA_DEN_R      (*((volatile uint32_t *)(GPIO_PORTA_BASE + 0x51C)))

/* GPIO Port E Registers (ADC) */
#define GPIO_PORTE_BASE       0x40024000
#define GPIO_PORTE_AFSEL_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x420)))
#define GPIO_PORTE_DEN_R      (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x51C)))
#define GPIO_PORTE_AMSEL_R    (*((volatile uint32_t *)(GPIO_PORTE_BASE + 0x528)))

/* GPIO Port F Registers */
#define GPIO_PORTF_BASE       0x40025000
#define GPIO_PORTF_DATA_R     (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x3FC)))
#define GPIO_PORTF_DIR_R      (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x400)))
#define GPIO_PORTF_DEN_R      (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x51C)))
#define GPIO_PORTF_LOCK_R     (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x520)))
#define GPIO_PORTF_CR_R       (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x524)))

/* UART0 Registers */
#define UART0_BASE            0x4000C000
#define UART0_DR_R             (*((volatile uint32_t *)(UART0_BASE + 0x000)))
#define UART0_FR_R             (*((volatile uint32_t *)(UART0_BASE + 0x018)))
#define UART0_IBRD_R           (*((volatile uint32_t *)(UART0_BASE + 0x024)))
#define UART0_FBRD_R           (*((volatile uint32_t *)(UART0_BASE + 0x028)))
#define UART0_LCRH_R           (*((volatile uint32_t *)(UART0_BASE + 0x02C)))
#define UART0_CTL_R            (*((volatile uint32_t *)(UART0_BASE + 0x030)))

/* ADC0 Registers */
#define ADC0_BASE             0x40038000
#define ADC0_ACTSS_R           (*((volatile uint32_t *)(ADC0_BASE + 0x000)))
#define ADC0_RIS_R             (*((volatile uint32_t *)(ADC0_BASE + 0x004)))
#define ADC0_IM_R              (*((volatile uint32_t *)(ADC0_BASE + 0x008)))
#define ADC0_ISC_R             (*((volatile uint32_t *)(ADC0_BASE + 0x00C)))
#define ADC0_EMUX_R            (*((volatile uint32_t *)(ADC0_BASE + 0x014)))
#define ADC0_PSSI_R            (*((volatile uint32_t *)(ADC0_BASE + 0x028)))
#define ADC0_SSMUX0_R          (*((volatile uint32_t *)(ADC0_BASE + 0x040)))
#define ADC0_SSCTL0_R          (*((volatile uint32_t *)(ADC0_BASE + 0x044)))
#define ADC0_SSFIFO0_R         (*((volatile uint32_t *)(ADC0_BASE + 0x048)))

/* Constants */
#define GPIO_LOCK_KEY         0x4C4F434B  // Unlock key for GPIO
#define SYSCTL_RCGCGPIO_R0    (1 << 0)    // Port A clock enable
#define SYSCTL_RCGCGPIO_R4    (1 << 4)    // Port E clock enable
#define SYSCTL_RCGCGPIO_R5    (1 << 5)    // Port F clock enable
#define SYSCTL_RCGCADC_R0     (1 << 0)    // ADC0 clock enable
#define SYSCTL_RCGCUART_R0    (1 << 0)    // UART0 clock enable

#endif /* TM4C123GH6PM_H */
