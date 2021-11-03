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

extern volatile bool switchPressed;

int main(void)
{
    int i, j = 0;
    uint8_t input = 0;
    char buffer[50];

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    //Enable PortF for initializing SW-1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Initialize SW-1, & enable interrupt
    gpioInit(PORT_F, PIN_4, INPUT);
    GPIOPadConfigSet(PORT_F, PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    enableGpioInterrupt(PORT_F, PIN_4, GPIO_INT_PIN_4);

    //Configure UART
    uart_config_args_t uartConfigParam;

    uartConfigParam.port = PORT_A;
    uartConfigParam.rxPinNum = PIN_0;
    uartConfigParam.txPinNum = PIN_1;
    uartConfigParam.uartModule = UART_0;

    //Initialize UART
    uartInit(&uartConfigParam);

    while(1)
    {
        if(switchPressed == true)
        {
            //Run all test cases
            strcpy(buffer, "1. TEST CASE: NORMAL MODE.\n");
            uartTxBytes(UART0_BASE, buffer, strlen(buffer));
            for(input = 0; input < 16; input++)
            {
                testNormalMode(input);
            }

            strcpy(buffer, "\n2. TEST CASE: INPUT(0-15) SENT ON WRONG PINS OF PORT1 p4-p7.\n");
            uartTxBytes(UART0_BASE, buffer, strlen(buffer));

            for(input = 0; input < 16; input++)
            {
                testWrongPins(input);
            }

            strcpy(buffer, "\n3. TEST CASE: WRONG PORT INPUT MODE from p2.0-p2.7\n");
            uartTxBytes(UART0_BASE, buffer, strlen(buffer));

            for(i = 0; i <= 15; i++)
            {
                for(j = 0; j <= 15; j++)
                {
                    input = j | (i << 4);
                    testWrongPort(input);
                }
            }

            i = 0;
            j = 0;

            strcpy(buffer, "\n4. TEST CASE: EXTENDED INPUT MODE from p1.0-p1.7\n");
            uartTxBytes(UART0_BASE, buffer, strlen(buffer));

            for(i = 0; i <= 15; i++)
            {
                for(j = 0; j <= 15; j++)
                {
                    input = j | (i << 4);
                    testExtendedDataInput(input);
                }
            }

            switchPressed = false;
        }
    }
}
