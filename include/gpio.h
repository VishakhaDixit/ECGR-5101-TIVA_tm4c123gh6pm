/**************************
 *
 * @file    gpio.h
 *
 * @brief   This file contains functions for initializing gpio.
 *
 * @date    Oct 22, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "include/common.h"

typedef enum direction
{
    INPUT  = 0,
    OUTPUT = 1
} dir_e;


void gpioInit(uint32_t portBaseAdd, uint8_t pins,  dir_e direction);

uint8_t gpioGet(uint32_t portBaseAdd, uint8_t pin);

void gpioSet(uint32_t portBaseAdd, uint8_t pins, uint8_t val);

void enableGpioInterrupt(uint32_t portBaseAdd, uint8_t pins, uint32_t intFlags);

void GPIOIntHandler(void);

#endif /* GPIO_H_ */
