/*
 * Chr_LCD.h
 *
 * Created: 9/8/2022 3:27:02 PM
 *  Author: ADEL
 */ 


#ifndef CHR_LCD_H_
#define CHR_LCD_H_

// Define the Clock Frequency 8 MHz
#define F_CPU 8000000UL

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/DIO/dio.h"
#include <string.h>
#include <util/delay.h>


/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define LCD_CLEAR                              0x01
#define LCD_4BIT_INITIALIZE                    0x02
#define LCD_DISPLAY_ON_CURSURE_OFF             0x0C
#define LCD_WRITE_DIRECTION_TO_RIGHT           0x06
#define LCD_DISPLAY_ON_CURSOR_BLINKIN          0x0E
#define LCD_SET_CURSOR_TO_FIRST_LINE           0x80
#define LCD_SET_CURSOR_TO_SEC_LINE             0xC0
#define LCD_SHIFT_CURSOR_LEFT                  0x10
#define LCD_SHIFT_CURSOR_RIGHT                 0X14
#define LCD_SHIFT_DISPLAY_LEFT                 0x18
#define LCD_SHIFT_DISPLAY_RIGHT                0x1C
#define LCD_2LINES_4BIT_MODE                   0x28
#define LCD_2LINES_8BIT_MODE                   0x38
#define LCD_1LINE_4BIT_MODE                    0x20
#define LCD_1LINE_8BIT_MODE                    0x30

#define LCD_CGRAM_START                        0x40
#define LCD_DDRAM_START                        0x80

#define ROW1  1
#define ROW2  2

#define COLUMN1   1
#define COLUMN2   2
#define COLUMN3   3
#define COLUMN4   4
#define COLUMN5   5
#define COLUMN6   6
#define COLUMN7   7
#define COLUMN8   8
#define COLUMN9   9
#define COLUMN10  10
#define COLUMN11  11
#define COLUMN12  12
#define COLUMN13  13
#define COLUMN14  14
#define COLUMN15  15
#define COLUMN16  16
/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef struct{
	St_pin_config_t lcd_rs;
	St_pin_config_t lcd_en;
	St_pin_config_t lcd_data_pins[4];
	uint8_t row;
	uint8_t column;
}St_chr_lcd_4bit_t;

typedef struct{
	St_pin_config_t lcd_rs;
	St_pin_config_t lcd_en;
	St_pin_config_t lcd_data_pins[8];
	uint8_t row;
	uint8_t column;
}St_chr_lcd_8bit_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

En_Std_ReturnType_t HLcd_4bit_init(St_chr_lcd_4bit_t* lcd);
En_Std_ReturnType_t HLcd_4bit_send_command(St_chr_lcd_4bit_t* lcd, uint8_t command);
En_Std_ReturnType_t HLcd_4bit_send_char_data(St_chr_lcd_4bit_t* lcd, uint8_t data);
En_Std_ReturnType_t HLcd_4bit_send_char_data_pos(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, uint8_t data);
En_Std_ReturnType_t HLcd_4bit_send_string(St_chr_lcd_4bit_t* lcd, char str[]);
En_Std_ReturnType_t HLcd_4bit_send_string_pos(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, char str[]);
En_Std_ReturnType_t HLcd_4bit_send_custom_char(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, 
                                                 char custom_char[], uint8_t mem_pos);

En_Std_ReturnType_t HLcd_8bit_init(St_chr_lcd_8bit_t* lcd);
En_Std_ReturnType_t HLcd_8bit_send_command(St_chr_lcd_8bit_t* lcd, uint8_t command);
En_Std_ReturnType_t HLcd_8bit_send_char_data(St_chr_lcd_8bit_t* lcd, uint8_t data);
En_Std_ReturnType_t HLcd_8bit_send_char_data_pos(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column, uint8_t data);
En_Std_ReturnType_t HLcd_8bit_send_string(St_chr_lcd_8bit_t* lcd, char str[]);
En_Std_ReturnType_t HLcd_8bit_send_string_pos(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column, char str[]);
En_Std_ReturnType_t HLcd_8bit_send_custom_char(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column,
												 char custom_char[], uint8_t mem_pos);


En_Std_ReturnType_t convert_uint8_to_string(char value, char str[]);
En_Std_ReturnType_t convert_uint16_to_string(uint16_t value, char str[]);
En_Std_ReturnType_t convert_uint32_to_string(int value, char str[]);




#endif /* CHR_LCD_H_ */