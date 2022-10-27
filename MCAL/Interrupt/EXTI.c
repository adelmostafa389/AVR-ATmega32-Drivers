/*
 * EXTI.c
 *
 * Created: 9/4/2022 1:59:54 PM
 *  Author: ADEL
 */ 

#include "EXTI.h"

/*======= the external interrupt will triggered no matter what the pin direction is */

static En_INTx_Error_t configure_INTX_sensing_mode(const St_interrupt_INTx_t *int_cfg);// This function Configure the ext. interrupt mode
static En_INTx_Error_t Enable_INTX_interrupt(const St_interrupt_INTx_t *int_cfg);      // This funciton Enable the ext. interrupt feature
static En_INTx_Error_t Disable_INTX_interrupt(const St_interrupt_INTx_t *int_cfg);     // This function Disable the ext. interrupt feature
static En_INTx_Error_t Clear_INTX_interrupt_flag(const St_interrupt_INTx_t *int_cfg);  // This function Clear the ext. interrupt flag

/**
 * @brief This function Initalizes the external interrupt with the configurations passed through the pointer int_cfg
 * 
 * @param int_cfg 
 * @return En_INTx_Error_t 
 */
En_INTx_Error_t init_external_INTx(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		// disable the corresponding external interrupt
		ret = Disable_INTX_interrupt(int_cfg);
		// configure interrupt sensing mode
		ret = configure_INTX_sensing_mode(int_cfg);
		// Clear the external interrupt flag
		ret = Clear_INTX_interrupt_flag(int_cfg);
#if EXTERNAL_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
		// enable the corresponding external interrupt
		ret = Enable_INTX_interrupt(int_cfg);
#endif
		// Enable Global Interrupt
		ENABLE_GLOBAL_INTERRUPT();
	}
	return ret;
}

/**
 * @brief This function De initializes the external interrupt
 * 
 * @param int_cfg 
 * @return En_INTx_Error_t 
 */
En_INTx_Error_t deinit_external_INTx(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		// disable the corresponding external interrupt
		switch(int_cfg->source){
			case INT0_INTERRUPT_EXTERNAL:
			INT0_CLEAR_FLAG();
			INT0_DISABLE_INTERRUPT();
			break;
			case INT1_INTERRUPT_EXTERNAL:
			INT1_CLEAR_FLAG();
			INT1_DISABLE_INTERRUPT();
			break;
			case INT2_INTERRUPT_EXTERNAL:
			INT2_CLEAR_FLAG();
			INT2_DISABLE_INTERRUPT();
			break;
			default:
			ret = INTx_WRONG_SOURCE;
			break;
		}
	}
	return ret;
}

En_INTx_Error_t configure_INTX_sensing_mode(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		if(INT0_INTERRUPT_EXTERNAL == int_cfg->source){
			if(INTI_FALLING_EDGE == int_cfg->edge)     { INT0_SENSE_FALLING_EDGE(); }
			else if(INTI_RISING_EDGE == int_cfg->edge) { INT0_SENSE_RISING_EDGE(); }
			else if(INTI_LOGIC_CHANGE == int_cfg->edge){ INT0_SENSE_LOGIC_CHANGE(); }
			else if(INTI_LOW_LEVEL == int_cfg->edge)   { INT0_SENSE_LOW_LEVEL(); }
			else{ ret = INTx_WRONG_EDGE;  }
		}
		else if(INT1_INTERRUPT_EXTERNAL == int_cfg->source){
			if(INTI_FALLING_EDGE == int_cfg->edge)     { INT1_SENSE_FALLING_EDGE(); }
			else if(INTI_RISING_EDGE == int_cfg->edge) { INT1_SENSE_RISING_EDGE(); }
			else if(INTI_LOGIC_CHANGE == int_cfg->edge){ INT1_SENSE_LOGIC_CHANGE(); }
			else if(INTI_LOW_LEVEL == int_cfg->edge)   { INT1_SENSE_LOW_LEVEL(); }
			else{ ret = INTx_WRONG_EDGE; }
		}
		else if(INT2_INTERRUPT_EXTERNAL == int_cfg->source){
			if(INTI_FALLING_EDGE == int_cfg->edge)     { INT2_SENSE_FALLING_EDGE(); }
			else if(INTI_RISING_EDGE == int_cfg->edge) { INT2_SENSE_RISING_EDGE(); }
			else{ ret = INTx_WRONG_EDGE; }
		}
		else{ ret = INTx_WRONG_SOURCE; }
	}
	return ret;
}

static En_INTx_Error_t Clear_INTX_interrupt_flag(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		switch(int_cfg->source){
			case INT0_INTERRUPT_EXTERNAL:
			INT0_CLEAR_FLAG();
			break;
			case INT1_INTERRUPT_EXTERNAL:
			INT1_CLEAR_FLAG();
			break;
			case INT2_INTERRUPT_EXTERNAL:
			INT2_CLEAR_FLAG();
			break;
			default:
			ret = INTx_WRONG_SOURCE;
			break;
		}
	}
	return ret;
}
static En_INTx_Error_t Enable_INTX_interrupt(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		switch(int_cfg->source){
			case INT0_INTERRUPT_EXTERNAL:
			INT0_ENABLE_INTERRUPT();
			break;
			case INT1_INTERRUPT_EXTERNAL:
			INT1_ENABLE_INTERRUPT();
			break;
			case INT2_INTERRUPT_EXTERNAL:
			INT2_ENABLE_INTERRUPT();
			break;
			default:
			ret = INTx_WRONG_SOURCE;
			break;
		}
	}
	return ret;
}
static En_INTx_Error_t Disable_INTX_interrupt(const St_interrupt_INTx_t *int_cfg){
	En_INTx_Error_t ret = INTx_OK;
	if(NULL == int_cfg){
		ret = INTx_NULL_POINTER;
	}
	else{
		switch(int_cfg->source){
			case INT0_INTERRUPT_EXTERNAL:
			INT0_DISABLE_INTERRUPT();
			break;
			case INT1_INTERRUPT_EXTERNAL:
			INT1_DISABLE_INTERRUPT();
			break;
			case INT2_INTERRUPT_EXTERNAL:
			INT2_DISABLE_INTERRUPT();
			break;
			default:
			ret = INTx_WRONG_SOURCE;
			break;
		}	
	}
	return ret;
}