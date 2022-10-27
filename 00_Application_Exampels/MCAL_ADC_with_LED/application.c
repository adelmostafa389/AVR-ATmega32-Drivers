/*
 * application.c
 *
 * Created: 8/29/2022 12:55:40 PM
 *  Author: ADEL
 */ 

#include "application.h"


void adc_ISR(void);

float adc_result = 0;

st_adc_config_t adc_ch0 = {
	.adc_reference = ADC_AVCC,
	.channel = ADC_CHANNEL_0,
	.prescaler = ADC_CLK_DIV_BY_2,
	.interruptHandler = adc_ISR
};

St_led_t led1 = {
	.port = PORTA_INDEX,
	.pin = PIN1,
	.led_status = LED_OFF
};

void App_init(){
	init_ADC(&adc_ch0);
	LED_init(&led1);
}

void App_start(){
	start_ADC(&adc_ch0, &adc_result);
}


void adc_ISR(void){
	if(adc_result > 3.0){
		turn_led_on(&led1);
	}
	else{
		turn_led_off(&led1);
	}
}