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
    uint8_t portBSetInp, portESetInp, portASetInp;
    uint8_t outputRecvd = 0;
    char outputData[9];
    char buffer[100];

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    if(testCase == INP_WRONG_PORT)
    {
        gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), OUTPUT);
        gpioInit(PORT_B, PIN_2, OUTPUT);
        gpioInit(PORT_E, PIN_0, OUTPUT);
        //reading input from P1.0 to P1.7
        gpioInit(PORT_B, (PIN_7 | PIN_6 | PIN_4 | PIN_1 | PIN_0 | PIN_5), OUTPUT);
        gpioInit(PORT_E, (PIN_4 | PIN_5), OUTPUT);

    }
    else
    {
    //Set output direction
    gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
    //gpioInit(PORT_B, (PIN_7 | PIN_6 | PIN_4), OUTPUT);
    //Because p1.4 -pe5, p1.5 pb4, p1.6 - pb6, p1.7 - pb7
    gpioInit(PORT_E, (PIN_4 | PIN_5), OUTPUT);
    //Set input direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);
    }

    //Provide initial input
    if(testCase == NORMAL_MODE)
    {
        portBSetInp = (input & 0x06) >> 1;
        portBSetInp |= (input & 0x01) << 5;

        portESetInp = (input & 0x08) << 1;
    }

    else if(testCase == INP_WRONG_PINS)
    {
        portESetInp = (input & 0x01) << 5;

        portBSetInp = (input & 0x02) << 3; // pb5 is connected to p1.0 , we need pb4 here, so <<2?
        portBSetInp |= (input & 0x0C) << 4;
    }

    else if(testCase == EXTENDED_INP_MODE)
    {
        portBSetInp = (input & 0x06) >> 1;
        portBSetInp |= (input & 0x01) << 5;
        portBSetInp |= (input & 0x20) >> 1;
        portBSetInp |= (input & 0xC0);

        portESetInp = (input & 0x18) << 1;
    }
    else if(testCase == INP_WRONG_PORT)
       {
           portASetInp = (input & 0x38) >> 1;
           portASetInp |= (input & 0x07) << 5;
           portBSetInp = (input & 0x40)>>6;
           portESetInp = (input & 0x80) >> 7;
           gpioSet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7),portASetInp);
       }
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), portBSetInp);
    gpioSet(PORT_E, PIN_4, portESetInp);


    SysCtlDelay((SysCtlClockGet() * 1) / 3);
    if(testCase == INP_WRONG_PORT)
    {
      outputRecvd += gpioGet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
      //check this part pls
      outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
      outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
      outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;
    }
   else
   {
    outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
    outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
    outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;
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

        strcpy(buffer, "4. TEST CASE: WRONG PORT INPUT MODE from p1.0-p1.7\n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));

        for(i = 0; i <= 15; i++)
        {
            for(j = 0; j <= 15; j++)
            {
                input = j | (i << 4);
                expectedOp = 0x00;
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

    strcpy(buffer, "3. TEST CASE: EXTENDED INPUT MODE from p1.0-p1.7\n");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    for(i = 0; i <= 15; i++)
    {
        for(j = 0; j <= 15; j++)
        {
            input = j | (i << 4);

            if((input & 0x0F) < 8)
            {
                expectedOp = 0xFF;
            }
            else
            {
                expectedOp = 1 << (input - 8);
            }

            testMspIoModes(EXTENDED_INP_MODE, input, expectedOp);
        }
    }
}
