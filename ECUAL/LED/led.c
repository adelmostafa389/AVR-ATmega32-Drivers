/*
 * led.c
 *
 * Created: 8/29/2022 12:18:51 PM
 *  Author: ADEL
 */ 

#include "led.h"


/**
 * @brief This function initialize the DIO pin the LED connected to
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t LED_init(St_led_t *led){
	En_LED_Error_t ret = LED_OK;
	if(NULL == led){
		ret = LED_NULL_POINTER;
	}
	else{
		St_pin_config_t led_pin_cfg = { 
			.port = led->port, 
			.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.initialVal = led->state 
		};
		ret = DIO_init(&led_pin_cfg);
	}
	return ret;
}

/**
 * @brief This function Write HIGH value to the DIO pin to turn ON the LED
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t turn_led_on(St_led_t *led){
	En_LED_Error_t ret = LED_OK;
	if(NULL == led){
		ret = LED_NULL_POINTER;
	}
	else{
		St_pin_config_t led_pin_cfg = {
			.port = led->port,
			.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.initialVal = led->state 
		};
		ret = DIO_write(led_pin_cfg.port, led_pin_cfg.pin, GPIO_HIGH);
	}
	if(LED_OK == ret){ led->state = LED_ON;}
	return ret;
}

/**
 * @brief This function Write LOW value to the DIO pin to turn OFF the LED
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t turn_led_off(St_led_t *led){
	En_LED_Error_t ret = LED_OK;
	if(NULL == led){
		ret = LED_NULL_POINTER;
	}
	else{
		St_pin_config_t led_pin_cfg = {
			.port = led->port,
			.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.initialVal = led->state 
		};
		ret = DIO_write(led_pin_cfg.port, led_pin_cfg.pin, GPIO_LOW);
	}
	if(LED_OK == ret){ led->state = LED_OFF;}
	return ret;
}

/**
 * @brief This function toggle the LED state by toggling the digital value at the DIO pin
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t toggle_led(St_led_t *led){
	En_LED_Error_t ret = LED_OK;
	if(NULL == led){
		ret = LED_NULL_POINTER;
	}
	else{
		St_pin_config_t led_pin_cfg = {
			.port = led->port,
			.pin = led->pin,
			.direction = GPIO_DIRECTION_OUTPUT,
			.initialVal = led->state 
		};
		ret = DIO_toggle(&led_pin_cfg);
		if(led->state == LED_OFF){
			led->state = LED_ON;
		}
		else{
			led->state = LED_OFF;
		}
	}
	return ret;
}
	
