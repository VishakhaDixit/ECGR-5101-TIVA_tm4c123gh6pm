/**************************
 *
 * @file    adc.h
 *
 * @brief   This file contains functions to initialize ADC and read its digital value.
 *
 * @date    Oct 22, 2021
 *
 * @author  Vishakha Dixit, Anuradha
 *
 **************************/

#ifndef ADC_H_
#define ADC_H_

#include "include/common.h"

typedef enum adcSelect
{
    ADC_0  = SYSCTL_PERIPH_ADC0,
    ADC_1  = SYSCTL_PERIPH_ADC1
} adcModuleSelect_e;

typedef enum adcChSelect
{
    ADC_CH0  = ADC_CTL_CH0,
    ADC_CH1  = ADC_CTL_CH1,
    ADC_CH2  = ADC_CTL_CH2,
    ADC_CH3  = ADC_CTL_CH3,
    ADC_CH4  = ADC_CTL_CH4,
    ADC_CH5  = ADC_CTL_CH5,
    ADC_CH6  = ADC_CTL_CH6,
    ADC_CH7  = ADC_CTL_CH7,
    ADC_CH8  = ADC_CTL_CH8,
    ADC_CH9  = ADC_CTL_CH9,
    ADC_CH10  = ADC_CTL_CH10,
    ADC_CH11  = ADC_CTL_CH11,
} adcChSelect_e;

typedef struct adcConfigArgs
{
    port_e port;
    adcModuleSelect_e adcModule;
    pin_num_e pinNum;
    uint32_t seqNum;
    adcChSelect_e adcChannel;
} adc_config_args_t;

void ADC_Init(adc_config_args_t *adc_config_params);

uint32_t ADC_Read(adc_config_args_t *adc_config_params);

uint8_t sampleADCData(uint32_t digital_val);

#endif /* ADC_H_ */
