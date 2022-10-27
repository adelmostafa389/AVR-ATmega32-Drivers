/*
 * application.c
 *
 * Created: 8/29/2022 12:55:40 PM
 *  Author: ADEL
 */ 

#include "application.h"


void adc_ISR(void);

uint8_t arr[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
uint8_t keypad_input = 0;
uint8_t kepad_currentInput = 0;

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
	.row = ROW1,
	.column = COLUMN1
};

St_keypad_type_t keypad_cfg = {
	.keypadRowsArr[0].port = PORTB_INDEX,
	.keypadRowsArr[0].pin = PIN0,
	.keypadRowsArr[1].port = PORTB_INDEX,
	.keypadRowsArr[1].pin = PIN1,
	.keypadRowsArr[2].port = PORTB_INDEX,
	.keypadRowsArr[2].pin = PIN2,
	.keypadRowsArr[3].port = PORTB_INDEX,
	.keypadRowsArr[3].pin = PIN3,
	.keypadColumnsArr[0].port = PORTB_INDEX,
	.keypadColumnsArr[0].pin = PIN4,
	.keypadColumnsArr[1].port = PORTB_INDEX,
	.keypadColumnsArr[1].pin = PIN5,
	.keypadColumnsArr[2].port = PORTB_INDEX,
	.keypadColumnsArr[2].pin = PIN6,
	.keypadColumnsArr[3].port = PORTB_INDEX,
	.keypadColumnsArr[3].pin = PIN7,
};


void App_init(){
	HLcd_4bit_init(&lcd_4bit);
	Keypad_initialize(&keypad_cfg);
	
	//HLcd_4bit_send_char_data(&lcd_4bit, 'A');
	
	//HLcd_4bit_send_string(&lcd_4bit, "ADEL MOSTAFA");
	//HLcd_4bit_send_string_pos(&lcd_4bit, ROW2, COLUMN9, "ELKING");
}

void App_start(){
	Keypad_get_value(&keypad_cfg, &keypad_input);
	if(keypad_input != kepad_currentInput){
		kepad_currentInput = keypad_input;
		HLcd_4bit_send_char_data(&lcd_4bit, keypad_input);
	}
}


