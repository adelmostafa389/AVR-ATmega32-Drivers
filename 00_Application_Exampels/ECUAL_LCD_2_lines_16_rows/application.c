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

St_chr_lcd_8bit_t lcd_8bit = {
	.lcd_en.port = PORTD_INDEX,
	.lcd_en.pin = PIN0,
	.lcd_rs.port = PORTD_INDEX,
	.lcd_rs.pin = PIN1,
	.lcd_data_pins[0].port = PORTC_INDEX,
	.lcd_data_pins[0].pin = PIN0,
	.lcd_data_pins[1].port = PORTC_INDEX,
	.lcd_data_pins[1].pin = PIN1,
	.lcd_data_pins[2].port = PORTC_INDEX,
	.lcd_data_pins[2].pin = PIN2,
	.lcd_data_pins[3].port = PORTC_INDEX,
	.lcd_data_pins[3].pin = PIN3,
	.lcd_data_pins[4].port = PORTC_INDEX,
	.lcd_data_pins[4].pin = PIN4,
	.lcd_data_pins[5].port = PORTC_INDEX,
	.lcd_data_pins[5].pin = PIN5,
	.lcd_data_pins[6].port = PORTC_INDEX,
	.lcd_data_pins[6].pin = PIN6,
	.lcd_data_pins[7].port = PORTC_INDEX,
	.lcd_data_pins[7].pin = PIN7,
};

St_chr_lcd_4bit_t lcd_4bit = {
	.lcd_en.port = PORTD_INDEX,
	.lcd_en.pin = PIN0,
	.lcd_rs.port = PORTD_INDEX,
	.lcd_rs.pin = PIN1,
	.lcd_data_pins[0].port = PORTC_INDEX,
	.lcd_data_pins[0].pin = PIN4,
	.lcd_data_pins[1].port = PORTC_INDEX,
	.lcd_data_pins[1].pin = PIN5,
	.lcd_data_pins[2].port = PORTC_INDEX,
	.lcd_data_pins[2].pin = PIN6,
	.lcd_data_pins[3].port = PORTC_INDEX,
	.lcd_data_pins[3].pin = PIN7,
};

void App_init(){
	//HLcd_8bit_init(&lcd_8bit);
	HLcd_4bit_init(&lcd_4bit);
	HLcd_4bit_send_char_data(&lcd_4bit, 'A');
	HLcd_4bit_send_string(&lcd_4bit, "ADEL MOSTAFA");
	HLcd_4bit_send_string_pos(&lcd_4bit, ROW2, COLUMN9, "ELKING");
}

void App_start(){
}


