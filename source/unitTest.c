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
 * @param [in]  decVal, *outputStr, strLen
 *
 * @return      void
 **************************/
static void decToBin(uint8_t decVal, char *outputStr)
{
    uint8_t strLen = 9;
    outputStr[strLen-1] = '\0';
    strLen--;
    while (strLen > 0)
    {
        // storing remainder in binary array
        if(decVal > 0)
        {
            outputStr[strLen-1] = (decVal & 0x01) + 48;
            decVal >>= 1;
            strLen--;
        }
        else
        {
            outputStr[strLen-1] = 48;
            strLen--;
        }
    }
}


/**************************
 * @brief       This function tests output of MSP430 based on the input provided
 *
 * @param [in]  isExtendedInp, input, expectedOp
 *
 * @return      NULL
 **************************/
void testMspIoModes(testCaseSelect_e testCase, uint8_t input, uint8_t expectedOp)
{
    uint8_t portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;
    char outputData[9];
    char buffer[100];

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Set input direction
    gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
    gpioInit(PORT_E, PIN_4, OUTPUT);

    //Set output direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);

    //Provide initial input
    if(testCase == NORMAL_MODE)
    {
        portBSetInp = (input & 0x06) >> 1;
        portBSetInp |= (input & 0x01) <<5;

        portESetInp = (input & 0x08) << 1;
    }
    else if(testCase == INP_WRONG_PINS)
    {

    }

    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), portBSetInp);
    gpioSet(PORT_E, PIN_4, portESetInp);

    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
    outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
    outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;

    strcpy(buffer, "\nInput provided: 0b");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    decToBin(input, outputData);
    uartTxBytes(UART0_BASE, outputData, 8);

    strcpy(buffer,", Output received: 0b");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    decToBin(outputRecvd, outputData);
    uartTxBytes(UART0_BASE, outputData, 8);

    if( outputRecvd == expectedOp )
    {
        strcpy(buffer, " => As Expected \n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));
    }
    else
    {
        strcpy(buffer, " => ERROR !!! \n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        strcpy(buffer, "Expected Output: 0b");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        decToBin(expectedOp, outputData);
        uartTxBytes(UART0_BASE, outputData, 8);
    }
}


/**************************
 * @brief       This function tests output of MSP430 for all inputs from 0 - F.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testNormalMode()
{
    char buffer[100];
    uint8_t input = 0;
    uint8_t expectedOp;

    strcpy(buffer, "1. TEST CASE: NORMAL MODE.\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    for(input = 0; input < 16; input++)
    {
        if(input < 8)
        {
            expectedOp = 0xFF;
        }
        else
        {
            expectedOp = 1 << (input - 8);
        }

        testMspIoModes(NORMAL_MODE, input, expectedOp);
    }
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
    char buffer[100];
    uint8_t input = 0;
    uint8_t expectedOp;

    strcpy(buffer, "1. TEST CASE: INPUT(0-15) SENT ON WRONG PINS OF PORT1 p4-p7.\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    strcpy(buffer, "EXPECTED RESULT: MUST RETAIN PREVIOUS STATE\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    for(input = 0; input < 16; input++)
    {
        if(input < 8)
        {
            expectedOp = 0xFF;
        }
        else
        {
            expectedOp = 1 << (input - 8);
        }

        testMspIoModes(INP_WRONG_PINS, input, expectedOp);
    }
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






