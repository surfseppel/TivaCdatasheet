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

/* GPIO Port F Registers */
#define GPIO_PORTF_BASE       0x40025000
#define GPIO_PORTF_DATA_R     (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x3FC)))
#define GPIO_PORTF_DIR_R      (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x400)))
#define GPIO_PORTF_DEN_R      (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x51C)))
#define GPIO_PORTF_LOCK_R     (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x520)))
#define GPIO_PORTF_CR_R       (*((volatile uint32_t *)(GPIO_PORTF_BASE + 0x524)))

/* Constants */
#define GPIO_LOCK_KEY         0x4C4F434B  // Unlock key for GPIO
#define SYSCTL_RCGCGPIO_R5    (1 << 5)    // Port F clock enable

#endif /* TM4C123GH6PM_H */
