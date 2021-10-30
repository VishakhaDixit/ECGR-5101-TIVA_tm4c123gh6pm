/*
 * common.h
 *
 *  Created on: Oct 22, 2021
 *      Author: visha
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "inc/tm4c123gh6pm.h"

typedef enum port
{
    PORT_A = GPIO_PORTA_BASE,
    PORT_B = GPIO_PORTB_BASE,
    PORT_C = GPIO_PORTC_BASE,
    PORT_D = GPIO_PORTD_BASE,
    PORT_E = GPIO_PORTE_BASE,
    PORT_F = GPIO_PORTF_BASE
} port_e;

typedef enum pinNum
{
    PIN_0 = GPIO_PIN_0,
    PIN_1 = GPIO_PIN_1,
    PIN_2 = GPIO_PIN_2,
    PIN_3 = GPIO_PIN_3,
    PIN_4 = GPIO_PIN_4,
    PIN_5 = GPIO_PIN_5,
    PIN_6 = GPIO_PIN_6,
    PIN_7 = GPIO_PIN_7
} pin_num_e;

#endif /* COMMON_H_ */
