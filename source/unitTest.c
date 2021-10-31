/**************************
 *
 * @file    unitTest.h
 *
 * @brief   This file contains definition of functions to test the working of MSP430.
 *
 * @date    Oct 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/unitTest.h>


/**************************
 * @brief       This function converts decimal to binary
 *
 * @param [in]  hexVal, *outputStr, strLen
 *
 * @return      void
 **************************/
void decToBin(uint8_t hexVal, char *outputStr, uint8_t strLen)
{
    outputStr[strLen-1] = '\0';
    strLen--;
    while (hexVal > 0)
    {
        // storing remainder in binary array
        outputStr[strLen-1] = (hexVal & 0x01) + 48;
        hexVal >>= 1;
        strLen--;
    }
}


/**************************
 * @brief       This function tests output of MSP430 on initial power up
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testInitialPowerUpMode()
{
    uint8_t outputRecvd = 0;
    char outputData[9];
    char buffer[100];

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    //Set input direction
    gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
    gpioInit(PORT_B, PIN_4, OUTPUT);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Set output direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);

    //Provide initial input as 0
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), 0x00);
    gpioSet(PORT_E, PIN_4, 0x00);

    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
    outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
    outputRecvd |= gpioGet(PORT_E, PIN_0);

     decToBin(outputRecvd, outputData, 9);

    strcpy(buffer, "Input provided: 0000 \n");
    uartTxBytes(UART0_BASE, buffer, 22);

    strcpy(buffer,"Output received: ");
    uartTxBytes(UART0_BASE, buffer, 17);

    uartTxBytes(UART0_BASE, outputData, 8);

    if( outputRecvd == 255 )
    {
        strcpy(buffer, " => As Expected \n");
        uartTxBytes(UART0_BASE, outputData, 17);
    }
    else
    {
        strcpy(buffer, " => ERROR !!! \n");
        uartTxBytes(UART0_BASE, outputData, 15);

        strcpy(buffer, "Expected Output: 1111 1111\n");
        uartTxBytes(UART0_BASE, outputData, 27);
    }
}


/**************************
 * @brief       This function writes 1 byte of data to be transmitted via uart.
 *
 * @param [in]  uartBaseAdd, data
 *
 * @return      NULL
 **************************/
void testNormalMode()
{

}


/**************************
 * @brief       This function writes 1 byte of data to be transmitted via uart.
 *
 * @param [in]  uartBaseAdd, data
 *
 * @return      NULL
 **************************/
void testWrongPins()
{

}


/**************************
 * @brief       This function writes 1 byte of data to be transmitted via uart.
 *
 * @param [in]  uartBaseAdd, data
 *
 * @return      NULL
 **************************/
void testWrongPort()
{

}


/**************************
 * @brief       This function writes 1 byte of data to be transmitted via uart.
 *
 * @param [in]  uartBaseAdd, data
 *
 * @return      NULL
 **************************/
void testExtendedDataInput()
{

}






