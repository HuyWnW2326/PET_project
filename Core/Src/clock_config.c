#include "clock_config.h"

#include <stdint.h>

#include "flash_regs.h"
#include "rcc_regs.h"

#define CLOCK_TIMEOUT 1000000UL

Clock_Status_t CLOCK_ConfigSystem(void)
{
    uint32_t timeout = CLOCK_TIMEOUT;

    /* Do not change PLL configuration while the PLL is running. */
    if ((RCC->CR & RCC_CR_PLLON) != 0U)
    {
        return CLOCK_ERROR_PLL;
    }

    RCC->CR |= RCC_CR_HSEON;

    while (((RCC->CR & RCC_CR_HSERDY) == 0U) && (timeout > 0U))
    {
        --timeout;
    }
    if ((RCC->CR & RCC_CR_HSERDY) == 0U)
    {
        return CLOCK_ERROR_HSE;
    }

    /* Set Flash timing before increasing SYSCLK to 72 MHz. */
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY_MSK) | FLASH_ACR_LATENCY_2WS | FLASH_ACR_PRFTBE;

    /* HSE / 1, PLL x9, HCLK / 1, PCLK1 / 2, and PCLK2 / 1. */
    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_HPRE_MSK | RCC_CFGR_PPRE1_MSK | RCC_CFGR_PPRE2_MSK |
                               RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL_MSK)) |
                RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_PLLSRC |
                RCC_CFGR_PLLMUL_X9;

    RCC->CR |= RCC_CR_PLLON;

    timeout = CLOCK_TIMEOUT;
    while (((RCC->CR & RCC_CR_PLLRDY) == 0U) && (timeout > 0U))
    {
        --timeout;
    }
    if ((RCC->CR & RCC_CR_PLLRDY) == 0U)
    {
        return CLOCK_ERROR_PLL;
    }

    RCC->CFGR &= ~RCC_CFGR_SW_MSK;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    timeout = CLOCK_TIMEOUT;
    while (((RCC->CFGR & RCC_CFGR_SWS_MSK) != RCC_CFGR_SWS_PLL) && (timeout > 0U))
    {
        --timeout;
    }
    if ((RCC->CFGR & RCC_CFGR_SWS_MSK) != RCC_CFGR_SWS_PLL)
    {
        return CLOCK_ERROR_SWITCH;
    }

    return CLOCK_OK;
}
