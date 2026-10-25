#ifndef PET_CORE_INC_RCC_REGS_H
#define PET_CORE_INC_RCC_REGS_H

#include <stdint.h>

#include "common.h"

/**
 * @brief RCC register layout for STM32F103.
 */
typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

#define RCC_BASE (0x40021000UL)

#define RCC ((RCC_TypeDef *)RCC_BASE)

/* ============================================================
 * RCC_CR
 * ============================================================ */

#define RCC_CR_HSION BIT(0)
#define RCC_CR_HSIRDY BIT(1)
#define RCC_CR_HSEON BIT(16)
#define RCC_CR_HSERDY BIT(17)
#define RCC_CR_HSEBYP BIT(18)
#define RCC_CR_CSSON BIT(19)
#define RCC_CR_PLLON BIT(24)
#define RCC_CR_PLLRDY BIT(25)

/* ============================================================
 * RCC_CFGR - System clock selection
 * ============================================================ */

#define RCC_CFGR_SW_POS 0U
#define RCC_CFGR_SW_MSK (0x03U << RCC_CFGR_SW_POS)

#define RCC_CFGR_SW_HSI (0x00U << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_HSE (0x01U << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_PLL (0x02U << RCC_CFGR_SW_POS)

/* System clock switch status */

#define RCC_CFGR_SWS_POS 2U
#define RCC_CFGR_SWS_MSK (0x03U << RCC_CFGR_SWS_POS)

#define RCC_CFGR_SWS_HSI (0x00U << RCC_CFGR_SWS_POS)
#define RCC_CFGR_SWS_HSE (0x01U << RCC_CFGR_SWS_POS)
#define RCC_CFGR_SWS_PLL (0x02U << RCC_CFGR_SWS_POS)

/* ============================================================
 * RCC_CFGR - AHB prescaler
 * ============================================================ */

#define RCC_CFGR_HPRE_POS 4U
#define RCC_CFGR_HPRE_MSK (0x0FU << RCC_CFGR_HPRE_POS)

#define RCC_CFGR_HPRE_DIV1 (0x00U << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV2 (0x08U << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV4 (0x09U << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV8 (0x0AU << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV16 (0x0BU << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV64 (0x0CU << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV128 (0x0DU << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV256 (0x0EU << RCC_CFGR_HPRE_POS)
#define RCC_CFGR_HPRE_DIV512 (0x0FU << RCC_CFGR_HPRE_POS)

/* ============================================================
 * RCC_CFGR - APB1 prescaler
 * ============================================================ */

#define RCC_CFGR_PPRE1_POS 8U
#define RCC_CFGR_PPRE1_MSK (0x07U << RCC_CFGR_PPRE1_POS)

#define RCC_CFGR_PPRE1_DIV1 (0x00U << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV2 (0x04U << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV4 (0x05U << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV8 (0x06U << RCC_CFGR_PPRE1_POS)
#define RCC_CFGR_PPRE1_DIV16 (0x07U << RCC_CFGR_PPRE1_POS)

/* ============================================================
 * RCC_CFGR - APB2 prescaler
 * ============================================================ */

#define RCC_CFGR_PPRE2_POS 11U
#define RCC_CFGR_PPRE2_MSK (0x07U << RCC_CFGR_PPRE2_POS)

#define RCC_CFGR_PPRE2_DIV1 (0x00U << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV2 (0x04U << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV4 (0x05U << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV8 (0x06U << RCC_CFGR_PPRE2_POS)
#define RCC_CFGR_PPRE2_DIV16 (0x07U << RCC_CFGR_PPRE2_POS)

/* ============================================================
 * RCC_CFGR - PLL configuration
 * ============================================================ */

#define RCC_CFGR_PLLSRC BIT(16)
#define RCC_CFGR_PLLXTPRE BIT(17)

#define RCC_CFGR_PLLMUL_POS 18U
#define RCC_CFGR_PLLMUL_MSK (0x0FU << RCC_CFGR_PLLMUL_POS)

#define RCC_CFGR_PLLMUL_X2 (0x00U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X3 (0x01U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X4 (0x02U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X5 (0x03U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X6 (0x04U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X7 (0x05U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X8 (0x06U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X9 (0x07U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X10 (0x08U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X11 (0x09U << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X12 (0x0AU << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X13 (0x0BU << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X14 (0x0CU << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X15 (0x0DU << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_X16 (0x0EU << RCC_CFGR_PLLMUL_POS)

/* ============================================================
 * RCC_AHBENR
 * ============================================================ */

#define RCC_AHBENR_DMA1EN BIT(0)

/* ============================================================
 * RCC_APB1ENR
 * ============================================================ */

#define RCC_APB1ENR_TIM2EN BIT(0)
#define RCC_APB1ENR_TIM3EN BIT(1)
#define RCC_APB1ENR_TIM4EN BIT(2)

#define RCC_APB1ENR_SPI2EN BIT(14)

#define RCC_APB1ENR_USART2EN BIT(17)
#define RCC_APB1ENR_USART3EN BIT(18)

#define RCC_APB1ENR_I2C1EN BIT(21)
#define RCC_APB1ENR_I2C2EN BIT(22)

/* ============================================================
 * RCC_APB2ENR
 * ============================================================ */

#define RCC_APB2ENR_AFIOEN BIT(0)

#define RCC_APB2ENR_IOPAEN BIT(2)
#define RCC_APB2ENR_IOPBEN BIT(3)
#define RCC_APB2ENR_IOPCEN BIT(4)
#define RCC_APB2ENR_IOPDEN BIT(5)
#define RCC_APB2ENR_IOPEEN BIT(6)

#define RCC_APB2ENR_ADC1EN BIT(9)
#define RCC_APB2ENR_ADC2EN BIT(10)

#define RCC_APB2ENR_TIM1EN BIT(11)
#define RCC_APB2ENR_SPI1EN BIT(12)
#define RCC_APB2ENR_USART1EN BIT(14)

#endif /* PET_CORE_INC_RCC_REGS_H */
