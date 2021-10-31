/**************************
 *
 * @file    unitTest.h
 *
 * @brief   This file contains functions to test the working of MSP430.
 *
 * @date    Oct 29, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#ifndef UNITTEST_H_
#define UNITTEST_H_

#include <include/common.h>
#include <include/uart.h>
#include <include/gpio.h>

void testInitialPowerUpMode();

void testNormalMode();

void testWrongPins();

void testWrongPort();

void testExtendedDataInput();


#endif /* UNITTEST_H_ */
