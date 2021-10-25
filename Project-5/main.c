/**************************
 *
 * @file    main.c
 *
 * @brief   This program tends to implement 7 segment display values from 0-F for every change of potentiometer voltage.
 *
 * @date    Oct 21, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/
#include "include/common.h"
#include "include/adc.h"
#include "include/gpio.h"
#include <include/7segDisplay.h>

int main(void)
{
    volatile uint8_t digVal = 0;

    sevenSegPin_Config_t setPinVal;

    setPinVal.a = PIN_6;
    setPinVal.b = PIN_5;
    setPinVal.c = PIN_4;
    setPinVal.d = PIN_3;
    setPinVal.e = PIN_2;
    setPinVal.f = PIN_1;
    setPinVal.g = PIN_0;

    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Initialize 7 segment display
    sevenSegDisplay_Init(PORT_B, &setPinVal);
    //Set initial value as 0 on 7 segment display
    sevenSegDisplay_Set(PORT_B, &setPinVal, digVal);

    //Set config parameters for ADC
    adc_config_args_t adcConfigParam;

    adcConfigParam.adcModule = ADC_0;
    adcConfigParam.pinNum = PIN_3;
    adcConfigParam.port = PORT_E;
    adcConfigParam.seqNum = 3;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    // Initialize ADC
    ADC_Init(&adcConfigParam);

    while(1)
    {
        // Read digital value
        digVal = ADC_Read(&adcConfigParam);

        // Display result in 7 seg display
        sevenSegDisplay_Set(PORT_B, &setPinVal, digVal);
    }
}
