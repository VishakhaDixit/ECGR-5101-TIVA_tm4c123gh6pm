/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to implement 7 segment display values from 0-F for every change of potentiometer voltage.
 *
 * @date    Oct 21, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/unitTest.h>

int main(void)
{
    char buffer[256] = "Vishakha";

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    uart_config_args_t uartConfigParam;

    uartConfigParam.port = PORT_A;
    uartConfigParam.rxPinNum = PIN_0;
    uartConfigParam.txPinNum = PIN_1;
    uartConfigParam.uartModule = UART_0;

    uartInit(&uartConfigParam);

	while(1)
	{
	    uartTxBytes(UART0_BASE, buffer, sizeof(buffer));
	}
}
