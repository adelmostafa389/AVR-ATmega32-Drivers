/*
 * timer0.h
 *
 * Created: 9/3/2022 12:22:24 PM
 *  Author: ADEL
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../MCAL/DIO/dio.h"
#include "../Interrupt/interrupts.h"

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/
// Set timer clock source
#define TIMER0_SET_CLK_SRC(CLK_SRC)     (TCCR0bits.CS0 = CLK_SRC)
// Clear overflow flag in timer0
#define TIMER0_CLEAR_OVF_FLAG()         (TIFRbits.TOV0 = 1)
// Clear output compare flag in timer0
#define TIMER0_CLEAR_OC_FLAG()          (TIFRbits.OCF0 = 1)
// Check if the overflow flag is set
#define TIMER0_IS_OVF_FLAG_SET()        (TIFRbits.TOV0)
// Check if the output compare flag is set
#define TIMER0_IS_OC_FLAG_SET()         (TIFRbits.OCF0)
// Enable Timer0 On Compare Interrupt
#define TIMER0_OC_ENABLE_INTERRUPT()    (TIMSKbits.OCIE0 = 1)
// Disable Timer0 On Compare Interrupt
#define TIMER0_OC_DIABLE_INTERRUPT()    (TIMSKbits.OCIE0 = 0)
// Enable Timer0 Over Flow Interrupt
#define TIMER0_OVF_ENABLE_INTERRUPT()   (TIMSKbits.TOIE0 = 1)
// Disable Timer0 Over Flow Interrupt
#define TIMER0_OVF_DIABLE_INTERRUPT()   (TIMSKbits.TOIE0 = 0)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	TIEMR0_OK,
	TIMER0_NULL_POINTER,
	TIMER0_WRONG_CLOCK_SOURCE,
	TIMER0_WRONG_MODE,
	TIMER0_WRONG_CO_MODE,
	TIMER0_WRONG_PRELOAD_VALUE,
	TIMER0_WRONG_PWM_DUTY_CYCLE
}En_Timer0_Error_t;

typedef enum{
	T0_NO_CLOCK_SOURCE = 0,
	T0_CLK_DIV_BY_1,
	T0_CLK_DIV_BY_8,
	T0_CLK_DIV_BY_64,
	T0_CLK_DIV_BY_256,
	T0_CLK_DIV_BY_1024,
	T0_EXTERNAL_CLK_FALLING,
	T0_EXTERNAL_CLK_RISING,
	T0_NUM_OF_CLK_SCR_OPTIONS
}en_T0ClockSource_t;

typedef enum{
	T0_NORMAL_MODE = 0,
	T0_PHASE_CORRECT_PWM_MODE,
	T0_CTC_MODE,
	T0_FAST_PWM_MODE,
	NUM_OF_TIMER0_MODES
}en_T0Mode_t;

typedef enum{
	OC0_nonPWM_DISCONNECTED = 0,
	OC0_nonPWM_TOGGLE,
	OC0_nonPWM_CLEAR,
	OC0_nonPWM_SET,
	NUM_OF_OC0_NONPWM_MODES
}en_T0_CO_nonPWM_mode_t;

typedef enum{
	OC0_FAST_PWM_DISCONNECTED = 0,
	OC0_FAST_PWM_RESERVED,
	OC0_FAST_PWM_CLEAR,
	OC0_FAST_PWM_SET,
	NUM_OF_OC0_FAST_PWM_MODES
}en_T0_CO_FAST_PWM_mode_t;

typedef enum{
	OC0_CORRECT_PWM_DISCONNECTED = 0,
	OC0_CORRECT_PWM_RESERVED,
	OC0_CORRECT_PWM_CLEAR,
	OC0_CORRECT_PWM_SET,
	NUM_OF_OC0_CORRECT_PWM_MODES
}en_T0_CO_CORRECT_PWM_mode_t;

typedef struct  {
	en_T0Mode_t mode;
	en_T0ClockSource_t clockSource;
	en_T0_CO_nonPWM_mode_t compareModeNonPWM;
	en_T0_CO_FAST_PWM_mode_t compareModeFastPWM;
	en_T0_CO_CORRECT_PWM_mode_t compareModeCorrectPWM;
	uint8_t preloadValue;
	uint8_t preload_pwmDC;
}st_timer0_config_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * @brief This function initializes timer0 configuration
 * 
 * @param timer0_cfg 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_init(st_timer0_config_t* timer0_cfg);

/**
 * @brief This function stops the the timer0 to count by clearing the clock source bits
 * 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_stop(void);

/**
 * @brief This function resume timer0 countinting by setting the clock source back if timer0_stop() was called before 
 * 
 * @param timer0_cfg 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_start(st_timer0_config_t* timer0_cfg);

/**
 * @brief This function write value to Timer0 register TCNT0
 * 
 * @param value 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_write(st_timer0_config_t* timer0_cfg, uint8_t value);

/**
 * @brief This function reads the value at the Timer0 register TCNT0
 * 
 * @param value 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_read(st_timer0_config_t* timer0_cfg, uint8_t*  value);

/**
 * @brief This function set the PWM Duty Cycle of timer0 in the PWM modes
 * 
 * @param timer0_cfg 
 * @param dutyCycle 
 * @return En_Timer0_Error_t 
 */
En_Timer0_Error_t timer0_pwm_set_DC(st_timer0_config_t* timer0_cfg, uint8_t dutyCycle);


#endif /* TIMER0_H_ */