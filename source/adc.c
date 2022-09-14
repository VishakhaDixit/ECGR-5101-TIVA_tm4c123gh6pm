/**************************
 *
 * @file    adc.c
 *
 * @brief   This file contains definition of functions for initializing and reading the digital value of ADC.
 *
 * @date    Oct 22, 2021
 *
 * @author  Vishakha Dixit
 *
 **************************/

#include <include/adc.h>


/**************************
 * @brief       This function initializes the ADC module.
 *
 * @param [in]  *adc_config_params
 *
 * @return      NULL
 **************************/
void ADC_Init(adc_config_args_t *adc_config_params)
{
    uint32_t adcBaseAdd;

    if(adc_config_params->adcModule == ADC_0)
    {
        adcBaseAdd = ADC0_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    }
    else
    {
        adcBaseAdd = ADC1_BASE;
        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    }

    GPIOPinTypeADC(adc_config_params->port, adc_config_params->pinNum);

    ADCSequenceDisable(adcBaseAdd, adc_config_params->seqNum);

    ADCReferenceSet(adcBaseAdd, ADC_REF_INT);

    ADCSequenceConfigure(adcBaseAdd, adc_config_params->seqNum, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(adcBaseAdd, adc_config_params->seqNum, 0, adc_config_params->adcChannel |
                             ADC_CTL_IE | ADC_CTL_END);

    ADCSequenceEnable(adcBaseAdd, adc_config_params->seqNum);

    ADCIntEnable(adcBaseAdd, adc_config_params->seqNum);
}


/**************************
 * @brief       This function reads the digital value of ADC.
 *
 * @param [in]  *adc_config_params
 *
 * @return      uint32_t ADC data
 **************************/
uint32_t ADC_Read(adc_config_args_t *adc_config_params)
{
    uint32_t pui32ADC0Value[1];
    uint32_t result = 0;
    uint32_t adcBaseAdd;

    if(adc_config_params->adcModule == ADC_0)
    {
        adcBaseAdd = ADC0_BASE;
    }
    else
    {
        adcBaseAdd = ADC1_BASE;
    }

    ADCIntClear(adcBaseAdd, adc_config_params->seqNum);
    ADCProcessorTrigger(adcBaseAdd, adc_config_params->seqNum);

    while(!ADCIntStatus(adcBaseAdd, adc_config_params->seqNum, false))
    {
    }

    // Read ADC Value.
    ADCSequenceDataGet(adcBaseAdd, adc_config_params->seqNum, pui32ADC0Value);
    result = pui32ADC0Value[0] & 0x00000FFF;

    return result;
}

uint8_t sampleADCData(uint32_t digital_val)
{
    uint8_t result = 0;

    if( (digital_val > 0) && (digital_val <= 511) )
        result = 0;
    else if( (digital_val >= 512) && (digital_val <= 1023) )
        result = 1;
    else if( (digital_val >= 1024) && (digital_val <= 1535) )
        result = 2;
    else if( (digital_val >= 1536) && (digital_val <= 2047) )
        result = 3;
    else if( (digital_val >= 2048) && (digital_val <= 2559) )
        result = 4;
    else if( (digital_val >= 2560) && (digital_val <= 3071) )
        result = 5;
    else if( (digital_val >= 3072) && (digital_val <= 3583) )
        result = 6;
    else if( (digital_val >= 3584) && (digital_val <= 4095) )
        result = 7;

    return result;
}


