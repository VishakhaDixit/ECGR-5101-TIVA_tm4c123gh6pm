/**************************
 *
 * @file    gpio.h
 *
 * @brief   This file contains functions for initializing 7 Segment Display and sets value on it.
 *
 * @date    Sept 08, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef INCLUDE_7SEGDISPLAY_H_
#define INCLUDE_7SEGDISPLAY_H_

#include <include/common.h>
#include <include/gpio.h>

typedef struct sevenSegPin
{
    uint8_t g;
    uint8_t f;
    uint8_t e;
    uint8_t d;
    uint8_t c;
    uint8_t b;
    uint8_t a;
}sevenSegPin_Config_t;

void sevenSegDisplay_Init(uint32_t portBaseAdd, sevenSegPin_Config_t *setPin);

void sevenSegDisplay_Set(port_e portNum, sevenSegPin_Config_t *setPin, uint8_t val);

#endif /* INCLUDE_7SEGDISPLAY_H_ */
