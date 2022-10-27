/*
 * Chr_LCD.c
 *
 * Created: 9/8/2022 3:27:16 PM
 *  Author: ADEL
 */ 

#include "Chr_LCD.h"

static En_Std_ReturnType_t LCD_send_enable_signal(St_pin_config_t* EN_pin);

static En_Std_ReturnType_t LCD_send_4bit(St_chr_lcd_4bit_t* lcd, uint8_t data);
static En_Std_ReturnType_t LCD_4bit_set_cursor(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column);

static En_Std_ReturnType_t LCD_8bit_set_cursor(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column);

En_Std_ReturnType_t HLcd_4bit_init(St_chr_lcd_4bit_t* lcd){
    En_Std_ReturnType_t error_ret = OK;
    uint8_t l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
	    lcd->lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
	    lcd->lcd_rs.initialVal = GPIO_LOW;
        error_ret = DIO_init(&(lcd->lcd_rs));
        lcd->lcd_en.direction = GPIO_DIRECTION_OUTPUT;
        lcd->lcd_en.initialVal = GPIO_LOW;
        error_ret = DIO_init(&(lcd->lcd_en));
        for(l_counter = 0; l_counter < 4; l_counter++){
			lcd->lcd_data_pins[l_counter].direction = GPIO_DIRECTION_OUTPUT;
			lcd->lcd_data_pins[l_counter].initialVal = GPIO_LOW;
            error_ret = DIO_init(&(lcd->lcd_data_pins[l_counter]));
        }
        _delay_ms(20);
        error_ret = HLcd_4bit_send_command(lcd, LCD_4BIT_INITIALIZE);
        error_ret = HLcd_4bit_send_command(lcd, LCD_2LINES_4BIT_MODE);   
        error_ret = HLcd_4bit_send_command(lcd, LCD_DISPLAY_ON_CURSURE_OFF);
        error_ret = HLcd_4bit_send_command(lcd, LCD_WRITE_DIRECTION_TO_RIGHT);
        error_ret = HLcd_4bit_send_command(lcd, LCD_CLEAR);   
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_command(St_chr_lcd_4bit_t* lcd, uint8_t command){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = DIO_write(lcd->lcd_rs.port, lcd->lcd_rs.pin, GPIO_LOW);
        error_ret = LCD_send_4bit(lcd, (command >> 4));     // Sending upper nibble
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
        error_ret = LCD_send_4bit(lcd, command);            // Sending lower nibble
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_char_data(St_chr_lcd_4bit_t* lcd, uint8_t data){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
		if((lcd->row == ROW1) && (lcd->column > COLUMN16)){
			lcd->column = COLUMN1;
			lcd->row = ROW2;
			LCD_4bit_set_cursor(lcd, lcd->row, lcd->column);
		}
		else if((lcd->row == ROW2) && (lcd->column > COLUMN16)){
			lcd->column = COLUMN1;
			lcd->row = ROW1;
			LCD_4bit_set_cursor(lcd, lcd->row, lcd->column);
		} 
		else{
			(lcd->column)++;
		}
	    error_ret = DIO_write(lcd->lcd_rs.port, lcd->lcd_rs.pin, GPIO_HIGH);
        error_ret = LCD_send_4bit(lcd, (data >> 4));
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
        error_ret = LCD_send_4bit(lcd, data);
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_char_data_pos(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, uint8_t data){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = LCD_4bit_set_cursor(lcd, row, column);
        error_ret = HLcd_4bit_send_char_data(lcd, data);
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_string(St_chr_lcd_4bit_t* lcd, char str[]){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
         while(*str){
            error_ret = HLcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_string_pos(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, char str[]){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = LCD_4bit_set_cursor(lcd, row, column);
        while(*str){
            error_ret = HLcd_4bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_4bit_send_custom_char(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column, char custom_char[], uint8_t mem_pos){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        
    }
    return error_ret;
}


En_Std_ReturnType_t HLcd_8bit_init(St_chr_lcd_8bit_t* lcd){
    En_Std_ReturnType_t error_ret = OK;
    uint8_t l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
	    lcd->lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
	    lcd->lcd_rs.initialVal = GPIO_LOW;
	    error_ret = DIO_init(&(lcd->lcd_rs));
	    lcd->lcd_en.direction = GPIO_DIRECTION_OUTPUT;
	    lcd->lcd_en.initialVal = GPIO_LOW;
	    error_ret = DIO_init(&(lcd->lcd_en));
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = DIO_init(&(lcd->lcd_data_pins[l_counter]));
        }
        _delay_ms(20);
        error_ret = HLcd_8bit_send_command(lcd, LCD_2LINES_8BIT_MODE);      
        error_ret = HLcd_8bit_send_command(lcd, LCD_DISPLAY_ON_CURSURE_OFF);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_WRITE_DIRECTION_TO_RIGHT);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_CLEAR);        
        error_ret = HLcd_8bit_send_command(lcd, LCD_SET_CURSOR_TO_FIRST_LINE);
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_command(St_chr_lcd_8bit_t* lcd, uint8_t command){
    En_Std_ReturnType_t error_ret = OK;
    uint8_t l_counter = ZERO_INIT;
	uint8_t dataBitToSend = 0;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
	    error_ret = DIO_write(lcd->lcd_rs.port, lcd->lcd_rs.pin, GPIO_LOW);
        for(l_counter = 0; l_counter < 8; l_counter++){
			dataBitToSend = ((command >> l_counter)& (uint8_t)0x01);
            error_ret = DIO_write(lcd->lcd_data_pins[l_counter].port, lcd->lcd_data_pins[l_counter].pin, dataBitToSend);
        }
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_char_data(St_chr_lcd_8bit_t* lcd, uint8_t data){
    En_Std_ReturnType_t error_ret = OK;
        uint8_t l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = DIO_write(lcd->lcd_rs.port, lcd->lcd_rs.pin, GPIO_HIGH);
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = DIO_write(lcd->lcd_data_pins[l_counter].port, lcd->lcd_data_pins[l_counter].pin, ((data >> l_counter)& (uint8_t)0x01));
        }
        error_ret = LCD_send_enable_signal(&(lcd->lcd_en));
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_char_data_pos(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column, uint8_t data){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = LCD_8bit_set_cursor(lcd, row, column);
        error_ret = HLcd_8bit_send_char_data(lcd, data);
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_string(St_chr_lcd_8bit_t* lcd, char str[]){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        while(*str){
            error_ret = HLcd_8bit_send_char_data(lcd, *str);
			str++;
        }
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_string_pos(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column, char str[]){
    En_Std_ReturnType_t error_ret = OK;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = LCD_8bit_set_cursor(lcd, row, column);
        while(*str){
            error_ret = HLcd_8bit_send_char_data(lcd, *str);
            str++;
        }
    }
    return error_ret;
}

En_Std_ReturnType_t HLcd_8bit_send_custom_char(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column,
                                            char custom_char[], uint8_t mem_pos){
    En_Std_ReturnType_t error_ret = OK;
    uint8_t l_counter = ZERO_INIT;
    if(NULL == lcd){ 
        error_ret = NOT_OK;
    }
    else{
        error_ret = HLcd_8bit_send_command(lcd, (LCD_CGRAM_START + (8*mem_pos)));
        for(l_counter = 0; l_counter < 8; l_counter++){
            error_ret = HLcd_8bit_send_char_data(lcd, custom_char[l_counter]);
        }
        error_ret = HLcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return error_ret;
}



En_Std_ReturnType_t convert_uint8_to_string(char value, char str[]){
    En_Std_ReturnType_t errorState = OK;
    if(NULL == str){
        errorState = NOT_OK;
    }
    else{
        memset((char *)str, '\0', 4);
        sprintf(str, "%i", value);
    }    
    return errorState;
}

En_Std_ReturnType_t convert_uint16_to_string(uint16_t value, char str[]){
    En_Std_ReturnType_t errorState = OK;
    uint8_t Temp_String[6] = {0};
    uint8_t DataCounter = 0;
    if(NULL == str){
        errorState = NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return errorState;
}

En_Std_ReturnType_t convert_uint32_to_string(int value, char str[]){
    En_Std_ReturnType_t errorState = OK;
    if(NULL == str){
        errorState = NOT_OK;
    }
    else{    
        memset((char *)str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return errorState;
}

static En_Std_ReturnType_t LCD_send_4bit(St_chr_lcd_4bit_t* lcd, uint8_t data){
    En_Std_ReturnType_t error_ret = OK;
    error_ret = DIO_write(lcd->lcd_data_pins[0].port, lcd->lcd_data_pins[0].pin, (data>>0) & 0x01);
    error_ret = DIO_write(lcd->lcd_data_pins[1].port, lcd->lcd_data_pins[1].pin, (data>>1) & 0x01);
    error_ret = DIO_write(lcd->lcd_data_pins[2].port, lcd->lcd_data_pins[2].pin, (data>>2) & 0x01);
    error_ret = DIO_write(lcd->lcd_data_pins[3].port, lcd->lcd_data_pins[3].pin, (data>>3) & 0x01);
    return error_ret;
}

static En_Std_ReturnType_t LCD_send_enable_signal(St_pin_config_t* EN_pin){
    En_Std_ReturnType_t error_ret = OK;
    error_ret = DIO_write(EN_pin->port, EN_pin->pin, GPIO_HIGH);
    _delay_us(5);
    error_ret = DIO_write(EN_pin->port, EN_pin->pin, GPIO_LOW);
    _delay_ms(2);
    return error_ret;
}

static En_Std_ReturnType_t LCD_8bit_set_cursor(St_chr_lcd_8bit_t* lcd, uint8_t row, uint8_t column){
    En_Std_ReturnType_t error_ret = OK;
    column--;
    switch(row){
    case ROW1:
        error_ret = HLcd_8bit_send_command(lcd, (0x80 + column));
        break; 
    case ROW2:
        error_ret = HLcd_8bit_send_command(lcd, (0xC0 + column));
        break;
    default:
        break;
    }
    return error_ret;
}

static En_Std_ReturnType_t LCD_4bit_set_cursor(St_chr_lcd_4bit_t* lcd, uint8_t row, uint8_t column){
    En_Std_ReturnType_t error_ret = OK;
    lcd->column = column;
    lcd->row = row;
    column--;
    switch(row){
    case ROW1:
        error_ret = HLcd_4bit_send_command(lcd, (0x80 + column));
        break; 
    case ROW2:
        error_ret = HLcd_4bit_send_command(lcd, (0xc0 + column));
        break;
    default:
        break;
    }
    return error_ret;
}

