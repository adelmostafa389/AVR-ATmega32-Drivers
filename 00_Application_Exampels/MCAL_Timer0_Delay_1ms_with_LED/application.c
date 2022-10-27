/*
 * application.c
 *
 * Created: 8/29/2022 12:55:40 PM
 *  Author: ADEL
 */ 

#include "application.h"

uint16_t counter1 = 0;

// Timer0 configuration to generate 1msec delay
st_timer0_config_t timer0_1secDelay = {
	.mode = T0_CTC_MODE,
	.compareModeNonPWM = OC0_nonPWM_DISCONNECTED,
	.clockSource = T0_CLK_DIV_BY_8,
	.preloadValue = 124
};

St_led_t led1 = {
	.port = PORTA_INDEX,
	.pin = PIN1,
	.led_status = LED_OFF
};



void App_init(){
	init_ADC(&adc_ch0);
	LED_init(&led1);
	timer0_init(&timer0_1secDelay);
}

void App_start(){

}


ISR(TIMER0_OVERFLOW){
	counter1++;
	if (counter1 > 1000)
	{ // This code will be executed every 1 second
		counter1 = 0;
		toggle_led(&led1);
	}
	else{ /* Nothing */ }
}
