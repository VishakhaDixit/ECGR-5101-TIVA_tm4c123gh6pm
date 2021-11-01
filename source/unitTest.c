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
/* this will start from power up and test all the cases  */
    uint8_t outputRecvd = 0;
    char outputData[9];
    char buffer[100];

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    /* initialize GPIO output pins
      * PB5 - P1.0
      * PB0 - P1.1
      * PB1 - P1.2
      * PE4 - P1.3
      */
    gpioInit(PORT_B, (PIN_5|PIN_0|PIN_1), OUTPUT);
    gpioInit(PORT_E, PIN_4, OUTPUT);

     /* initialize GPIO INPUT pins
      * PA5 - P2.0
      * PA6 -P2.1
      * PA7 - P2.2
      * PA2 - P2.3
      * pa3 - p2.4
      * PA4 - P2.5
      * PB2  -XIN - P2.6
      * PE0 - XOUT - P2.7
      */

    gpioInit(PORT_A, PIN_2|PIN_3|PIN_4|PIN_5|PIN_6|PIN_7, INPUT);
    gpioInit(PORT_B, PIN_2, INPUT);
    gpioInit(PORT_E, PIN_0, INPUT);


    int i = 1;
    for(i=1;i<17;i++)
          {
              switch(i)
              {
             /* case 0:
              {
                  gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x00);
                  gpioSet(PORT_E, PIN_4, 0x00);
                  SysCtlDelay((SysCtlClockGet() * 1) / 3);
                  outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                  outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                  outputRecvd |= gpioGet(PORT_E, PIN_0);
                  break;*/



              case 1:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x00);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                             outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                             outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                             outputRecvd |= gpioGet(PORT_E, PIN_0);
                             decToBin(outputRecvd, outputData, 9);
                             strcpy(buffer, "Input provided: 0001 \n");
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
                             break;
                       }





              case 2:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x02);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                              outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 0010 \n");
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
                                  break;

                         }
              case 3:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x02);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                              outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 0011 \n");
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
                                  break;


                         }
              case 4:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x01);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                             outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 0100 \n");
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
                                  break;


                         }
              case 5:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x01);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                              outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 0101 \n");
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
                                  break;


                         }
              case 6:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x03);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                              outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 0110 \n");
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
                                  break;


                         }
              case 7:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x03);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                          outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                          outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                          outputRecvd |= gpioGet(PORT_E, PIN_0);
                          decToBin(outputRecvd, outputData, 9);
                          strcpy(buffer, "Input provided: 0111 \n");
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
                              break;

                         }
              case 8:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x20);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                              outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                              outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                              outputRecvd |= gpioGet(PORT_E, PIN_0);
                              decToBin(outputRecvd, outputData, 9);
                              strcpy(buffer, "Input provided: 1000 \n");
                              uartTxBytes(UART0_BASE, buffer, 22);
                              strcpy(buffer,"Output received: ");
                              uartTxBytes(UART0_BASE, buffer, 17);
                              uartTxBytes(UART0_BASE, outputData, 8);
                              if( outputRecvd == 1 )
                              {
                                  strcpy(buffer, " => As Expected \n");
                                  uartTxBytes(UART0_BASE, outputData, 17);
                              }
                              else
                              {
                                  strcpy(buffer, " => ERROR !!! \n");
                                  uartTxBytes(UART0_BASE, outputData, 15);

                                  strcpy(buffer, "Expected Output: 0000 0001\n");
                                  uartTxBytes(UART0_BASE, outputData, 27);
                              }
                                  break;


                         }
              case 9:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x20);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                               outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                               outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                               outputRecvd |= gpioGet(PORT_E, PIN_0);
                               decToBin(outputRecvd, outputData, 9);
                               strcpy(buffer, "Input provided: 1001 \n");
                               uartTxBytes(UART0_BASE, buffer, 22);
                               strcpy(buffer,"Output received: ");
                               uartTxBytes(UART0_BASE, buffer, 17);
                               uartTxBytes(UART0_BASE, outputData, 8);
                               if( outputRecvd == 1 )
                               {
                                   strcpy(buffer, " => As Expected \n");
                                   uartTxBytes(UART0_BASE, outputData, 17);
                               }
                               else
                               {
                                   strcpy(buffer, " => ERROR !!! \n");
                                   uartTxBytes(UART0_BASE, outputData, 15);

                                   strcpy(buffer, "Expected Output: 0000 0010\n");
                                   uartTxBytes(UART0_BASE, outputData, 27);
                               }
                                   break;

                         }
              case 10:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x22);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                           outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                           outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                           outputRecvd |= gpioGet(PORT_E, PIN_0);
                           decToBin(outputRecvd, outputData, 9);
                           strcpy(buffer, "Input provided: 1010 \n");
                           uartTxBytes(UART0_BASE, buffer, 22);
                           strcpy(buffer,"Output received: ");
                           uartTxBytes(UART0_BASE, buffer, 17);
                           uartTxBytes(UART0_BASE, outputData, 8);
                           if( outputRecvd == 1 )
                           {
                               strcpy(buffer, " => As Expected \n");
                               uartTxBytes(UART0_BASE, outputData, 17);
                           }
                           else
                           {
                               strcpy(buffer, " => ERROR !!! \n");
                               uartTxBytes(UART0_BASE, outputData, 15);

                               strcpy(buffer, "Expected Output: 0000 0100\n");
                               uartTxBytes(UART0_BASE, outputData, 27);
                           }
                               break;

                         }
              case 11:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x22);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                               outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                               outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                               outputRecvd |= gpioGet(PORT_E, PIN_0);
                               decToBin(outputRecvd, outputData, 9);
                               strcpy(buffer, "Input provided: 1011 \n");
                               uartTxBytes(UART0_BASE, buffer, 22);
                               strcpy(buffer,"Output received: ");
                               uartTxBytes(UART0_BASE, buffer, 17);
                               uartTxBytes(UART0_BASE, outputData, 8);
                               if( outputRecvd == 1 )
                               {
                                   strcpy(buffer, " => As Expected \n");
                                   uartTxBytes(UART0_BASE, outputData, 17);
                               }
                               else
                               {
                                   strcpy(buffer, " => ERROR !!! \n");
                                   uartTxBytes(UART0_BASE, outputData, 15);

                                   strcpy(buffer, "Expected Output: 0000 1000\n");
                                   uartTxBytes(UART0_BASE, outputData, 27);
                               }
                                   break;

                         }
              case 12:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x21);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                               outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                               outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                               outputRecvd |= gpioGet(PORT_E, PIN_0);
                               decToBin(outputRecvd, outputData, 9);
                               strcpy(buffer, "Input provided: 1100 \n");
                               uartTxBytes(UART0_BASE, buffer, 22);
                               strcpy(buffer,"Output received: ");
                               uartTxBytes(UART0_BASE, buffer, 17);
                               uartTxBytes(UART0_BASE, outputData, 8);
                               if( outputRecvd == 1 )
                               {
                                   strcpy(buffer, " => As Expected \n");
                                   uartTxBytes(UART0_BASE, outputData, 17);
                               }
                               else
                               {
                                   strcpy(buffer, " => ERROR !!! \n");
                                   uartTxBytes(UART0_BASE, outputData, 15);

                                   strcpy(buffer, "Expected Output: 0001 0000\n");
                                   uartTxBytes(UART0_BASE, outputData, 27);

                               }
                               break;
                         }
              case 13:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x21);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                               outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                               outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                               outputRecvd |= gpioGet(PORT_E, PIN_0);
                               decToBin(outputRecvd, outputData, 9);
                               strcpy(buffer, "Input provided: 1101 \n");
                               uartTxBytes(UART0_BASE, buffer, 22);
                               strcpy(buffer,"Output received: ");
                               uartTxBytes(UART0_BASE, buffer, 17);
                               uartTxBytes(UART0_BASE, outputData, 8);
                               if( outputRecvd == 1 )
                               {
                                   strcpy(buffer, " => As Expected \n");
                                   uartTxBytes(UART0_BASE, outputData, 17);
                               }
                               else
                               {
                                   strcpy(buffer, " => ERROR !!! \n");
                                   uartTxBytes(UART0_BASE, outputData, 15);

                                   strcpy(buffer, "Expected Output: 0010 0000\n");
                                   uartTxBytes(UART0_BASE, outputData, 27);
                               }
                                   break;

                         }
              case 14:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x23);
                             gpioSet(PORT_E, PIN_4, 0x00);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                           outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                           outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                           outputRecvd |= gpioGet(PORT_E, PIN_0);
                           decToBin(outputRecvd, outputData, 9);
                           strcpy(buffer, "Input provided: 1110 \n");
                           uartTxBytes(UART0_BASE, buffer, 22);
                           strcpy(buffer,"Output received: ");
                           uartTxBytes(UART0_BASE, buffer, 17);
                           uartTxBytes(UART0_BASE, outputData, 8);
                           if( outputRecvd == 1 )
                           {
                               strcpy(buffer, " => As Expected \n");
                               uartTxBytes(UART0_BASE, outputData, 17);
                           }
                           else
                           {
                               strcpy(buffer, " => ERROR !!! \n");
                               uartTxBytes(UART0_BASE, outputData, 15);

                               strcpy(buffer, "Expected Output: 0100 0000\n");
                               uartTxBytes(UART0_BASE, outputData, 27);
                           }
                               break;

                         }
              case 15:
                         {
                             gpioSet(PORT_B, (PIN_5|PIN_0|PIN_1), 0x23);
                             gpioSet(PORT_E, PIN_4, 0x10);
                             SysCtlDelay((SysCtlClockGet() * 1) / 3);
                               outputRecvd |= gpioGet(PORT_A, (PIN_5 | PIN_6 | PIN_7 | PIN_2 | PIN_3 | PIN_4));
                               outputRecvd |= gpioGet(PORT_B, PIN_2) >> 1;
                               outputRecvd |= gpioGet(PORT_E, PIN_0);
                               decToBin(outputRecvd, outputData, 9);
                               strcpy(buffer, "Input provided: 1111 \n");
                               uartTxBytes(UART0_BASE, buffer, 22);
                               strcpy(buffer,"Output received: ");
                               uartTxBytes(UART0_BASE, buffer, 17);
                               uartTxBytes(UART0_BASE, outputData, 8);
                               if( outputRecvd == 1 )
                               {
                                   strcpy(buffer, " => As Expected \n");
                                   uartTxBytes(UART0_BASE, outputData, 17);
                               }
                               else
                               {
                                   strcpy(buffer, " => ERROR !!! \n");
                                   uartTxBytes(UART0_BASE, outputData, 15);

                                   strcpy(buffer, "Expected Output: 1000 0000\n");
                                   uartTxBytes(UART0_BASE, outputData, 27);
                               }
                                   break;

                         }
              default:
              {


                  break;
              }
              }
          }
          i=1;


}



/**************************
 * @brief       This function writes data on P1.4 to P1.7 of MSP.
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






