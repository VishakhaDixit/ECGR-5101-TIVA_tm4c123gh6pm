/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to implement unit test cases to test the functioning of MSP430 and display corresponding results in terminal using UART.
 *
 * @date    Oct 21, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/unitTest.h>

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    uart_config_args_t uartConfigParam;

    uartConfigParam.port = PORT_A;
    uartConfigParam.rxPinNum = PIN_0;
    uartConfigParam.txPinNum = PIN_1;
    uartConfigParam.uartModule = UART_0;

    uartInit(&uartConfigParam);
    testNormalMode();

	while(1)
	{
	}
}
