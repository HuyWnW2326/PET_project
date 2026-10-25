#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

#include "gpio_regs.h"

/* GPIO configuration fields */
#define GPIO_CFG_ALLOWED_MASK                                                                      \
    (GPIO_INPUT | GPIO_CNF_MASK | GPIO_MODE_MASK | GPIO_INIT_HIGH | GPIO_PORT_MASK | GPIO_PIN_MASK)

/* STM32F103 GPIO configuration register fields */
#define GPIO_CR_FIELD_MASK (0xFUL)
#define GPIO_CR_FIELD_WIDTH (4U)

/* Number of GPIO pins per configuration register */
#define GPIO_CRL_PIN_COUNT (8U)

/**
 * @brief Get GPIO register base address from encoded port index.
 *
 * @param port GPIO port index.
 * @return GPIO_TypeDef pointer, or NULL for an unsupported port.
 */
static GPIO_TypeDef *GPIO_GetPort(uint32_t port)
{
    switch (port)
    {
    case 0U:
        return GPIOA;

    case 1U:
        return GPIOB;

    case 2U:
        return GPIOC;

    case 3U:
        return GPIOD;

    case 4U:
        return GPIOE;

    default:
        return (GPIO_TypeDef *)0;
    }
}

GPIO_Status_t GPIO_Config(uint32_t cfgset)
{
    if ((cfgset & ~GPIO_CFG_ALLOWED_MASK) != 0UL)
    {
        return GPIO_INVALID_CONFIG;
    }

    uint32_t port = (cfgset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
    uint32_t pin = (cfgset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

    GPIO_TypeDef *gpio = GPIO_GetPort(port);

    if (gpio == (GPIO_TypeDef *)0)
    {
        return GPIO_INVALID_CONFIG;
    }

    bool input = ((cfgset & GPIO_INPUT) != 0UL);

    uint32_t mode = (cfgset & GPIO_MODE_MASK) >> GPIO_MODE_SHIFT;
    uint32_t cnf = (cfgset & GPIO_CNF_MASK) >> GPIO_CNF_SHIFT;
    uint32_t mode_cnf;

    if (input)
    {
        /*
         * Input configurations must use MODE = 00.
         * CNF = 11 is reserved for input mode.
         */

        if ((mode != 0UL) || (cnf == 3UL))
        {
            return GPIO_INVALID_CONFIG;
        }

        mode_cnf = cnf << 2U;
    }
    else
    {
        /*
         * Output and alternate-function configurations
         * require MODE != 00.
         */

        if (mode == 0UL)
        {
            return GPIO_INVALID_CONFIG;
        }

        mode_cnf = (cnf << 2U) | mode;
    }

    volatile uint32_t *config_reg;
    uint32_t position;

    if (pin < GPIO_CRL_PIN_COUNT)
    {
        config_reg = &gpio->CRL;
        position = pin;
    }
    else
    {
        config_reg = &gpio->CRH;
        position = pin - GPIO_CRL_PIN_COUNT;
    }

    uint32_t shift = position * GPIO_CR_FIELD_WIDTH;

    /*
     * Prepare output state before enabling output.
     *
     * For input pull-up/pull-down, ODR selects the pull direction.
     * For general-purpose output, ODR selects the initial level.
     *
     * Alternate-function outputs are driven by peripherals.
     */

    if ((input && (cnf == 2UL)) || (!input && (cnf <= 1UL)))
    {
        if ((cfgset & GPIO_INIT_HIGH) != 0UL)
        {
            gpio->BSRR = (1UL << pin);
        }
        else
        {
            gpio->BSRR = (1UL << (pin + 16U));
        }
    }

    uint32_t register_value = *config_reg;

    register_value &= ~(GPIO_CR_FIELD_MASK << shift);

    register_value |= (mode_cnf << shift);

    *config_reg = register_value;

    return GPIO_OK;
}

void GPIO_Write(uint32_t pinset, GPIO_State_t state)
{
    uint32_t port = (pinset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
    uint32_t pin = (pinset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

    GPIO_TypeDef *gpio = GPIO_GetPort(port);

    if (gpio == (GPIO_TypeDef *)0)
    {
        return;
    }

    if (state == GPIO_HIGH)
    {
        gpio->BSRR = (1UL << pin);
    }
    else
    {
        gpio->BSRR = (1UL << (pin + 16U));
    }
}

GPIO_State_t GPIO_Read(uint32_t pinset)
{
    uint32_t port = (pinset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
    uint32_t pin = (pinset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

    GPIO_TypeDef *gpio = GPIO_GetPort(port);

    if (gpio == (GPIO_TypeDef *)0)
    {
        return GPIO_LOW;
    }

    if ((gpio->IDR & (1UL << pin)) != 0UL)
    {
        return GPIO_HIGH;
    }

    return GPIO_LOW;
}

void GPIO_Toggle(uint32_t pinset)
{
    uint32_t port = (pinset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
    uint32_t pin = (pinset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

    GPIO_TypeDef *gpio = GPIO_GetPort(port);

    if (gpio == (GPIO_TypeDef *)0)
    {
        return;
    }

    if ((gpio->ODR & (1UL << pin)) != 0UL)
    {
        gpio->BSRR = (1UL << (pin + 16U));
    }
    else
    {
        gpio->BSRR = (1UL << pin);
    }
}
