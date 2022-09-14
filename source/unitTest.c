/**************************
 *
 * @file    unitTest.h
 *
 * @brief   This file contains definition of functions to test the working of MSP430.
 *
 * @date    Oct 29, 2021
 *
 * @author  Vishakha Dixit
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
 * @brief       This function tests output of MSP430 for all inputs from 0-F.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testNormalMode(uint8_t input)
{
    uint8_t expectedOp;

    uint8_t portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /******************************Initialize Test******************************/

    //Set input direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);

    //Set output direction
    gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
    gpioInit(PORT_E, (PIN_4), OUTPUT);

    //Set initial value to zero.
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1 | PIN_4 | PIN_6 | PIN_7), 0x00);
    gpioSet(PORT_E, (PIN_4 | PIN_5), 0x00);

    if(input < 8)
    {
        expectedOp = 0xFF;
    }
    else
    {
        expectedOp = 1 << (input - 8);
    }

    /********************************Execute Test**********************************/

    portBSetInp = (input & 0x06) >> 1;
    portBSetInp |= (input & 0x01) << 5;

    portESetInp = (input & 0x08) << 1;

    //Set the given input
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), portBSetInp);
    gpioSet(PORT_E, PIN_4, portESetInp);

    //Introduced delay to wait for msp430 to process the given input
    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    /**********************************Assert received data**************************/

    outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
    outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
    outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;

    assertOutput(input, outputRecvd, expectedOp);
}


/**************************
 * @brief       This function tests output of MSP430 for all inputs from 0-F set on
 *              wrong pins.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testWrongPins(uint8_t input)
{
    uint8_t expectedOp;

    uint8_t portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /******************************Initialize Test******************************/

    //Set input direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);

    //Set output direction
    gpioInit(PORT_B, (PIN_4 | PIN_6 | PIN_7), OUTPUT);
    gpioInit(PORT_E, (PIN_5), OUTPUT);

    //Set initial value to zero.
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1 | PIN_4 | PIN_6 | PIN_7), 0x00);
    gpioSet(PORT_E, (PIN_4 | PIN_5), 0x00);

    expectedOp = 0xFF;

    /********************************Execute Test**********************************/

    portESetInp = (input & 0x01) << 5;

    portBSetInp = (input & 0x02) << 3;
    portBSetInp |= (input & 0x0C) << 4;

    gpioSet(PORT_B, (PIN_4 | PIN_6 | PIN_7), portBSetInp);
    gpioSet(PORT_E, PIN_5, portESetInp);

    //Introduced delay to wait for msp430 to process the given input
    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    /**********************************Assert received data*************************/

    outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
    outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
    outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;

    input = input << 4;

    assertOutput(input, outputRecvd, expectedOp);
}


/**************************
 * @brief       This function tests output of MSP430 for all inputs from 0-F set on
 *              wrong port.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testWrongPort(uint8_t input)
{
    uint8_t expectedOp;
    char buffer[50];

    uint8_t portASetInp, portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /******************************Initialize Test******************************/

    //Set input direction
    gpioInit(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_E, (PIN_4 | PIN_5), INPUT);

    //Set output direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), OUTPUT);
    gpioInit(PORT_B, PIN_2, OUTPUT);
    gpioInit(PORT_E, PIN_0, OUTPUT);

    //Set initial value  to zero.
    gpioSet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), 0x00);
    gpioSet(PORT_B, PIN_2, 0x00);
    gpioSet(PORT_E, PIN_0, 0x00);

    expectedOp = 0x00;

    /********************************Execute Test**********************************/

    portASetInp = (input & 0x07) << 5;
    portASetInp |= (input & 0x38) >> 1;

    portBSetInp = (input & 0x40) >> 4;
    portESetInp = (input & 0x80) >> 7;

    //Set given input
    gpioSet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), portASetInp);
    gpioSet(PORT_B, PIN_2, portBSetInp);
    gpioSet(PORT_E, PIN_0, portESetInp);

    //Introduced delay to wait for msp430 to process the given input
    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    /**********************************Assert received data**************************/

    outputRecvd += gpioGet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ( ((outputRecvd & 0x03) << 1) | ((outputRecvd & 0x20) >> 5) |
                  ((outputRecvd & 0x10) << 1) | (outputRecvd & 0xC0) );
    outputRecvd += (gpioGet(PORT_E, (PIN_4 | PIN_5)) & 0x18) >> 1;

    if(outputRecvd > 0)
    {
        strcpy(buffer, "Configured Ports Wrong, Sending INPUT on PORT-2 & Receiving OUTPUT from PORT-1\n");
        uartTxBytes(UART0_BASE, buffer, strlen(buffer));
        assertOutput(input, outputRecvd, expectedOp);
        return;
    }
}


