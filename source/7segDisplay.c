/**************************
 *
 * @file    gpio.c
 *
 * @brief   This file contains definition of functions for initializing 7 Segment Display and sets value on it.
 *
 * @date    Sept 08, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include <include/7segDisplay.h>

/**************************
 * @brief       This function initializes the 7 segment display pins.
 *
 * @param [in]  portBaseAdd, *setPin
 *
 * @return      NULL
 **************************/
void sevenSegDisplay_Init(uint32_t portBaseAdd, sevenSegPin_Config_t *setPin)
{
    gpioInit(portBaseAdd, (setPin->a | setPin->b | setPin->c | setPin->d | setPin->e | setPin->f | setPin->g), OUTPUT);
}


/**************************
 * @brief       This function displays the given value in 7 segment display.
 *
 * @param [in]  portBaseAdd, *setPin, val
 *
 * @return      NULL
 **************************/
void sevenSegDisplay_Set(uint32_t portBaseAdd, sevenSegPin_Config_t *setPin, uint8_t val)
{
    uint8_t portVal;

    switch(val)
    {
    case 0:
        portVal = ~(0x7E);    // display 0 - 0111 1110
        break;

    case 1:
        portVal = ~(0x30);    // display 1 - 0011 0000
        break;

    case 2:
        portVal = ~(0x6D);     // display 2 - 0110 1101
        break;

    case 3:
        portVal = ~(0x79);     // display 3 - 0111 1001
        break;

    case 4:
        portVal = ~(0x33);     // display 4 - 0011 0011
        break;

    case 5:
        portVal = ~(0x5B);     // display 5 - 0101 1011
        break;

    case 6:
        portVal = ~(0x5F);     // display 6 - 0101 1111
        break;

    case 7:
        portVal = ~(0x70);     // display 7 - 0111 0000
        break;

    case 8:
        portVal = (uint8_t)~(0xFF);    // display 8 - 1111 1111
        break;

    case 9:
        portVal = ~(0x73);    // display 9 - 0111 0011
        break;

    case 10:
        portVal = ~(0x77);    // display A - 0111 0111
        break;

    case 11:
        portVal = ~(0x1F);    // display b - 0001 1111
        break;

    case 12:
        portVal = ~(0x4E);    // display C - 0100 1110
        break;

    case 13:
        portVal = ~(0x3D);    // display d - 0011 1101
        break;

    case 14:
        portVal = ~(0x4F);    // display E - 0100 1111
        break;

    case 15:
        portVal = ~(0x47);    // display F - 0100 0111
        break;

    default:
        portVal = ~(0x01);    // display - 0000 0001
        break;
    }

    gpioSet(portBaseAdd, setPin->a | setPin->b | setPin->c | setPin->d | setPin->e | setPin->f | setPin->g, portVal);
}


