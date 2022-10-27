/*
 * timer0.c
 *
 * Created: 9/3/2022 12:22:02 PM
 *  Author: ADEL
 */ 


#include "timer0.h"

static En_Timer0_Error_t timer0_config_compare_output_mode(st_timer0_config_t* timer0_cfg);
static void timer0_enable_interrupt(void);

/**
 * @brief This function initializes timer0 configuration
 * 
 * @param timer0_cfg 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_init(st_timer0_config_t* timer0_cfg){
	En_Timer0_Error_t ret = TIEMR0_OK;
	if(NULL == timer0_cfg){
		ret = TIMER0_NULL_POINTER;
	}
	else{
		timer0_stop();
		// set timer mode: configure Waveform Generation Mode bits WGM0 in TCCR0 register
		if(timer0_cfg->mode > NUM_OF_TIMER0_MODES)
		{ ret = TIMER0_WRONG_MODE; }
		else{
			TCCR0bits.WGM00 = (timer0_cfg->mode);
			TCCR0bits.WGM01 = ((timer0_cfg->mode)>>1);  
		}
		// Compare Output Mode bits COM00, COM01
		ret = timer0_config_compare_output_mode(timer0_cfg);
		if(T0_NORMAL_MODE ==timer0_cfg->mode){
			// set the preload value
			if((timer0_cfg->preloadValue > 255) || ( timer0_cfg->preloadValue < 0))
			{ ret = TIMER0_WRONG_PRELOAD_VALUE; }
			else{ TCNT0 = timer0_cfg->preloadValue; }
		}
		else if(T0_CTC_MODE == timer0_cfg->mode){
			// set the preload value
			if((timer0_cfg->preloadValue > 255) || ( timer0_cfg->preloadValue < 0))
			{ ret = TIMER0_WRONG_PRELOAD_VALUE; }
			else{ OCR0 = timer0_cfg->preloadValue; }
		}
		else{
			// Set CO0 pin direction to Output for PWM modes
			DIO_set_direction(PORTB_INDEX, PIN3, GPIO_DIRECTION_OUTPUT);
			// Set the initial preload PWM duty cycle
			if((timer0_cfg->preload_pwmDC > 100) || ( timer0_cfg->preload_pwmDC < 0))
			{ ret = TIMER0_WRONG_PWM_DUTY_CYCLE; }
			else{ ret = timer0_pwm_set_DC(timer0_cfg, timer0_cfg->preload_pwmDC); }
		}
		// set timer clock source
		if(timer0_cfg->clockSource > T0_NUM_OF_CLK_SCR_OPTIONS)
		{ ret = TIMER0_WRONG_CLOCK_SOURCE; }
		else{ TIMER0_SET_CLK_SRC(timer0_cfg->clockSource); }
		// Enable timer interrupt 
		timer0_enable_interrupt();
	}
	return ret;
}

/**
 * @brief This function stops the the timer0 to count by clearing the clock source bits
 * 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_stop(void){
	// clear clock select bit CS00, CS01, CS02 in TCCR0 register
	TCCR0bits.CS0 = T0_NO_CLOCK_SOURCE;
	// Disable timer0 overflow interrupt and on compare interrupt
	TIMER0_OC_DIABLE_INTERRUPT();
	TIMER0_OVF_DIABLE_INTERRUPT();
	return TIEMR0_OK;
}

/**
 * @brief This function resume timer0 countinting by setting the clock source back if timer0_stop() was called before 
 * 
 * @param timer0_cfg 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_start(st_timer0_config_t* timer0_cfg){
	// set timer clock source
	En_Timer0_Error_t ret = TIEMR0_OK;
	if(NULL == timer0_cfg){
		ret = TIMER0_NULL_POINTER;
	}
	else{
		timer0_enable_interrupt();
		TCCR0bits.CS0 = timer0_cfg->clockSource;
	}
	return ret;
}

/**
 * @brief This function write value to Timer0 register TCNT0
 * 
 * @param value 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_write(st_timer0_config_t* timer0_cfg, uint8_t value){
	En_Timer0_Error_t ret = TIEMR0_OK;
	if(NULL == timer0_cfg){
		ret = TIMER0_NULL_POINTER;
	}
	else{
		TCNT0 = value;
	}
	return ret;
}

/**
 * @brief This function reads the value at the Timer0 register TCNT0
 * 
 * @param value 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_read(st_timer0_config_t* timer0_cfg, uint8_t*  value){
	En_Timer0_Error_t ret = TIEMR0_OK;
	if((NULL == value) || (NULL == timer0_cfg)){
		ret = TIMER0_NULL_POINTER;
	}
	else{
		*value = TCNT0;
	}
	return ret;
}

/**
 * @brief This function set the PWM Duty Cycle of timer0 in the PWM modes
 * 
 * @param timer0_cfg 
 * @param dutyCycle 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_pwm_set_DC(st_timer0_config_t* timer0_cfg, uint8_t dutyCycle){
	En_Timer0_Error_t ret = TIEMR0_OK;
	if(NULL == timer0_cfg){
		ret = TIMER0_NULL_POINTER;
	}
	else if(dutyCycle > 100 || ( dutyCycle < 0))
	{ 
		ret = TIMER0_WRONG_PWM_DUTY_CYCLE; 
	}
	else{
		if(T0_FAST_PWM_MODE == timer0_cfg->mode){
			if(OC0_FAST_PWM_CLEAR == timer0_cfg->compareModeFastPWM){
				OCR0 = (dutyCycle*256/(100)) -1;
			}
			else if(OC0_FAST_PWM_SET == timer0_cfg->compareModeFastPWM){
				OCR0 = 256 - (dutyCycle*256/(100)) -1;
			}
			else{ ret = TIMER0_WRONG_MODE; }
		}
		else if(T0_PHASE_CORRECT_PWM_MODE == timer0_cfg->mode){
			if(OC0_CORRECT_PWM_CLEAR == timer0_cfg->compareModeCorrectPWM){
				OCR0 = (dutyCycle*510/(2*100));
			}
			else if(OC0_CORRECT_PWM_SET == timer0_cfg->compareModeCorrectPWM){
				OCR0 = (510 -(dutyCycle*510/100))/2;
			}
			else{ ret = TIMER0_WRONG_MODE; }
		}
		else{ ret = TIMER0_WRONG_MODE; }
	}
	return ret;
}


static En_Timer0_Error_t timer0_config_compare_output_mode(st_timer0_config_t* timer0_cfg){
	En_Timer0_Error_t ret = TIEMR0_OK;
	if(NULL == timer0_cfg){
		ret = TIMER0_NULL_POINTER;
	}
	else{
		switch(timer0_cfg->mode){
			case T0_NORMAL_MODE:
			if(timer0_cfg->compareModeNonPWM > NUM_OF_OC0_NONPWM_MODES){ ret = TIMER0_WRONG_CO_MODE;}
			else{ TCCR0bits.COM0 = timer0_cfg->compareModeNonPWM; }
			break;
			case T0_CTC_MODE:
			if(timer0_cfg->compareModeNonPWM > NUM_OF_OC0_NONPWM_MODES){ ret = TIMER0_WRONG_CO_MODE;}
			else{ TCCR0bits.COM0 = timer0_cfg->compareModeNonPWM; }
			break;
			case T0_FAST_PWM_MODE:
			if(timer0_cfg->compareModeFastPWM > NUM_OF_OC0_FAST_PWM_MODES){ ret = TIMER0_WRONG_CO_MODE;}
			else{ TCCR0bits.COM0 = timer0_cfg->compareModeFastPWM; }
			break;
			case T0_PHASE_CORRECT_PWM_MODE:
			if(timer0_cfg->compareModeCorrectPWM > NUM_OF_OC0_CORRECT_PWM_MODES){ ret = TIMER0_WRONG_CO_MODE;}
			else{ TCCR0bits.COM0 = timer0_cfg->compareModeCorrectPWM; }
			break;
			default:
			ret = TIMER0_WRONG_MODE;
			break;
		}
	}
	return ret;
}

static void timer0_enable_interrupt(){
	#if GLOBAL_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	ENABLE_GLOBAL_INTERRUPT();
	#if TIMER0_OVERFLOW_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	TIMER0_OVF_ENABLE_INTERRUPT();
	#endif
	#if TIMER0_OCM_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	TIMER0_OC_ENABLE_INTERRUPT();
	#endif
	#endif
}