/**************************
 *
 * @file    gpio.c
 *
 * @brief   This file contains definition of functions for initializing msp430 gpio.
 *
 * @date    Oct 22, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#include "include/gpio.h"


/**************************
 * @brief       This function initializes the given port based on the direction provided.
 *
 * @param [in]  portBaseAdd, portVal, direction
 *
 * @return      NULL
 **************************/
void gpioInit(uint32_t portBaseAdd, uint8_t pins,  dir_e direction)
{
    if(direction == INPUT)
    {
        GPIOPinTypeGPIOInput(portBaseAdd, pins);
    }
    else
    {
        GPIOPinTypeGPIOOutput(portBaseAdd, pins);
    }
}


/**************************
 * @brief       This function reads the values present of the specified pin(s).
 *
 * @param [in]  portBaseAdd, pinNum
 *
 * @return      int32_t  Status of the pin
 **************************/
int32_t gpioGet(uint32_t portBaseAdd, uint8_t pin)
{
    int32_t val;

    val = GPIOPinRead(portBaseAdd, pin);

    return val;
}


/**************************
 * @brief       This function sets the gpio pins of given port
 *
 * @param [in]  portBaseAdd, pinNum, val
 *
 * @return      NULL
 **************************/
void gpioSet(uint32_t portBaseAdd, uint8_t pins, uint8_t val)
{
    GPIOPinWrite(portBaseAdd, pins, val);
}
