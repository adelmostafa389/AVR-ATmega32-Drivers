/*
 * dio.h
 *
 * Created: 8/29/2022 10:12:48 AM
 *  Author: ADEL
 */ 


#ifndef DIO_H_
#define DIO_H_


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../Utilities/types.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"
/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	DIO_OK,
	DIO_NULL_POINTER,
	DIO_WRONG_PORT,
	DIO_WRONG_PIN,
	DIO_WRONG_DIRECTION,
	DIO_WRONG_LOGIC_VALUE
}En_DIO_Error_t;

typedef enum{
	GPIO_LOW = 0,
	GPIO_HIGH
}En_DIO_logic_t;

typedef enum{
	GPIO_DIRECTION_INPUT = 0,
	GPIO_DIRECTION_OUTPUT
}En_direction_t;

typedef enum{
	PIN0 = 0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	NUM_OF_PINS
}En_pin_index_t;

typedef enum{
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX,
	PORTE_INDEX,
	NUM_OF_PORTS
}En_port_index_t;

typedef struct{
	En_port_index_t port;      
	En_pin_index_t pin;       
	En_direction_t direction; 
	En_DIO_logic_t initialVal;     
}St_pin_config_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * @brief This function initialize the DIO pin direction and the initial value if output
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_init(const St_pin_config_t* pin_cfg);

/**
 * @brief This function Write digital value to the DIO pin
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_write(En_port_index_t port_index, En_pin_index_t pin_index, En_DIO_logic_t value);

/**
 * @brief This function Toggle the state of the DIO pin
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_toggle( St_pin_config_t* pin_cfg);

/**
 * @brief This function read the state of the DIO pin and return the value through a pointer
 * 
 * @param pin_cfg 
 * @param value 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_read(En_port_index_t port_index, En_pin_index_t pin_index, En_DIO_logic_t* value);

/**
 * @brief This function set the DIO pin direction
 * 
 * @param port_index 
 * @param pin_index 
 * @param direction 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_set_direction(En_port_index_t port_index, En_pin_index_t pin_index, En_direction_t direction);



#endif /* DIO_H_ */