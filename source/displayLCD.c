/**************************
 *
 * @file    displayLCD.c
 *
 * @brief   This file contains definitions of functions to initialize and display in LCD.
 *
 * @date    Nov 26, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "include/displayLCD.h"

/* 0x0000 is black and 0XFFFF is white*/
/* declaration of the pixel values of circle*/
const uint16_t blackBallPixels[]= {

                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0X0000, 0X0000, 0X0000, 0X0000, 0XFFFF,
                            0XFFFF, 0X0000, 0X0000, 0X0000, 0X0000, 0XFFFF,
                            0XFFFF, 0X0000, 0X0000, 0X0000, 0X0000, 0XFFFF,
                            0XFFFF, 0X0000, 0X0000, 0X0000, 0X0000, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,

};

const uint16_t whiteBallPixels[]= {

                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,
                            0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF, 0XFFFF,

};


/**************************
 * @brief       This function initializes the LCD module.
 *
 * @param [in]  NULL
 *
 * @return      NULL
 **************************/
void lcdInit()
{
    PLL_Init(Bus80MHz);
    ST7735_InitR(INITR_REDTAB);
}


/**************************
 * @brief       This function display's ball in LCD.
 *
 * @param [in]  x, y
 *
 * @return      NULL
 **************************/
void displayBall(int16_t x, int16_t y, ballColorSelect_e ballColor)
{
    if(ballColor == BLACK)
        ST7735_DrawBitmap(x, y, blackBallPixels, 6, 6);

    else
        ST7735_DrawBitmap(x, y, whiteBallPixels, 6, 6);
}


/**************************
 * @brief       This function display's paddle in LCD.
 *
 * @param [in]  x, y, len, color
 *
 * @return      NULL
 **************************/
void displayPaddle(int16_t x, int16_t y, int16_t w, int16_t len, uint16_t color)
{
    ST7735_FillRect(x, y, w, len, color);
}
