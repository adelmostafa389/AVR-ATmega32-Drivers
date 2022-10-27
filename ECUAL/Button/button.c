/*
 * button.c
 *
 * Created: 8/29/2022 4:46:15 PM
 *  Author: ADEL
 */ 

#include "button.h"


En_Std_ReturnType_t Button_init(st_button_t* button_cfg){
	En_Std_ReturnType_t ret = OK;
	if(NULL == button_cfg){
		ret = NOT_OK;
	}
	else{
		DIO_init(&(button_cfg->button_pin));
	}
	return ret;
}

En_Std_ReturnType_t Button_read(st_button_t* button_cfg, uint8_t* buttonState){
	
	En_Std_ReturnType_t ret = OK;
	if((NULL == button_cfg) || (NULL == buttonState)){
		ret = NOT_OK;
	}
	else{
		En_DIO_logic_t Pin_Logic_Status = GPIO_LOW;
		DIO_read(button_cfg->button_pin.port, button_cfg->button_pin.pin, &Pin_Logic_Status);
		if(BUTTON_ACTIVE_HIGH == button_cfg->button_connection){
			if(GPIO_HIGH == Pin_Logic_Status){
				*buttonState = BUTTON_PRESSED;
			}
			else{
				*buttonState = BUTTON_RELEASED;
			}
		}
		else if(BUTTON_ACTIVE_LOW == button_cfg->button_connection){
			if(GPIO_HIGH == Pin_Logic_Status){
				*buttonState = BUTTON_RELEASED;
			}
			else{
				*buttonState = BUTTON_PRESSED;
			}
		}
		else { /* Nothing */ }
	}
	return ret;
}