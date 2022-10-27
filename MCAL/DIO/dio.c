/*
 * dio.c
 *
 * Created: 8/29/2022 10:12:31 AM
 *  Author: ADEL
 */ 

#include "dio.h"

/**
 * @brief This function initialize the DIO pin direction and the initial value if output
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_init(const St_pin_config_t* pin_cfg){
	En_DIO_Error_t ret = DIO_OK;
	if(NULL == pin_cfg){
		ret = DIO_NULL_POINTER;
	}
	else{
		ret = DIO_set_direction(pin_cfg->port, pin_cfg->pin, pin_cfg->direction);
		ret = DIO_write(pin_cfg->port, pin_cfg->pin, pin_cfg->initialVal);
	}
	return ret;
}

/**
 * @brief This function Write digital value to the DIO pin
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_write(En_port_index_t port_index, En_pin_index_t pin_index, En_DIO_logic_t value){
	En_DIO_Error_t ret = DIO_OK;
	if(pin_index >= NUM_OF_PINS){
		ret = DIO_WRONG_PIN;
	}
	else{
		if (GPIO_HIGH == value){
			switch(port_index){
				case PORTA_INDEX:
				SET_BIT(PORTA,pin_index);
				break;
				case PORTB_INDEX:
				SET_BIT(PORTB,pin_index);
				break;
				case PORTC_INDEX:
				SET_BIT(PORTC,pin_index);
				break;
				case PORTD_INDEX:
				SET_BIT(PORTD,pin_index);
				break;
				default:
				ret = DIO_WRONG_PORT;
				break;
			}
		}
		else if(GPIO_LOW == value){
			switch(port_index){
				case PORTA_INDEX:
				CLEAR_BIT(PORTA,pin_index);
				break;
				case PORTB_INDEX:
				CLEAR_BIT(PORTB,pin_index);
				break;
				case PORTC_INDEX:
				CLEAR_BIT(PORTC,pin_index);
				break;
				case PORTD_INDEX:
				CLEAR_BIT(PORTD,pin_index);
				break;
				default:
				ret = DIO_WRONG_PORT;
				break;
			}
		}
		else{
			ret = DIO_WRONG_LOGIC_VALUE;
		}
	}
	return ret;
}

/**
 * @brief This function Toggle the state of the DIO pin
 * 
 * @param pin_cfg 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_toggle( St_pin_config_t* pin_cfg){
	En_DIO_Error_t ret = DIO_OK;
	if(NULL == pin_cfg){
		ret = DIO_NULL_POINTER;
	}
	else if(pin_cfg->pin >= NUM_OF_PINS){
		ret = DIO_WRONG_PIN;
	}
	else{
		switch(pin_cfg->port){
			case PORTA_INDEX:
			TOGGLE_BIT(PORTA, pin_cfg->pin);
			break;
			case PORTB_INDEX:
			TOGGLE_BIT(PORTB, pin_cfg->pin);
			break;
			case PORTC_INDEX:
			TOGGLE_BIT(PORTC, pin_cfg->pin);
			break;
			case PORTD_INDEX:
			TOGGLE_BIT(PORTD, pin_cfg->pin);
			break;
			default:
			ret = DIO_WRONG_PORT;
			break;
		}
		TOGGLE_BIT(pin_cfg->port, pin_cfg->pin);
	}
	return ret;
}

/**
 * @brief This function read the state of the DIO pin and return the value through a pointer
 * 
 * @param pin_cfg 
 * @param value 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_read(En_port_index_t port_index, En_pin_index_t pin_index, En_DIO_logic_t* value){
	En_DIO_Error_t ret = DIO_OK;
	if(NULL == value){
		ret = DIO_NULL_POINTER;
	}
	else if(pin_index >= NUM_OF_PINS){
		ret = DIO_WRONG_PIN;
	}
	else{
		switch(port_index){
			case PORTA_INDEX:
			*value = READ_BIT(PINA, pin_index);
			break;
			case PORTB_INDEX:
			*value = READ_BIT(PINB, pin_index);
			break;
			case PORTC_INDEX:
			*value = READ_BIT(PINC, pin_index);
			break;
			case PORTD_INDEX:
			*value = READ_BIT(PIND, pin_index);
			break;
			default:
			ret = DIO_WRONG_PORT;
			break;
		}
	}
	return ret;
}

/**
 * @brief This function set the DIO pin direction
 * 
 * @param port_index 
 * @param pin_index 
 * @param direction 
 * @return En_DIO_Error_t 
 */
En_DIO_Error_t DIO_set_direction(En_port_index_t port_index, En_pin_index_t pin_index, En_direction_t direction){
	En_DIO_Error_t ret = DIO_OK;
	if(pin_index >= NUM_OF_PINS){
		ret = DIO_WRONG_PIN;
	}
	else if (GPIO_DIRECTION_OUTPUT == direction){
		switch(port_index){
			case PORTA_INDEX:
			SET_BIT(DDRA,pin_index);
			break;
			case PORTB_INDEX:
			SET_BIT(DDRB,pin_index);
			break;
			case PORTC_INDEX:
			SET_BIT(DDRC,pin_index);
			break;
			case PORTD_INDEX:
			SET_BIT(DDRD,pin_index);
			break;
			default:
			ret = DIO_WRONG_PORT;
			break;
		}
	}
	else if(GPIO_DIRECTION_INPUT == direction){
		switch(port_index){
			case PORTA_INDEX:
			CLEAR_BIT(DDRA,pin_index);
			break;
			case PORTB_INDEX:
			CLEAR_BIT(DDRB,pin_index);
			break;
			case PORTC_INDEX:
			CLEAR_BIT(DDRC,pin_index);
			break;
			case PORTD_INDEX:
			CLEAR_BIT(DDRD,pin_index);
			break;
			default:
			ret = DIO_WRONG_PORT;
			break;
		}
	}
	else{
		ret = DIO_WRONG_DIRECTION;
	}
	return ret;
}