/**************************
 *
 * @file    main.c
 *
 * @brief   This project intends to implement a simple pong game using joystick and LCD.
 *
 * @date    Nov 26, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include "include/displayLCD.h"
#include "include/adc.h"
#include "include/gpio.h"

#define X_MAX 124
#define X_MIN 8
#define Y_MAX 124
#define Y_MIN 4

#define INITX_MAX 124
#define INITX_MIN 80

#define DELX -2
#define DELX_MAX 3
#define DELY_MAX  2
#define DELY_MIN -2

#define MAX_REFLECTION_ANGLE 75
#define BALL_ACC 2

#define PADDLE_MIN 4
#define PADDLE_MAX 115

int8_t getAccVal(uint8_t sampleVal);

void main(void)
{
    bool isInit = true;

    uint32_t adcRanVal = 0;
    uint32_t adcResult = 0;
    uint8_t sampleAdcVal = 0;

    int16_t ballX = 0;
    int16_t ballY = 0;
    int16_t ballDelX = 0;
    int16_t ballDelY = 0;
    uint16_t ballAngle;
    float ballVelocityX;
    float ballVelocityY;

    int16_t paddleX, paddleY;
    int16_t paddleWidth = 2;
    int16_t paddleLen = 15;
    int8_t paddleAcc;

    float yIntersectPt;
    float normalizedyIntersectPt;

    //Set system clock
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
               SYSCTL_XTAL_16MHZ);

    //Set ADC to fetch random value from unused channel
    adc_config_args_t adcRanValParam;

    adcRanValParam.adcModule = ADC_1;
    adcRanValParam.pinNum = PIN_3;
    adcRanValParam.port = PORT_E;
    adcRanValParam.seqNum = 3;
    adcRanValParam.adcChannel = ADC_CH0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Initialize ADC
    ADC_Init(&adcRanValParam);

    //Initialize Port D pin 3 as input to fetch adc data from joystick
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    gpioInit(PORT_D, PIN_3, INPUT);

    //Set config parameters for ADC
    adc_config_args_t adcConfigParam;

    adcConfigParam.adcModule = ADC_0;
    adcConfigParam.pinNum = PIN_3;
    adcConfigParam.port = PORT_D;
    adcConfigParam.seqNum = 3;
    adcConfigParam.adcChannel = ADC_CH4;

    // Initialize ADC
    ADC_Init(&adcConfigParam);

    //Initialize LCD
    lcdInit();

    ST7735_FillScreen(0x0000);  // black screen
    SysCtlDelay(500000);
    ST7735_FillScreen(0XFFFF);  //white screen

    while(1)
    {
        if(isInit == true)
        {
            //fetch adc random value and use it as seed to generate random ball coordinates for a set range
            adcRanVal = ADC_Read(&adcRanValParam);
            srand(adcRanVal);
            ballX = (rand() % (INITX_MAX - INITX_MIN + 1)) + INITX_MIN;
            ballY = (rand() % (Y_MAX - Y_MIN + 1)) + Y_MIN;

            if(ballY < Y_MIN)
                ballY = Y_MIN;

            //fetch adc random value to generate random differential coordinates to randomize ball's movement
            adcRanVal = ADC_Read(&adcRanValParam);
            srand(adcRanVal);
            ballDelX = DELX;
            ballDelY = (rand() % (DELY_MAX - DELY_MIN + 1)) + DELY_MIN;

            if(ballDelY == 0)
                ballDelY = 1;

            //Set initial paddle coordinates
            paddleX = 4;
            paddleY = 54;

            //Display initial paddle & ball position
            displayBall(ballX, ballY, BLACK);
            displayPaddle(paddleX, paddleY, paddleWidth, paddleLen, ST7735_BLACK);

            ST7735_DrawCharS(59, 4, '3', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            SysCtlDelay(1000000);
            ST7735_DrawCharS(59, 4, '3', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(59, 4, '2', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            SysCtlDelay(1000000);
            ST7735_DrawCharS(59, 4, '2', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(59, 4, '1', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            SysCtlDelay(1000000);
            ST7735_DrawCharS(59, 4, '1', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
            SysCtlDelay(500000);
            ST7735_DrawCharS(59, 4, 'G', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(70, 4, 'O', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(80, 4, '!', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
            SysCtlDelay(500000);
            ST7735_DrawCharS(59, 4, 'G', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(70, 4, 'O', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
            ST7735_DrawCharS(80, 4, '!', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);

            isInit = false;
        }

        displayBall(ballX, ballY, WHITE);
        displayPaddle(paddleX, paddleY, paddleWidth, paddleLen, ST7735_WHITE);

        ballX += ballDelX;
        ballY += ballDelY;

        //Reflect the ball when it touches right side wall
        if(ballX >= X_MAX)
        {
            if(ballDelY == 0)
                ballDelY = 1;
            ballDelX *= -1;
            ballX = X_MAX;
        }

        //Reflect ball when it touches the paddle
        if( (ballX >= paddleX) && (ballX <= (paddleX + paddleWidth)) )
        {
            if( (ballY >= paddleY) && (ballY <= (paddleY + paddleLen + 3)) )
            {
                //Calculating ball's direction based on how far from center of the paddle it collided.
                yIntersectPt = ( (paddleY + 7) + (paddleLen/2.0) ) - ballY;
                normalizedyIntersectPt = ( yIntersectPt / (paddleLen/2) );
                ballAngle = normalizedyIntersectPt * MAX_REFLECTION_ANGLE;

                ballVelocityX = ballDelX * cos(ballAngle);
                ballVelocityY = (-1) * ballDelY * sin(ballAngle);

                if((ballVelocityX > 0) && (ballVelocityX < 1))
                    ballDelX = 1;
                else if(ballVelocityX == 0)
                    ballDelX = 1;
                else
                {
                    ballDelX = (int16_t) ballVelocityX + BALL_ACC;
                    if(ballDelX > DELX_MAX)
                        ballDelX = DELX_MAX;
                }

                if((ballVelocityY < 0) && (ballVelocityY > -1))
                    ballDelY = -1;
                else if((ballVelocityY > 0) && (ballVelocityY < 1))
                    ballDelY = 1;
                else if(ballVelocityY == 0)
                    ballDelY = 0;
                else
                {
                    ballDelY = (int16_t) ballVelocityY + BALL_ACC;
                    if(ballDelY > 3)
                        ballDelY = 3;
                }
            }
        }

        //Reflect ball when it touch top or bottom wall
        if((ballY <= Y_MIN) || (ballY >= Y_MAX))
        {
            ballDelY *= -1;

            if(ballY <= Y_MIN)
                ballY = Y_MIN;

            if(ballY >= Y_MAX)
                ballY = Y_MAX;
        }

        //If ball doesn't touch the paddle and goes beyond the left wall then display END
        if(ballX < paddleX)
        {
            if( !( (ballY >= paddleY) && (ballY <= (paddleY + paddleLen + 1)) ) )
            {
                ballX = 0;

                displayBall(ballX, ballY, BLACK);
                displayPaddle(paddleX, paddleY, paddleWidth, paddleLen, ST7735_BLACK);

                SysCtlDelay(250000);

                displayBall(ballX, ballY, WHITE);

                SysCtlDelay(250000);

                ST7735_DrawCharS(59, 4, 'E', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
                ST7735_DrawCharS(70, 4, 'N', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
                ST7735_DrawCharS(84, 4, 'D', ST7735_Color565 (0, 0, 139), ST7735_Color565 (255, 255, 255), 2);
                SysCtlDelay(1000000);
                ST7735_DrawCharS(59, 4, 'E', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
                ST7735_DrawCharS(70, 4, 'N', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
                ST7735_DrawCharS(84, 4, 'D', ST7735_Color565 (255, 255, 255), ST7735_Color565 (255, 255, 255), 2);
                SysCtlDelay(500000);

                displayPaddle(paddleX, paddleY, paddleWidth, paddleLen, ST7735_WHITE);

                isInit = true;

                continue;
            }
        }

        //Fetch ADC data to read joystick value
        adcResult = ADC_Read(&adcConfigParam);
        sampleAdcVal = sampleADCData(adcResult);

        //Calculate acceleration of paddle based on ADC value
        paddleAcc = getAccVal(sampleAdcVal);

        //Accelerate the paddle when it's within the top and bottom walls
        if(paddleY > PADDLE_MIN && paddleY < PADDLE_MAX)
        {
            paddleY += paddleAcc;

            if(paddleY < PADDLE_MIN)
                paddleY = PADDLE_MIN;

            if(paddleY > PADDLE_MAX)
                paddleY = PADDLE_MAX;
        }
        //Paddle shouldn't accelerate when it touches the top wall.
        else if(paddleY == PADDLE_MIN && paddleAcc > 0)
        {
            paddleY += paddleAcc;
        }
        //Paddle shouldn't accelerate when it touches the bottom wall.
        else if(paddleY == PADDLE_MAX && paddleAcc < 0)
        {
            paddleY += paddleAcc;
        }

        displayBall(ballX, ballY, BLACK);
        displayPaddle(paddleX, paddleY, paddleWidth, paddleLen, ST7735_BLACK);
        SysCtlDelay(25000);
    }
}

int8_t getAccVal(uint8_t sampleVal)
{
    switch(sampleVal)
    {
    case 0:
        return(8);
    case 1:
        return(4);
    case 2:
        return(1);
    case 3:
        return(0);
    case 4:
        return(0);
    case 5:
        return(-1);
    case 6:
        return(-4);
    case 7:
        return(-8);
    }

    return 0;
}
