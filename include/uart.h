/**************************
 *
 * @file    uart.h
 *
 * @brief   This file contains functions to initialize, tx, & rx messages using uart.
 *
 * @date    Oct 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#ifndef UART_H_
#define UART_H_

#include <include/common.h>

typedef enum uartSelect
{
    UART_0  = SYSCTL_PERIPH_UART0,
    UART_1  = SYSCTL_PERIPH_UART1,
    UART_2  = SYSCTL_PERIPH_UART2,
    UART_3  = SYSCTL_PERIPH_UART3,
    UART_4  = SYSCTL_PERIPH_UART4,
    UART_5  = SYSCTL_PERIPH_UART5,
    UART_6  = SYSCTL_PERIPH_UART6,
    UART_7  = SYSCTL_PERIPH_UART7
} uartSelect_e;

typedef struct uartConfigArgs
{
    port_e port;
    uartSelect_e uartModule;
    pin_num_e txPinNum;
    pin_num_e rxPinNum;
} uart_config_args_t;


void uartInit(uart_config_args_t *uart_config_params);

void uartTxBytes(uint32_t uartBaseAdd, char *buffer, int len);

void uartTxPacket(uint32_t uartBaseAdd, uint8_t data);

#endif /* UART_H_ */
