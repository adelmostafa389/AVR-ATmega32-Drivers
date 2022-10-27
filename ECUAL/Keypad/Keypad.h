/* 
 * File:   Keypad.h
 * Author: ADEL
 *
 * Created on June 3, 2022, 5:43 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/DIO/dio.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define KEYPAD_ROWS     4
#define KEYPAD_COLUMNS  4

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	KEYPAD_OK,
	KEYPAD_NULL_POINTER,
	KEYPAD_WRONG_PORT,
	KEYPAD_WRONG_PIN,
	KEYPAD_WRONG_DIRECTION,
	KEYPAD_WRONG_STATE
}En_KEYPAD_Error_t;

typedef struct{
	En_port_index_t port;
	En_pin_index_t pin;
}St_keypad_pin_t;

typedef struct{
    St_keypad_pin_t keypadRowsArr[KEYPAD_ROWS];
    St_keypad_pin_t keypadColumnsArr[KEYPAD_COLUMNS];
}St_keypad_type_t;


/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/
En_KEYPAD_Error_t Keypad_initialize(St_keypad_type_t* keypad);
En_KEYPAD_Error_t Keypad_get_value(St_keypad_type_t* keypad, uint8_t* value);


#endif	/* KEYPAD_H */

