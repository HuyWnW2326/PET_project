#ifndef PET_CORE_INC_RCC_H
#define PET_CORE_INC_RCC_H

#include <stdint.h>

/**
 * @brief RCC bus identifiers.
 *
 * Peripheral ID encoding:
 *
 * Bits [7:5] : RCC bus
 * Bits [4:0] : Peripheral bit position
 */
#define RCC_BUS_APB1 0U
#define RCC_BUS_APB2 1U
#define RCC_BUS_AHB 2U

#define RCC_PERIPH_ID(bus, bit) (((bus) << 5U) | (bit))

/**
 * @brief RCC peripheral identifiers.
 */
typedef enum
{
    /* AHB peripherals */
    RCC_PERIPH_DMA1 = RCC_PERIPH_ID(RCC_BUS_AHB, 0),

    /* APB2 - AFIO */
    RCC_PERIPH_AFIO = RCC_PERIPH_ID(RCC_BUS_APB2, 0),

    /* APB2 - GPIO */
    RCC_PERIPH_GPIOA = RCC_PERIPH_ID(RCC_BUS_APB2, 2),
    RCC_PERIPH_GPIOB = RCC_PERIPH_ID(RCC_BUS_APB2, 3),
    RCC_PERIPH_GPIOC = RCC_PERIPH_ID(RCC_BUS_APB2, 4),
    RCC_PERIPH_GPIOD = RCC_PERIPH_ID(RCC_BUS_APB2, 5),
    RCC_PERIPH_GPIOE = RCC_PERIPH_ID(RCC_BUS_APB2, 6),

    /* APB2 - USART */
    RCC_PERIPH_USART1 = RCC_PERIPH_ID(RCC_BUS_APB2, 14),

    /* APB1 - USART */
    RCC_PERIPH_USART2 = RCC_PERIPH_ID(RCC_BUS_APB1, 17),
    RCC_PERIPH_USART3 = RCC_PERIPH_ID(RCC_BUS_APB1, 18),

    /* SPI */
    RCC_PERIPH_SPI1 = RCC_PERIPH_ID(RCC_BUS_APB2, 12),
    RCC_PERIPH_SPI2 = RCC_PERIPH_ID(RCC_BUS_APB1, 14),

    /* I2C */
    RCC_PERIPH_I2C1 = RCC_PERIPH_ID(RCC_BUS_APB1, 21),
    RCC_PERIPH_I2C2 = RCC_PERIPH_ID(RCC_BUS_APB1, 22),

    /* Timers */
    RCC_PERIPH_TIM1 = RCC_PERIPH_ID(RCC_BUS_APB2, 11),
    RCC_PERIPH_TIM2 = RCC_PERIPH_ID(RCC_BUS_APB1, 0),
    RCC_PERIPH_TIM3 = RCC_PERIPH_ID(RCC_BUS_APB1, 1),
    RCC_PERIPH_TIM4 = RCC_PERIPH_ID(RCC_BUS_APB1, 2),

    /* ADC */
    RCC_PERIPH_ADC1 = RCC_PERIPH_ID(RCC_BUS_APB2, 9),
    RCC_PERIPH_ADC2 = RCC_PERIPH_ID(RCC_BUS_APB2, 10)

} RCC_Peripheral_t;

/**
 * @brief RCC operation status.
 */
typedef enum
{
    RCC_OK = 0,
    RCC_ERROR_INVALID_PERIPHERAL,
    RCC_ERROR_UNSUPPORTED_OPERATION

} RCC_Status_t;

/**
 * @brief Enable a peripheral clock.
 * @note Reads back the enable register before returning. No readiness polling.
 *       Serialize RCC register updates with other callers and interrupts.
 *
 * @param peripheral Peripheral identifier.
 *
 * @return RCC_OK on success, RCC_ERROR_INVALID_PERIPHERAL for an unknown ID,
 *         or RCC_ERROR_UNSUPPORTED_OPERATION if the bus has no enable register.
 */
RCC_Status_t RCC_EnableClock(RCC_Peripheral_t peripheral);

/**
 * @brief Disable a peripheral clock.
 * @note Stops the peripheral clock without waiting for ongoing transfers.
 *       Serialize RCC register updates with other callers and interrupts.
 *
 * @param peripheral Peripheral identifier.
 *
 * @return RCC_OK on success, RCC_ERROR_INVALID_PERIPHERAL for an unknown ID,
 *         or RCC_ERROR_UNSUPPORTED_OPERATION if the bus has no enable register.
 */
RCC_Status_t RCC_DisableClock(RCC_Peripheral_t peripheral);

/**
 * @brief Reset peripheral through RCC reset register.
 *
 * @note AHB peripherals such as DMA1 do not support
 *       this reset mechanism.
 *
 * @param peripheral Peripheral identifier.
 *
 * @return RCC_OK on success, RCC_ERROR_INVALID_PERIPHERAL for an unknown ID,
 *         or RCC_ERROR_UNSUPPORTED_OPERATION for an unsupported reset bus.
 * @note Asserts reset, reads back the register, then releases reset without
 *       polling. Peripheral state is reset. Serialize RCC register updates
 *       with other callers and interrupts.
 */
RCC_Status_t RCC_ResetPeripheral(RCC_Peripheral_t peripheral);

#endif /* PET_CORE_INC_RCC_H */
