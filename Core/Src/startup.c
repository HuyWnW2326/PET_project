#include <stdint.h>

#include "clock_config.h"

/* Linker-defined symbols retain their required external names. */
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sidata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

/**
 * @brief Initialize data and BSS, configure clocks, and enter main.
 * @note Reset entry point; halts on clock failure or if main returns.
 */
void Reset_Handler(void)
{
    uint32_t *source = &_sidata;
    uint32_t *destination = &_sdata;

    while (destination != &_edata)
    {
        *destination++ = *source++;
    }

    destination = &_sbss;
    while (destination != &_ebss)
    {
        *destination++ = 0;
    }

    Clock_Status_t clock_status = CLOCK_ConfigSystem();
    if (clock_status != CLOCK_OK)
    {
        for (;;)
        {
        }
    }

    main();
    for (;;)
    {
    }
}
