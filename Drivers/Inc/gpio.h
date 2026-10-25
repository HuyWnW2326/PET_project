#ifndef PET_DRIVERS_INC_GPIO_H
#define PET_DRIVERS_INC_GPIO_H

/**
 * @file    gpio.h
 * @brief   GPIO driver interface for STM32F103.
 *
 * @details
 * GPIO configuration is encoded into a 32-bit unsigned integer (cfgset).
 * The encoding is inspired by Apache NuttX STM32F1 GPIO configuration.
 *
 * GPIO Configuration Bit Layout:
 *
 *  31                  16 15  14 13  12 11  10  9 8   7    6 5 4   3 2 1 0
 * +----------------------+---+-----+-----+----+-----+----+-------+---------+
 * |       Reserved       | I | CNF |MODE |EXTI| Res |INIT| PORT  |   PIN   |
 * +----------------------+---+-----+-----+----+-----+----+-------+---------+
 *
 * Field Description:
 *
 *  Bits    Field    Description
 *  --------------------------------------------------------------------------
 *  31:16   Reserved Unused, must be zero.
 *  15      INPUT    0: Output / Alternate Function
 *                   1: Input
 *  14:13   CNF      GPIO configuration (CNF[1:0]).
 *  12:11   MODE     GPIO output speed (MODE[1:0]).
 *                   Must be zero for input configurations.
 *  10      EXTI     Unsupported; must be zero.
 *   9:8    Reserved Unused, must be zero.
 *   7      INIT     0: Initial LOW / Pull-down
 *                   1: Initial HIGH / Pull-up
 *   6:4    PORT     GPIO port index (A=0, B=1, C=2, ...).
 *   3:0    PIN      GPIO pin number (0-15).
 *
 * GPIO Hardware Configuration:
 *
 *  CNF[1:0]  MODE[1:0]  Configuration
 *  --------------------------------------------------------------------------
 *     00         00      Analog input
 *     01         00      Floating input
 *     10         00      Input pull-up / pull-down
 *     00         !=00    General purpose output push-pull
 *     01         !=00    General purpose output open-drain
 *     10         !=00    Alternate function output push-pull
 *     11         !=00    Alternate function output open-drain
 *
 * Output Speed:
 *
 *  MODE[1:0] = 01 : 10 MHz
 *  MODE[1:0] = 10 :  2 MHz
 *  MODE[1:0] = 11 : 50 MHz
 *
 * Example:
 *
 *  GPIO_Config(GPIO_PORTC |
 *              GPIO_PIN13 |
 *              GPIO_OUTPUT |
 *              GPIO_CNF_OUT_PP |
 *              GPIO_MODE_2MHZ |
 *              GPIO_INIT_HIGH);
 *
 * Notes:
 *  - GPIO peripheral clock must be enabled before configuration.
 *  - EXTI and AFIO remapping are not supported in this version.
 *  - Only the lower 16 bits are currently used.
 *
 */

#include <stdint.h>

/* GPIO Configuration Encoding */

/* Input / Output Selection */

#define GPIO_INPUT (1UL << 15)
#define GPIO_OUTPUT (0UL)
#define GPIO_ALT (0UL)

/* Configuration Field: Bits 13-14 */

#define GPIO_CNF_SHIFT (13U)
#define GPIO_CNF_MASK (3UL << GPIO_CNF_SHIFT)

/* Input Configuration */

#define GPIO_CNF_ANALOG (0UL << GPIO_CNF_SHIFT)
#define GPIO_CNF_FLOATING (1UL << GPIO_CNF_SHIFT)
#define GPIO_CNF_PULLDOWN (2UL << GPIO_CNF_SHIFT)
#define GPIO_CNF_PULLUP ((2UL << GPIO_CNF_SHIFT) | GPIO_INIT_HIGH)

/* Output Configuration */

#define GPIO_CNF_OUT_PP (0UL << GPIO_CNF_SHIFT)
#define GPIO_CNF_OUT_OD (1UL << GPIO_CNF_SHIFT)

/* Alternate Function Configuration */

#define GPIO_CNF_AF_PP (2UL << GPIO_CNF_SHIFT)
#define GPIO_CNF_AF_OD (3UL << GPIO_CNF_SHIFT)

/* Mode Field: Bits 11-12 */

#define GPIO_MODE_SHIFT (11U)
#define GPIO_MODE_MASK (3UL << GPIO_MODE_SHIFT)

#define GPIO_MODE_INPUT (0UL << GPIO_MODE_SHIFT)
#define GPIO_MODE_10MHZ (1UL << GPIO_MODE_SHIFT)
#define GPIO_MODE_2MHZ (2UL << GPIO_MODE_SHIFT)
#define GPIO_MODE_50MHZ (3UL << GPIO_MODE_SHIFT)

