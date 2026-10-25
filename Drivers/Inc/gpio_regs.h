#ifndef PET_DRIVERS_INC_GPIO_REGS_H
#define PET_DRIVERS_INC_GPIO_REGS_H

#include <stdint.h>

/**
 * @brief GPIO register layout for STM32F103.
 */
typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

/* GPIO Base Addresses */

#define GPIOA_BASE (0x40010800UL)
#define GPIOB_BASE (0x40010C00UL)
#define GPIOC_BASE (0x40011000UL)
#define GPIOD_BASE (0x40011400UL)
#define GPIOE_BASE (0x40011800UL)

/* GPIO Peripheral Pointers */

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)

#endif /* PET_DRIVERS_INC_GPIO_REGS_H */
