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
    uint8_t portASetInp, portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;
    char outputData[9];
    char buffer[100];

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //Provide initial input
    if(testCase == NORMAL_MODE)
    {
        //Set output direction
        gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
        gpioInit(PORT_E, (PIN_4), OUTPUT);

        portBSetInp = (input & 0x06) >> 1;
        portBSetInp |= (input & 0x01) << 5;

        portESetInp = (input & 0x08) << 1;

        gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), portBSetInp);
        gpioSet(PORT_E, PIN_4, portESetInp);
    }

    else if(testCase == INP_WRONG_PINS)
    {
        //Set output direction
        gpioInit(PORT_B, (PIN_4 | PIN_6 | PIN_7), OUTPUT);
        gpioInit(PORT_E, (PIN_5), OUTPUT);

        portESetInp = (input & 0x01) << 5;

        portBSetInp = (input & 0x02) << 3;
        portBSetInp |= (input & 0x0C) << 4;

        gpioSet(PORT_B, (PIN_4 | PIN_6 | PIN_7), portBSetInp);
        gpioSet(PORT_E, PIN_5, portESetInp);
    }

    else if(testCase == EXTENDED_INP_MODE)
    {
        //Set output direction
        gpioInit(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), OUTPUT);
        gpioInit(PORT_E, (PIN_4 | PIN_5), OUTPUT);

        portBSetInp = (input & 0x06) >> 1;
        portBSetInp |= (input & 0x01) << 5;
        portBSetInp |= (input & 0x20) >> 1;
        portBSetInp |= (input & 0xC0);

        portESetInp = (input & 0x18) << 1;

        gpioSet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), portBSetInp);
        gpioSet(PORT_E, (PIN_4 | PIN_5), portESetInp);
    }
    else
    {
        //Set output direction
        gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), OUTPUT);
        gpioInit(PORT_B, PIN_2, OUTPUT);
        gpioInit(PORT_E, PIN_0, OUTPUT);

        portASetInp = (input & 0x07) << 5;
        portASetInp |= (input & 0x38) >> 1;

        portBSetInp = (input & 0x40) >> 4;
        portESetInp = (input & 0x80) >> 7;

        gpioSet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), portASetInp);
        gpioSet(PORT_B, PIN_2, portBSetInp);
        gpioSet(PORT_E, PIN_0, portESetInp);
    }

    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    if( (testCase == NORMAL_MODE) || (testCase == INP_WRONG_PINS) ||(testCase == EXTENDED_INP_MODE) )
    {
        //Set input direction
        gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
        gpioInit(PORT_B, PIN_2, INPUT);
        gpioInit(PORT_E, PIN_0, INPUT);

        outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
        outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
        outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
        outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;
    }
    else
    {
        //Set input direction
        gpioInit(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
        gpioInit(PORT_E, (PIN_4 | PIN_5), INPUT);

        outputRecvd += gpioGet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
        outputRecvd = ( ((outputRecvd & 0x03) << 1) | ((outputRecvd & 0x20) >> 5) |
                      ((outputRecvd & 0x10) << 1) | (outputRecvd & 0xC0) );
        outputRecvd += (gpioGet(PORT_E, (PIN_4 | PIN_5)) & 0x18) >> 1;
    }

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
        strcpy(buffer, " => PASS !!! \n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));
    }
    else
    {
        strcpy(buffer, " => FAIL !!! ");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        strcpy(buffer, "Expected Output: 0b");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        decToBin(expectedOp, outputData);
        uartTxBytes(UART0_BASE, outputData, 8);
    }
}


/**************************
 * @brief       This function tests output of MSP430 for all inputs from 0-F.
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
 * @brief       This function tests output of MSP430 for all inputs from 0-F set on
 *              wrong pins.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testWrongPins()
{
    char buffer[100];
    uint8_t input = 0;
    uint8_t expectedOp = 0;

    strcpy(buffer, "2. TEST CASE: INPUT(0-15) SENT ON WRONG PINS OF PORT1 p4-p7.\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    strcpy(buffer, "EXPECTED RESULT: MUST RETAIN DEFAULT STATE\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    expectedOp = 0xFF;

    for(input = 0; input < 16; input++)
    {
        testMspIoModes(INP_WRONG_PINS, input, expectedOp);
    }
}


/**************************
 * @brief       This function tests output of MSP430 for all inputs from 0-F set on
 *              wrong port.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testWrongPort()
{
    uint8_t i,j = 0;
    char buffer[100];
    uint8_t input = 0;
    uint8_t expectedOp = 0;

        strcpy(buffer, "3. TEST CASE: WRONG PORT INPUT MODE from p2.0-p2.7\n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        expectedOp = 0x00;

        for(i = 0; i <= 15; i++)
        {
            for(j = 0; j <= 15; j++)
            {
                input = j | (i << 4);
                testMspIoModes(INP_WRONG_PORT, input, expectedOp);
            }
        }
}


/**************************
 * @brief       This function tests output of MSP430 for extended 8-bit input
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testExtendedDataInput()
{
    uint8_t i,j = 0;
    char buffer[100];
    uint8_t input = 0;
    uint8_t expectedOp = 0;

    strcpy(buffer, "4. TEST CASE: EXTENDED INPUT MODE from p1.0-p1.7\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    for(i = 0; i <= 15; i++)
    {
        for(j = 0; j <= 15; j++)
        {
            input = j | (i << 4);

            switch(input & 0x0F)
            {
            case 8:
                expectedOp = 0x01;
                break;
            case 9:
                expectedOp = 0x02;
                break;
            case 10:
                expectedOp = 0x04;
                break;
            case 11:
                expectedOp = 0x08;
                break;
            case 12:
                expectedOp = 0x10;
                break;
            case 13:
                expectedOp = 0x20;
                break;
            case 14:
                expectedOp = 0x40;
                break;
            case 15:
                expectedOp = 0x80;
                break;
            default:
                expectedOp = 0xFF;
                break;
            }

            testMspIoModes(EXTENDED_INP_MODE, input, expectedOp);
        }
    }
}
