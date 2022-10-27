/* 
 * File:   Keypad.h
 * Author: ADEL
 *
 * Created on June 3, 2022, 5:43 PM
 */

#include "Keypad.h"

static const uint8_t keypad_buttons[KEYPAD_ROWS][KEYPAD_COLUMNS] =
{
    {'7', '8', '9', '/'},  
    {'4', '5', '6', '*'},  
    {'1', '2', '3', '-'},  
    {'#', '0', '=', '+'}  
};

/**
 * #brief Initialize 
 * @param keypad
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (KEYPAD_NULL_POINTER) : The function has issue while execution
 */
En_KEYPAD_Error_t Keypad_initialize(St_keypad_type_t* keypad){
    En_KEYPAD_Error_t error_ret = KEYPAD_OK;
	St_pin_config_t keypadPinConfig;
    uint8_t rowsCounter = 0;
    uint8_t columnsCounter = 0;
    if(NULL == keypad){ 
        error_ret = KEYPAD_NULL_POINTER;
    }
    else{
        for(rowsCounter = 0; rowsCounter < KEYPAD_ROWS; rowsCounter++)
        {
			keypadPinConfig.direction = GPIO_DIRECTION_OUTPUT;
			keypadPinConfig.initialVal = GPIO_LOW;
			keypadPinConfig.port = keypad->keypadRowsArr[rowsCounter].port;
			keypadPinConfig.pin = keypad->keypadRowsArr[rowsCounter].pin;
            error_ret = DIO_init(&keypadPinConfig);
        }
        for(columnsCounter = 0; columnsCounter < KEYPAD_COLUMNS; columnsCounter++)
        {
            error_ret = DIO_set_direction(keypad->keypadColumnsArr[columnsCounter].port, 
			                              keypad->keypadColumnsArr[columnsCounter].pin, 
										  GPIO_DIRECTION_INPUT);
        }
    }
    return error_ret;
}

En_DIO_logic_t column_logic = 0;

/**
 * #brief 
 * @param keypad
 * @param value
 * @return Status of the function
 *          (E_OK)     : The function done successfully
 *          (KEYPAD_NULL_POINTER) : The function has issue while execution
 */
En_KEYPAD_Error_t Keypad_get_value(St_keypad_type_t* keypad, uint8_t* value){
    En_KEYPAD_Error_t error_ret = KEYPAD_OK;
    uint8_t rowsCounter = 0;
    uint8_t columnsCounter = 0;
    if(NULL == keypad){
        error_ret = KEYPAD_NULL_POINTER;
    }
    else{
        for(rowsCounter = 0; rowsCounter < KEYPAD_ROWS; rowsCounter++){
            error_ret = DIO_write(keypad->keypadRowsArr[rowsCounter].port, keypad->keypadRowsArr[rowsCounter].pin, GPIO_HIGH);
            for(columnsCounter = 0; columnsCounter < KEYPAD_COLUMNS; columnsCounter++){
                error_ret = DIO_read(keypad->keypadColumnsArr[columnsCounter].port,
				                     keypad->keypadColumnsArr[columnsCounter].pin,
									 &column_logic);
				if(GPIO_HIGH == column_logic){
					*value = keypad_buttons[rowsCounter][columnsCounter];
				}
				else{ /* Do nothing */ }      
            }
			error_ret  = DIO_write(keypad->keypadRowsArr[rowsCounter].port, keypad->keypadRowsArr[rowsCounter].pin, GPIO_LOW);
        }
    }
    return error_ret;
}