/**************************
 * @brief       This function tests output of MSP430 for extended 8-bit input
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void testExtendedDataInput(uint8_t input)
{
    uint8_t expectedOp;

    uint8_t portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /******************************Initialize Test******************************/

    //Set input direction
    gpioInit(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);

    //Set output direction
    gpioInit(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), OUTPUT);
    gpioInit(PORT_E, (PIN_4 | PIN_5), OUTPUT);

    //Set initial value to zero.
    gpioSet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), 0x00);
    gpioSet(PORT_E, (PIN_4 | PIN_5), 0x00);

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

    /********************************Execute Test**********************************/

    portBSetInp = (input & 0x06) >> 1;
    portBSetInp |= (input & 0x01) << 5;
    portBSetInp |= (input & 0x20) >> 1;
    portBSetInp |= (input & 0xC0);

    portESetInp = (input & 0x18) << 1;

    gpioSet(PORT_B, (PIN_0 | PIN_1 | PIN_4 | PIN_5 | PIN_6 | PIN_7), portBSetInp);
    gpioSet(PORT_E, (PIN_4 | PIN_5), portESetInp);

    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    /**********************************Assert received data**************************/

    outputRecvd += gpioGet(PORT_A, (PIN_2 | PIN_3 | PIN_4 | PIN_5 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0xE0) >> 5) | ((outputRecvd & 0x1C) << 1);
    outputRecvd += (gpioGet(PORT_B, PIN_2) & 0x04) << 4;
    outputRecvd += (gpioGet(PORT_E, PIN_0) & 0x01) << 7;

    assertOutput(input, outputRecvd, expectedOp);
}


/**************************
 * @brief       This function verifies received output with expected data & displays result via uart
 *
 * @param [in]  input, outputRecvd, expectedOp
 *
 * @return      void
 **************************/
void assertOutput(uint8_t input, uint8_t outputRecvd, uint8_t expectedOp)
{
    char outputData[9];
    char buffer[100];

    strcpy(buffer, "\nInput provided: 0b");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    decToBin(input, outputData);
    uartTxBytes(UART0_BASE, outputData, 8);

    strcpy(buffer,", Output received: 0b");
    uartTxBytes(UART0_BASE, buffer, strlen(buffer));

    decToBin(outputRecvd, outputData);
    uartTxBytes(UART0_BASE, outputData, 8);

    //Verify received data
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
 * @brief       This function verifies that no output is received on wrong pins of p1.4-p1.7
 *
 * @param [in]  input
 *
 * @return      void
 **************************/
void testReadWrongPins(uint8_t input)
{
    uint8_t expectedOp;

    uint8_t portBSetInp, portESetInp;
    uint8_t outputRecvd = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /******************************Initialize Test******************************/

    //Set input direction
    gpioInit(PORT_B, (PIN_4 | PIN_6 | PIN_7), INPUT);
    gpioInit(PORT_E, PIN_5, INPUT);

    //Set output direction
    gpioInit(PORT_B, (PIN_5 | PIN_0 | PIN_1), OUTPUT);
    gpioInit(PORT_E, (PIN_4), OUTPUT);

    //Set initial value to zero.
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1 | PIN_4 | PIN_6 | PIN_7), 0x00);
    gpioSet(PORT_E, (PIN_4 | PIN_5), 0x00);

    expectedOp = 0x00;

    /********************************Execute Test**********************************/

    portBSetInp = (input & 0x06) >> 1;
    portBSetInp |= (input & 0x01) << 5;

    portESetInp = (input & 0x08) << 1;

    //Set the given input
    gpioSet(PORT_B, (PIN_5 | PIN_0 | PIN_1), portBSetInp);
    gpioSet(PORT_E, PIN_4, portESetInp);

    //Introduced delay to wait for msp430 to process the given input
    SysCtlDelay((SysCtlClockGet() * 1) / 3);

    /**********************************Assert received data**************************/

    outputRecvd += gpioGet(PORT_B, (PIN_4 | PIN_6 | PIN_7));
    outputRecvd = ((outputRecvd & 0x10) >> 3) | ((outputRecvd & 0xC0) >> 4);
    outputRecvd += gpioGet(PORT_E, (PIN_5)) >> 5;

    outputRecvd = outputRecvd << 4;

    assertOutput(input, outputRecvd, expectedOp);
}
