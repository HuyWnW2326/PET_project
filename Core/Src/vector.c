#include <stdint.h>

/* Linker-defined initial stack address; the external name is required. */
extern uint32_t _estack;

/**
 * @brief Halt indefinitely for an unhandled exception or interrupt.
 */
void Default_Handler(void)
{
    while (1)
    {
    }
}

void Reset_Handler(void);

/* IRQ names and weak aliases are required by the interrupt interface. */
#define WEAK_ALIAS __attribute__((weak, alias("Default_Handler")))

/* Core exception handlers. */
void NMI_Handler(void) WEAK_ALIAS;
void HardFault_Handler(void) WEAK_ALIAS;
void MemManage_Handler(void) WEAK_ALIAS;
void BusFault_Handler(void) WEAK_ALIAS;
void UsageFault_Handler(void) WEAK_ALIAS;

void SVC_Handler(void) WEAK_ALIAS;
void DebugMon_Handler(void) WEAK_ALIAS;
void PendSV_Handler(void) WEAK_ALIAS;
void SysTick_Handler(void) WEAK_ALIAS;

/* External interrupt handlers. */
void WWDG_IRQHandler(void) WEAK_ALIAS;
void PVD_IRQHandler(void) WEAK_ALIAS;
void TAMPER_IRQHandler(void) WEAK_ALIAS;
void RTC_IRQHandler(void) WEAK_ALIAS;
void FLASH_IRQHandler(void) WEAK_ALIAS;
void RCC_IRQHandler(void) WEAK_ALIAS;

void EXTI0_IRQHandler(void) WEAK_ALIAS;
void EXTI1_IRQHandler(void) WEAK_ALIAS;
void EXTI2_IRQHandler(void) WEAK_ALIAS;
void EXTI3_IRQHandler(void) WEAK_ALIAS;
void EXTI4_IRQHandler(void) WEAK_ALIAS;

void DMA1_Channel1_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel2_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel3_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel4_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel5_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel6_IRQHandler(void) WEAK_ALIAS;
void DMA1_Channel7_IRQHandler(void) WEAK_ALIAS;

void ADC1_2_IRQHandler(void) WEAK_ALIAS;
void USB_HP_CAN_TX_IRQHandler(void) WEAK_ALIAS;
void USB_LP_CAN_RX0_IRQHandler(void) WEAK_ALIAS;
void CAN_RX1_IRQHandler(void) WEAK_ALIAS;
void CAN_SCE_IRQHandler(void) WEAK_ALIAS;

void EXTI9_5_IRQHandler(void) WEAK_ALIAS;

void TIM1_BRK_IRQHandler(void) WEAK_ALIAS;
void TIM1_UP_IRQHandler(void) WEAK_ALIAS;
void TIM1_TRG_COM_IRQHandler(void) WEAK_ALIAS;
void TIM1_CC_IRQHandler(void) WEAK_ALIAS;

void TIM2_IRQHandler(void) WEAK_ALIAS;
void TIM3_IRQHandler(void) WEAK_ALIAS;
void TIM4_IRQHandler(void) WEAK_ALIAS;

void I2C1_EV_IRQHandler(void) WEAK_ALIAS;
void I2C1_ER_IRQHandler(void) WEAK_ALIAS;
void I2C2_EV_IRQHandler(void) WEAK_ALIAS;
void I2C2_ER_IRQHandler(void) WEAK_ALIAS;

void SPI1_IRQHandler(void) WEAK_ALIAS;
void SPI2_IRQHandler(void) WEAK_ALIAS;

void USART1_IRQHandler(void) WEAK_ALIAS;
void USART2_IRQHandler(void) WEAK_ALIAS;
void USART3_IRQHandler(void) WEAK_ALIAS;

void EXTI15_10_IRQHandler(void) WEAK_ALIAS;
void RTC_Alarm_IRQHandler(void) WEAK_ALIAS;
void USBWakeUp_IRQHandler(void) WEAK_ALIAS;

/**
 * @brief Initial stack address and handlers in hardware-defined vector order.
 * @note Consumed at reset; reserved entries remain zero.
 */
