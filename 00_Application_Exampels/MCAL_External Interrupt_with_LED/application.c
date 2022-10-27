/*
 * application.c
 *
 * Created: 8/29/2022 12:55:40 PM
 *  Author: ADEL
 */ 

#include "application.h"

uint16_t counter1 = 0;

St_led_t led1 = {
	.port = PORTA_INDEX,
	.pin = PIN1,
	.led_status = LED_OFF
};

St_interrupt_INTx_t externalInterrupt0 = {
	.source = INT0_INTERRUPT_EXTERNAL,
	.edge = INTI_RISING_EDGE
};


void App_init(){
	LED_init(&led1);
	init_external_INTx(&externalInterrupt0);
}

void App_start(){
	
}


ISR(EXT_INT_0){
	toggle_led(&led1);
}