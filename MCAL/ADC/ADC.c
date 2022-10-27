/*
 * ADC.c
 *
 * Created: 9/7/2022 2:21:46 PM
 *  Author: ADEL
 */ 

#include "ADC.h"

uint16_t adc_digital_result = 0;
float* adc_analog_result = 0;
PtrTo_func_t adc_interrupt_handler = NULL;
static void ADC_set_channel_pin_direction(en_adc_channel_t channel);

En_Std_ReturnType_t init_ADC(const st_adc_config_t* adc_cfg){
	En_Std_ReturnType_t ret = OK;
	if(NULL == adc_cfg){
		ret = NOT_OK;
	}
	else{
		// set the ADC mode
		
		// set ADC pin to be input
		ADC_set_channel_pin_direction(adc_cfg->channel);
		// Choose ADC Channel
		ADMUXbits.MUX = adc_cfg->channel;
		// select the reference voltage
		ADMUXbits.REFS = adc_cfg->adc_reference;
		// set the result adjustment
		ADC_ADJUST_RESUTLT();
		// Enable the ADC
		ADC_ENABLE();
		// Choose the frequency prescaler
		ADCSRAbits.ADSC = adc_cfg->prescaler;
		// enable the ADC Interrupt if it is enabled
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		ADC_ENABLE_INTERRUPT();
		ENABLE_GLOBAL_INTERRUPT();
		adc_interrupt_handler = adc_cfg->interruptHandler;
#endif
	}
	return ret;
}

En_Std_ReturnType_t start_ADC(const st_adc_config_t* adc_cfg, float* result){
	En_Std_ReturnType_t ret = OK;
	if((NULL == adc_cfg) || (NULL == result)){
		ret = NOT_OK;
	}
	else{
		// Choose channel to read
		ADMUXbits.MUX = adc_cfg->channel;
		// Start Conversion
		ADC_START();
		// Get the ADC conversion result in case of the ADC Interrupt is disabled
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_DISABLE
		// Wait for conversion to complete
		while(ADCSRAbits.ADIF == 0);
		// Read the digital value and convert it to analog
	#if ADC_RESULT_ADJUSTMENT == ADC_RESULT_RIGHT_ADJUST
		adc_digital_result = (uint16_t)(ADC_L + (uint16_t)(ADC_H << 8));
	#elif ADC_RESULT_ADJUSTMENT == ADC_RESULT_LEFT_ADJUST
		adc_digital_result = (uint16_t)((ADC_L >> 6) + (uint16_t)(ADC_H));
	#endif
		*result = adc_digital_result * ADC_STEP;
#elif ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		adc_analog_result = result;
#endif
	}
	return ret;
}


static void ADC_set_channel_pin_direction(en_adc_channel_t channel){
	switch(channel){
		case ADC_CHANNEL_0:
		DIO_set_direction(PORTA_INDEX, PIN0, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_1:
		DIO_set_direction(PORTA_INDEX, PIN1, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_2:
		DIO_set_direction(PORTA_INDEX, PIN2, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_3:
		DIO_set_direction(PORTA_INDEX, PIN3, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_4:
		DIO_set_direction(PORTA_INDEX, PIN4, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_5:
		DIO_set_direction(PORTA_INDEX, PIN5, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_6:
		DIO_set_direction(PORTA_INDEX, PIN6, GPIO_DIRECTION_INPUT);
		break;
		case ADC_CHANNEL_7:
		DIO_set_direction(PORTA_INDEX, PIN7, GPIO_DIRECTION_INPUT);
		break;
		default:
		break;
	}
}

ISR(ADC_INT_REQ_VECTOR){
#if ADC_RESULT_ADJUSTMENT == ADC_RESULT_RIGHT_ADJUST
	adc_digital_result = (uint16_t)(ADC_L + (uint16_t)(ADC_H << 8));
#elif ADC_RESULT_ADJUSTMENT == ADC_RESULT_LEFT_ADJUST
	adc_digital_result = (uint16_t)((ADC_L >> 6) + (uint16_t)(ADC_H));
#endif
	*adc_analog_result = adc_digital_result * ADC_STEP;
	adc_interrupt_handler();	
}