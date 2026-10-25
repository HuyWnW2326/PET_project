#include "gpio.h"
#include "rcc.h"

#define LED_CONFIG                                                                                 \
    (GPIO_PORTC | GPIO_PIN13 | GPIO_OUTPUT | GPIO_CNF_OUT_PP | GPIO_MODE_2MHZ | GPIO_INIT_HIGH)

/**
 * @brief Stores the result of the application clock-enable request.
 *
 * @note Owned by main and not shared with interrupt handlers.
 */
volatile RCC_Status_t g_rcc_status;

/**
 * @brief Configure the application LED pin and remain in the main loop.
 * @note This function does not return.
 */
int main(void)
{
    g_rcc_status = RCC_EnableClock(RCC_PERIPH_GPIOC);
    GPIO_Status_t status = GPIO_Config(LED_CONFIG);

    if (status != GPIO_OK)
    {
        while (1)
        {
            /* Halt if GPIO configuration fails. */
        }
    }

    while (1)
    {
    }
}
