/**************************
 *
 * @file    uart.c
 *
 * @brief   This file contains definition of functions to initialize, tx, & rx messages using uart.
 *
 * @date    Oct 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/uart.h>


/**************************
 * @brief       This function initializes the UART module.
 *
 * @param [in]  *uart_config_params
 *
 * @return      NULL
 **************************/
void uartInit(uart_config_args_t *uart_config_params)
{
    uint32_t uartBaseAdd;

    switch(uart_config_params->uartModule)
    {
    case(UART_1):
        uartBaseAdd = UART1_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        GPIOPinConfigure(GPIO_PC4_U1RX);
        GPIOPinConfigure(GPIO_PC5_U1TX);
        break;
    case(UART_2):
        uartBaseAdd = UART2_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinConfigure(GPIO_PD6_U2RX);
        GPIOPinConfigure(GPIO_PD7_U2TX);
        break;
    case(UART_3):
        uartBaseAdd = UART3_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        GPIOPinConfigure(GPIO_PC6_U3RX);
        GPIOPinConfigure(GPIO_PC7_U3TX);
        break;
    case(UART_4):
        uartBaseAdd = UART4_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        GPIOPinConfigure(GPIO_PC4_U4RX);
        GPIOPinConfigure(GPIO_PC5_U4TX);
        break;
    case(UART_5):
        uartBaseAdd = UART5_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinConfigure(GPIO_PE4_U5RX);
        GPIOPinConfigure(GPIO_PE5_U5TX);
        break;
    case(UART_6):
        uartBaseAdd = UART6_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
        GPIOPinConfigure(GPIO_PD4_U6RX);
        GPIOPinConfigure(GPIO_PD5_U6TX);
        break;
    case(UART_7):
        uartBaseAdd = UART7_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        GPIOPinConfigure(GPIO_PE0_U7RX);
        GPIOPinConfigure(GPIO_PE1_U7TX);
        break;
    default:
        uartBaseAdd = UART0_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        break;
    }

    GPIOPinTypeUART(uart_config_params->port, uart_config_params->rxPinNum | uart_config_params->txPinNum);

    UARTConfigSetExpClk(uartBaseAdd, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
}


/**************************
 * @brief       This function writes bytes of data of size len to be transmitted via UART module.
 *
 * @param [in]  uartBaseAdd, *buffer, len
 *
 * @return      NULL
 **************************/
void uartTxBytes(uint32_t uartBaseAdd, char *buffer, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        uartTxPacket(uartBaseAdd, buffer[i]);
    }
}


/**************************
 * @brief       This function writes 1 byte of data to be transmitted via uart.
 *
 * @param [in]  uartBaseAdd, data
 *
 * @return      NULL
 **************************/
void uartTxPacket(uint32_t uartBaseAdd, uint8_t data)
{
    UARTCharPut(uartBaseAdd, data);
    while(UARTBusy(uartBaseAdd));
}