__attribute__((used, section(".isr_vector"))) const uintptr_t vector_table[] = {
    /* Core exception handlers. */
    (uintptr_t)&_estack,           // 0  Initial MSP
    (uintptr_t)Reset_Handler,      // 1  Reset
    (uintptr_t)NMI_Handler,        // 2  NMI
    (uintptr_t)HardFault_Handler,  // 3  HardFault
    (uintptr_t)MemManage_Handler,  // 4  MemManage
    (uintptr_t)BusFault_Handler,   // 5  BusFault
    (uintptr_t)UsageFault_Handler, // 6  UsageFault

    0, // 7  Reserved
    0, // 8  Reserved
    0, // 9  Reserved
    0, // 10 Reserved

    (uintptr_t)SVC_Handler,      // 11 SVCall
    (uintptr_t)DebugMon_Handler, // 12 Debug Monitor

    0, // 13 Reserved

    (uintptr_t)PendSV_Handler,  // 14 PendSV
    (uintptr_t)SysTick_Handler, // 15 SysTick

    /* External interrupt handlers. */
    (uintptr_t)WWDG_IRQHandler,   // IRQ 0
    (uintptr_t)PVD_IRQHandler,    // IRQ 1
    (uintptr_t)TAMPER_IRQHandler, // IRQ 2
    (uintptr_t)RTC_IRQHandler,    // IRQ 3
    (uintptr_t)FLASH_IRQHandler,  // IRQ 4
    (uintptr_t)RCC_IRQHandler,    // IRQ 5

    (uintptr_t)EXTI0_IRQHandler, // IRQ 6
    (uintptr_t)EXTI1_IRQHandler, // IRQ 7
    (uintptr_t)EXTI2_IRQHandler, // IRQ 8
    (uintptr_t)EXTI3_IRQHandler, // IRQ 9
    (uintptr_t)EXTI4_IRQHandler, // IRQ 10

    (uintptr_t)DMA1_Channel1_IRQHandler, // IRQ 11
    (uintptr_t)DMA1_Channel2_IRQHandler, // IRQ 12
    (uintptr_t)DMA1_Channel3_IRQHandler, // IRQ 13
    (uintptr_t)DMA1_Channel4_IRQHandler, // IRQ 14
    (uintptr_t)DMA1_Channel5_IRQHandler, // IRQ 15
    (uintptr_t)DMA1_Channel6_IRQHandler, // IRQ 16
    (uintptr_t)DMA1_Channel7_IRQHandler, // IRQ 17

    (uintptr_t)ADC1_2_IRQHandler, // IRQ 18

    (uintptr_t)USB_HP_CAN_TX_IRQHandler,  // IRQ 19
    (uintptr_t)USB_LP_CAN_RX0_IRQHandler, // IRQ 20
    (uintptr_t)CAN_RX1_IRQHandler,        // IRQ 21
    (uintptr_t)CAN_SCE_IRQHandler,        // IRQ 22

    (uintptr_t)EXTI9_5_IRQHandler, // IRQ 23

    (uintptr_t)TIM1_BRK_IRQHandler,     // IRQ 24
    (uintptr_t)TIM1_UP_IRQHandler,      // IRQ 25
    (uintptr_t)TIM1_TRG_COM_IRQHandler, // IRQ 26
    (uintptr_t)TIM1_CC_IRQHandler,      // IRQ 27

    (uintptr_t)TIM2_IRQHandler, // IRQ 28
    (uintptr_t)TIM3_IRQHandler, // IRQ 29
    (uintptr_t)TIM4_IRQHandler, // IRQ 30

    (uintptr_t)I2C1_EV_IRQHandler, // IRQ 31
    (uintptr_t)I2C1_ER_IRQHandler, // IRQ 32
    (uintptr_t)I2C2_EV_IRQHandler, // IRQ 33
    (uintptr_t)I2C2_ER_IRQHandler, // IRQ 34

    (uintptr_t)SPI1_IRQHandler, // IRQ 35
    (uintptr_t)SPI2_IRQHandler, // IRQ 36

    (uintptr_t)USART1_IRQHandler, // IRQ 37
    (uintptr_t)USART2_IRQHandler, // IRQ 38
    (uintptr_t)USART3_IRQHandler, // IRQ 39

    (uintptr_t)EXTI15_10_IRQHandler, // IRQ 40
    (uintptr_t)RTC_Alarm_IRQHandler, // IRQ 41
    (uintptr_t)USBWakeUp_IRQHandler  // IRQ 42
};
