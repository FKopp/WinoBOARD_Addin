/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011-2014, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following condition is met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _MAIN_H_
#define _MAIN_H_


#define CPU_FREQUENCY                     8000000

#define WAIT_SHORT                        150000 // 100k = 1.5s
#define WAIT_LONG                         4000000 // 1M = 15s

#define ESP8266_CH_PD_PIN                 PIN_PA11
#define ESP8266_CH_PD_PIN_MASK           (1U << (ESP8266_CH_PD_PIN & 0x1f))
#define LED_PIN                           PIN_PA16
#define LED_PIN_MASK                     (1U << (LED_PIN & 0x1f))
#define LED_PORT                         (LED_PIN / 32)
#define LED_ON                            PORT->Group[LED_PORT].OUTSET.reg = LED_PIN_MASK
#define LED_OFF                           PORT->Group[LED_PORT].OUTCLR.reg = LED_PIN_MASK
#define LED_TOGGLE                        PORT->Group[LED_PORT].OUTTGL.reg = LED_PIN_MASK

#define DEBUG_SERCOM                      SERCOM1
#define DEBUG_USART_MUX_SETTINGS          UART_RX_PAD3_TX_PAD2
#define DEBUG_USART_PAD3                  PINMUX_PA19C_SERCOM1_PAD3
#define DEBUG_USART_PAD2                  PINMUX_PA18C_SERCOM1_PAD2
#define DEBUG_USART_PAD1                  PINMUX_UNUSED
#define DEBUG_USART_PAD0                  PINMUX_UNUSED
//#define DEBUG_USART_OPEN                  debug_usart_open();
//#define DEBUG_WRITE(val)                  uart_write_byte(DEBUG_SERCOM, val)
#define DEBUG_USART_OPEN                  if (0)
#define DEBUG_WRITE(val)                  if (0)

#define FLASH_WAIT_STATES                 1

//#define BOOT_USART_PIN                    PIN_PA14 // If this pin is low at the startup, bootlader should work in USART mode
#define BOOT_USART_MODULE                 SERCOM3
#define BOOT_USART_MUX_SETTINGS           UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD3                   PINMUX_UNUSED
#define BOOT_USART_PAD2                   PINMUX_UNUSED
#define BOOT_USART_PAD1                   PINMUX_PA23C_SERCOM3_PAD1
#define BOOT_USART_PAD0                   PINMUX_PA22C_SERCOM3_PAD0


#endif // _MAIN_H_
