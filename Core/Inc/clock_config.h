#ifndef PET_CORE_INC_CLOCK_CONFIG_H
#define PET_CORE_INC_CLOCK_CONFIG_H

/**
 * @brief System clock configuration status.
 */
typedef enum
{
    CLOCK_OK = 0,
    CLOCK_ERROR_HSE,
    CLOCK_ERROR_PLL,
    CLOCK_ERROR_SWITCH
} Clock_Status_t;

/**
 * @brief Configure the system clock to use the 72 MHz PLL clock.
 *
 * Requires an 8 MHz HSE source and a disabled PLL. Configures SYSCLK/HCLK at
 * 72 MHz, APB1 at 36 MHz, APB2 at 72 MHz, and Flash latency at two wait states.
 * Each readiness wait is bounded by 1000000 polling iterations, not a time unit.
 * Call during startup before interrupts or concurrent clock-register access.
 * Failure may leave partially configured clocks and Flash timing in place.
 *
 * @return CLOCK_OK on success, or a clock configuration error.
 */
Clock_Status_t CLOCK_ConfigSystem(void);

#endif /* PET_CORE_INC_CLOCK_CONFIG_H */
