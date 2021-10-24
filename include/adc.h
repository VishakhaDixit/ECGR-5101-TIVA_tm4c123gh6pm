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

typedef struct adcConfigArgs
{
    port_e port;
    adcModuleSelect_e adcModule;
    pin_num_e pinNum;
    uint32_t seqNum;
} adc_config_args_t;

void ADC_Init(adc_config_args_t *adc_config_params);

uint16_t ADC_Read(adc_config_args_t *adc_config_params);

uint16_t sampleADCData(uint32_t digital_val);

#endif /* ADC_H_ */
