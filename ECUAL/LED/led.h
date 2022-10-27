/*
 * led.h
 *
 * Created: 8/29/2022 12:18:31 PM
 *  Author: ADEL
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/

#include "../../MCAL/DIO/dio.h"

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	LED_OK,
	LED_NULL_POINTER,
	LED_WRONG_PORT,
	LED_WRONG_PIN,
	LED_WRONG_DIRECTION,
	LED_WRONG_STATE
}En_LED_Error_t;

typedef enum{
	LED_OFF,
	LED_ON
}En_led_status_t;

typedef struct{
	En_port_index_t port;
	En_pin_index_t pin;
	En_led_status_t state;
}St_led_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * @brief This function initialize the DIO pin the LED connected to
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t LED_init(St_led_t *led);

/**
 * @brief This function Write HIGH value to the DIO pin to turn ON the LED
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t turn_led_on(St_led_t *led);

/**
 * @brief This function Write LOW value to the DIO pin to turn OFF the LED
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t turn_led_off(St_led_t *led);

/**
 * @brief This function toggle the LED state by toggling the digital value at the DIO pin
 * 
 * @param led 
 * @return En_LED_Error_t 
 */
En_LED_Error_t toggle_led(St_led_t *led);


#endif /* INCFILE1_H_ */