/* Initial Output State: Bit 7 */

#define GPIO_INIT_LOW (0UL)
#define GPIO_INIT_HIGH (1UL << 7)

/* GPIO Port Field: Bits 4-6 */

#define GPIO_PORT_SHIFT (4U)
#define GPIO_PORT_MASK (7UL << GPIO_PORT_SHIFT)

#define GPIO_PORTA (0UL << GPIO_PORT_SHIFT)
#define GPIO_PORTB (1UL << GPIO_PORT_SHIFT)
#define GPIO_PORTC (2UL << GPIO_PORT_SHIFT)
#define GPIO_PORTD (3UL << GPIO_PORT_SHIFT)
#define GPIO_PORTE (4UL << GPIO_PORT_SHIFT)

/* GPIO Pin Field: Bits 0-3 */

#define GPIO_PIN_SHIFT (0U)
#define GPIO_PIN_MASK (15UL << GPIO_PIN_SHIFT)

#define GPIO_PIN0 (0UL << GPIO_PIN_SHIFT)
#define GPIO_PIN1 (1UL << GPIO_PIN_SHIFT)
#define GPIO_PIN2 (2UL << GPIO_PIN_SHIFT)
#define GPIO_PIN3 (3UL << GPIO_PIN_SHIFT)
#define GPIO_PIN4 (4UL << GPIO_PIN_SHIFT)
#define GPIO_PIN5 (5UL << GPIO_PIN_SHIFT)
#define GPIO_PIN6 (6UL << GPIO_PIN_SHIFT)
#define GPIO_PIN7 (7UL << GPIO_PIN_SHIFT)
#define GPIO_PIN8 (8UL << GPIO_PIN_SHIFT)
#define GPIO_PIN9 (9UL << GPIO_PIN_SHIFT)
#define GPIO_PIN10 (10UL << GPIO_PIN_SHIFT)
#define GPIO_PIN11 (11UL << GPIO_PIN_SHIFT)
#define GPIO_PIN12 (12UL << GPIO_PIN_SHIFT)
#define GPIO_PIN13 (13UL << GPIO_PIN_SHIFT)
#define GPIO_PIN14 (14UL << GPIO_PIN_SHIFT)
#define GPIO_PIN15 (15UL << GPIO_PIN_SHIFT)

/**
 * @brief GPIO operation status.
 */
typedef enum
{
    GPIO_OK = 0,
    GPIO_ERROR,
    GPIO_INVALID_CONFIG
} GPIO_Status_t;

/**
 * @brief GPIO logic state.
 */
typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} GPIO_State_t;

/* Public APIs */

/**
 * @brief Configure a GPIO pin using bit-encoded configuration.
 *
 * @param cfgset Encoded GPIO configuration.
 * @return GPIO_OK on success; GPIO_INVALID_CONFIG for unsupported bits, port,
 *         or mode/configuration combinations.
 *
 * @note Enable the GPIO peripheral clock before calling. Updates CRL/CRH and,
 *       when applicable, the output latch. Does not wait for hardware readiness.
 *       Serialize configuration of pins sharing a configuration register; the
 *       read-modify-write sequence is not safe against concurrent configuration.
 */
GPIO_Status_t GPIO_Config(uint32_t cfgset);

/**
 * @brief Write a logic level to a GPIO pin.
 *
 * @param pinset Encoded GPIO port and pin.
 * @param state GPIO_HIGH sets the pin; any other value resets it.
 * @note Enable the GPIO clock and configure the pin before calling. Uses a
 *       single BSRR write without polling; unsupported ports are ignored.
 *       Concurrent writes to the same pin still require caller coordination.
 */
void GPIO_Write(uint32_t pinset, GPIO_State_t state);

/**
 * @brief Read the physical logic level of a GPIO pin.
 *
 * @param pinset Encoded GPIO port and pin.
 * @return GPIO_HIGH or GPIO_LOW from IDR; GPIO_LOW for an unsupported port.
 * @note Enable the GPIO clock before calling. Samples IDR without polling
 *       or changing configuration; it does not synchronize with pin writers.
 */
GPIO_State_t GPIO_Read(uint32_t pinset);

/**
 * @brief Toggle the output state of a GPIO pin.
 *
 * @param pinset Encoded GPIO port and pin.
 * @note Enable the GPIO clock and configure the pin before calling. Reads ODR
 *       then writes BSRR without polling; unsupported ports are ignored.
 *       Serialize access with other writers, including interrupt handlers.
 */
void GPIO_Toggle(uint32_t pinset);

#endif /* PET_DRIVERS_INC_GPIO_H */
