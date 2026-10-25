#ifndef PET_CORE_INC_FLASH_REGS_H
#define PET_CORE_INC_FLASH_REGS_H

#include <stdint.h>

#include "common.h"

/**
 * @brief Flash access-control register layout for STM32F103.
 */
typedef struct
{
    volatile uint32_t ACR;
} FLASH_TypeDef;

#define FLASH_BASE (0x40022000UL)

#define FLASH ((FLASH_TypeDef *)FLASH_BASE)

#define FLASH_ACR_LATENCY_POS 0x00U
#define FLASH_ACR_LATENCY_MSK (0x07U << FLASH_ACR_LATENCY_POS)
#define FLASH_ACR_LATENCY_1WS (0x01U << FLASH_ACR_LATENCY_POS)
#define FLASH_ACR_LATENCY_2WS (0x02U << FLASH_ACR_LATENCY_POS)

#define FLASH_ACR_HLFCYA BIT(3)
#define FLASH_ACR_PRFTBE BIT(4)
#define FLASH_ACR_PRFTBS BIT(5)

#endif /* PET_CORE_INC_FLASH_REGS_H */
