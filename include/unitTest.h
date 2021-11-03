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

void testNormalMode(uint8_t input);

void testWrongPins(uint8_t input);

void testWrongPort(uint8_t input);

void testExtendedDataInput(uint8_t input);

void assertOutput(uint8_t input, uint8_t outputRecvd, uint8_t expectedOp);

#endif /* UNITTEST_H_ */
