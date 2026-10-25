#include "rcc.h"

#include <stdint.h>

#include "rcc_regs.h"

#define RCC_GET_BUS(peripheral_id) (((uint32_t)(peripheral_id) >> 5U) & 0x07U)

#define RCC_GET_BIT(peripheral_id) (((uint32_t)(peripheral_id)) & 0x1FU)

/**
 * @brief Check whether a peripheral ID is supported.
 */
static uint8_t RCC_IsValidPeripheral(RCC_Peripheral_t peripheral)
{
    switch (peripheral)
    {
    /* AHB */
    case RCC_PERIPH_DMA1:

    /* GPIO */
    case RCC_PERIPH_GPIOA:
    case RCC_PERIPH_GPIOB:
    case RCC_PERIPH_GPIOC:
    case RCC_PERIPH_GPIOD:
    case RCC_PERIPH_GPIOE:

    /* AFIO */
    case RCC_PERIPH_AFIO:

    /* USART */
    case RCC_PERIPH_USART1:
    case RCC_PERIPH_USART2:
    case RCC_PERIPH_USART3:

    /* SPI */
    case RCC_PERIPH_SPI1:
    case RCC_PERIPH_SPI2:

    /* I2C */
    case RCC_PERIPH_I2C1:
    case RCC_PERIPH_I2C2:

    /* Timers */
    case RCC_PERIPH_TIM1:
    case RCC_PERIPH_TIM2:
    case RCC_PERIPH_TIM3:
    case RCC_PERIPH_TIM4:

    /* ADC */
    case RCC_PERIPH_ADC1:
    case RCC_PERIPH_ADC2:
        return 1U;

    default:
        return 0U;
    }
}

/**
 * @brief Get peripheral clock enable register.
 */
static volatile uint32_t *RCC_GetEnableRegister(uint32_t bus)
{
    switch (bus)
    {
    case RCC_BUS_APB1:
        return &RCC->APB1ENR;

    case RCC_BUS_APB2:
        return &RCC->APB2ENR;

    case RCC_BUS_AHB:
        return &RCC->AHBENR;

    default:
        return (volatile uint32_t *)0;
    }
}

/**
 * @brief Get peripheral reset register.
 *
 * @note STM32F103 does not provide an AHB reset
 *       register corresponding to RCC_AHBENR.
 */
static volatile uint32_t *RCC_GetResetRegister(uint32_t bus)
{
    switch (bus)
    {
    case RCC_BUS_APB1:
        return &RCC->APB1RSTR;

    case RCC_BUS_APB2:
        return &RCC->APB2RSTR;

    default:
        return (volatile uint32_t *)0;
    }
}

RCC_Status_t RCC_EnableClock(RCC_Peripheral_t peripheral)
{
    if (RCC_IsValidPeripheral(peripheral) == 0U)
    {
        return RCC_ERROR_INVALID_PERIPHERAL;
    }

    uint32_t peripheral_bus = RCC_GET_BUS(peripheral);
    uint32_t peripheral_bit = RCC_GET_BIT(peripheral);

    volatile uint32_t *register_address = RCC_GetEnableRegister(peripheral_bus);

    if (register_address == (volatile uint32_t *)0)
    {
        return RCC_ERROR_UNSUPPORTED_OPERATION;
    }

    *register_address |= (1UL << peripheral_bit);

    /*
     * Readback ensures the clock enable write
     * has reached the RCC register before
     * subsequent peripheral accesses.
     */
    (void)*register_address;

    return RCC_OK;
}

RCC_Status_t RCC_DisableClock(RCC_Peripheral_t peripheral)
{
    if (RCC_IsValidPeripheral(peripheral) == 0U)
    {
        return RCC_ERROR_INVALID_PERIPHERAL;
    }

    uint32_t peripheral_bus = RCC_GET_BUS(peripheral);
    uint32_t peripheral_bit = RCC_GET_BIT(peripheral);

    volatile uint32_t *register_address = RCC_GetEnableRegister(peripheral_bus);

    if (register_address == (volatile uint32_t *)0)
    {
        return RCC_ERROR_UNSUPPORTED_OPERATION;
    }

    *register_address &= ~(1UL << peripheral_bit);

    return RCC_OK;
}

RCC_Status_t RCC_ResetPeripheral(RCC_Peripheral_t peripheral)
{
    if (RCC_IsValidPeripheral(peripheral) == 0U)
    {
        return RCC_ERROR_INVALID_PERIPHERAL;
    }

    uint32_t peripheral_bus = RCC_GET_BUS(peripheral);
    uint32_t peripheral_bit = RCC_GET_BIT(peripheral);

    volatile uint32_t *register_address = RCC_GetResetRegister(peripheral_bus);

    if (register_address == (volatile uint32_t *)0)
    {
        return RCC_ERROR_UNSUPPORTED_OPERATION;
    }

    *register_address |= (1UL << peripheral_bit);

    /* Readback ensures the reset assertion reaches RCC. */
    (void)*register_address;

    *register_address &= ~(1UL << peripheral_bit);

    return RCC_OK;
}
