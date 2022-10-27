/*
 * button.h
 *
 * Created: 8/29/2022 4:46:26 PM
 *  Author: ADEL
 */ 

#ifndef BUTTON_H_
#define BUTTON_H_

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/DIO/dio.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef enum{
	BUTTON_PRESSED = 0,
	BUTTON_RELEASED
}button_state_t;

typedef enum{
	BUTTON_ACTIVE_HIGH,
	BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
	St_pin_config_t button_pin;
	button_state_t button_state;
	button_active_t button_connection;
}st_button_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

En_Std_ReturnType_t Button_init(st_button_t* button_cfg);

En_Std_ReturnType_t Button_read(st_button_t* button_cfg, uint8_t* buttonState);




#endif /* BUTTON_H_ */