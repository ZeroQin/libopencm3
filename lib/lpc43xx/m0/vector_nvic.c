/* This file is part of the libopencm3 project.
 *
 * It was generated by the irq2nvic_h script.
 *
 * This part needs to get included in the compilation unit where
 * blocking_handler gets defined due to the way #pragma works.
 */


/** @defgroup CM3_nvic_isrdecls_LPC43xx (M0) User interrupt service routines (ISR) defaults for LPC 43xx series M0 core
    @ingroup CM3_nvic_isrdecls

    @{*/

void rtc_isr(void) __attribute__((weak, alias("blocking_handler")));
void m4core_isr(void) __attribute__((weak, alias("blocking_handler")));
void dma_isr(void) __attribute__((weak, alias("blocking_handler")));
void flasheepromat_isr(void) __attribute__((weak, alias("blocking_handler")));
void ethernet_isr(void) __attribute__((weak, alias("blocking_handler")));
void sdio_isr(void) __attribute__((weak, alias("blocking_handler")));
void lcd_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb0_isr(void) __attribute__((weak, alias("blocking_handler")));
void usb1_isr(void) __attribute__((weak, alias("blocking_handler")));
void sct_isr(void) __attribute__((weak, alias("blocking_handler")));
void ritimer_or_wwdt_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer0_isr(void) __attribute__((weak, alias("blocking_handler")));
void gint1_isr(void) __attribute__((weak, alias("blocking_handler")));
void pin_int4_isr(void) __attribute__((weak, alias("blocking_handler")));
void timer3_isr(void) __attribute__((weak, alias("blocking_handler")));
void mcpwm_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc0_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2c0_or_irc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void sgpio_isr(void) __attribute__((weak, alias("blocking_handler")));
void spi_or_dac_isr(void) __attribute__((weak, alias("blocking_handler")));
void adc1_isr(void) __attribute__((weak, alias("blocking_handler")));
void ssp0_or_ssp1_isr(void) __attribute__((weak, alias("blocking_handler")));
void eventrouter_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart0_isr(void) __attribute__((weak, alias("blocking_handler")));
void uart1_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart2_or_c_can1_isr(void) __attribute__((weak, alias("blocking_handler")));
void usart3_isr(void) __attribute__((weak, alias("blocking_handler")));
void i2s0_or_i2s1_isr(void) __attribute__((weak, alias("blocking_handler")));
void c_can0_isr(void) __attribute__((weak, alias("blocking_handler")));

/**@}*/

/* Initialization template for the interrupt vector table. This definition is
 * used by the startup code generator (vector.c) to set the initial values for
 * the interrupt handling routines to the chip family specific _isr weak
 * symbols. */

#define IRQ_HANDLERS \
    [NVIC_RTC_IRQ] = rtc_isr, \
    [NVIC_M4CORE_IRQ] = m4core_isr, \
    [NVIC_DMA_IRQ] = dma_isr, \
    [NVIC_FLASHEEPROMAT_IRQ] = flasheepromat_isr, \
    [NVIC_ETHERNET_IRQ] = ethernet_isr, \
    [NVIC_SDIO_IRQ] = sdio_isr, \
    [NVIC_LCD_IRQ] = lcd_isr, \
    [NVIC_USB0_IRQ] = usb0_isr, \
    [NVIC_USB1_IRQ] = usb1_isr, \
    [NVIC_SCT_IRQ] = sct_isr, \
    [NVIC_RITIMER_OR_WWDT_IRQ] = ritimer_or_wwdt_isr, \
    [NVIC_TIMER0_IRQ] = timer0_isr, \
    [NVIC_GINT1_IRQ] = gint1_isr, \
    [NVIC_PIN_INT4_IRQ] = pin_int4_isr, \
    [NVIC_TIMER3_IRQ] = timer3_isr, \
    [NVIC_MCPWM_IRQ] = mcpwm_isr, \
    [NVIC_ADC0_IRQ] = adc0_isr, \
    [NVIC_I2C0_OR_IRC1_IRQ] = i2c0_or_irc1_isr, \
    [NVIC_SGPIO_IRQ] = sgpio_isr, \
    [NVIC_SPI_OR_DAC_IRQ] = spi_or_dac_isr, \
    [NVIC_ADC1_IRQ] = adc1_isr, \
    [NVIC_SSP0_OR_SSP1_IRQ] = ssp0_or_ssp1_isr, \
    [NVIC_EVENTROUTER_IRQ] = eventrouter_isr, \
    [NVIC_USART0_IRQ] = usart0_isr, \
    [NVIC_UART1_IRQ] = uart1_isr, \
    [NVIC_USART2_OR_C_CAN1_IRQ] = usart2_or_c_can1_isr, \
    [NVIC_USART3_IRQ] = usart3_isr, \
    [NVIC_I2S0_OR_I2S1_IRQ] = i2s0_or_i2s1_isr, \
    [NVIC_C_CAN0_IRQ] = c_can0_isr
