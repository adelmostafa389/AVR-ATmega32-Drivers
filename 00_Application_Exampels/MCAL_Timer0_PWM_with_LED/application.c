/*
 * application.c
 *
 * Created: 8/29/2022 12:55:40 PM
 *  Author: ADEL
 */ 

#include "application.h"


void adc_ISR(void);

uint16_t pwmDutyCycle = 0;
uint16_t counter1 = 0;

// Timer0 configuration to generate PWM
st_timer0_config_t timer0_pwm = {
	.mode = T0_FAST_PWM_MODE,
	.compareModeFastPWM = OC0_FAST_PWM_CLEAR,
	.clockSource = T0_CLK_DIV_BY_8,
	.preload_pwmDC = 0
};

St_led_t led1 = {
	.port = PORTA_INDEX,
	.pin = PIN1,
	.led_status = LED_OFF
};


void App_init(){
	LED_init(&led1);
	timer0_init(&timer0_pwm);
}

void App_start(){
	timer0_pwm_set_DC(&timer0_pwm, pwmDutyCycle);
}

ISR(TIMER0_OVERFLOW){
	if (counter1 > 100){
		pwmDutyCycle++;
		counter1 = 0;
	}
	else{ 
		counter1++; 
	}
	if (pwmDutyCycle > 100)
	{
		pwmDutyCycle = 0;
	}
	else{ /* Nothing */ }
}