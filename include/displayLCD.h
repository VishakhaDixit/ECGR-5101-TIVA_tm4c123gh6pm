/**************************
 *
 * @file    displayLCD.h
 *
 * @brief   This file contains functions to initialize and display in LCD.
 *
 * @date    Nov 26, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#ifndef DISPLAYLCD_H_
#define DISPLAYLCD_H_

#include "include/PLL.h"
#include "include/ST7735.h"
#include "include/common.h"

typedef enum ballColorSelect
{
    WHITE,
    BLACK
} ballColorSelect_e;

void lcdInit();

void displayBall(int16_t x, int16_t y, ballColorSelect_e ballColor);

void displayPaddle(int16_t x, int16_t y, int16_t w, int16_t len, uint16_t color);

#endif /* DISPLAYLCD_H_ */
