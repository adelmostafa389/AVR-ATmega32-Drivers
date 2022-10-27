/*
 * EXTI.h
 *
 * Created: 9/4/2022 2:00:08 PM
 *  Author: ADEL
 */ 


#ifndef EXTI_H_
#define EXTI_H_

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../Utilities/registers.h"
#include "../DIO/dio.h"
#include "interrupts.h"

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

// Configure external interrupt 0 sense control
#define INT0_SENSE_LOW_LEVEL()     (MCUCRbits.ISC0 = 0x00)
#define INT0_SENSE_LOGIC_CHANGE()  (MCUCRbits.ISC0 = 0x01)
#define INT0_SENSE_FALLING_EDGE()  (MCUCRbits.ISC0 = 0x02)
#define INT0_SENSE_RISING_EDGE()   (MCUCRbits.ISC0 = 0x03)
#define INT0_ENABLE_INTERRUPT()    (GICRbits.INT0 = 1)
#define INT0_DISABLE_INTERRUPT()   (GICRbits.INT0 = 0)
#define INT0_CLEAR_FLAG()          (GIFRbits.INTF0)

// Configure external interrupt 1 sense control
#define INT1_SENSE_LOW_LEVEL()     (MCUCRbits.ISC1 = 0x00)
#define INT1_SENSE_LOGIC_CHANGE()  (MCUCRbits.ISC1 = 0x01)
#define INT1_SENSE_FALLING_EDGE()  (MCUCRbits.ISC1 = 0x02)
#define INT1_SENSE_RISING_EDGE()   (MCUCRbits.ISC1 = 0x03)
#define INT1_ENABLE_INTERRUPT()    (GICRbits.INT1 = 1)
#define INT1_DISABLE_INTERRUPT()   (GICRbits.INT1 = 0)
#define INT1_CLEAR_FLAG()          (GIFRbits.INTF1)

// Configure external interrupt 2 sense control
#define INT2_SENSE_FALLING_EDGE()  (MCUCSRbits.ISC2 = 0x00)
#define INT2_SENSE_RISING_EDGE()   (MCUCSRbits.ISC2 = 0x01)
#define INT2_ENABLE_INTERRUPT()    (GICRbits.INT2 = 1)
#define INT2_DISABLE_INTERRUPT()   (GICRbits.INT2 = 0)
#define INT2_CLEAR_FLAG()          (GIFRbits.INTF2)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	INTx_OK,
	INTx_NULL_POINTER,
	INTx_WRONG_SOURCE,
	INTx_WRONG_EDGE
}En_INTx_Error_t;

typedef enum{
	INTI_FALLING_EDGE = 0,
	INTI_RISING_EDGE,
	INTI_LOW_LEVEL,
	INTI_LOGIC_CHANGE
}En_interrupt_INTx_edge;

typedef enum{
	INT0_INTERRUPT_EXTERNAL = 0,
	INT1_INTERRUPT_EXTERNAL,
	INT2_INTERRUPT_EXTERNAL
}En_interrupt_INTx_src;

typedef struct{
	En_interrupt_INTx_edge edge;
	En_interrupt_INTx_src source;
}St_interrupt_INTx_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

/**
 * @brief This function Initializes the external interrupt with the configurations passed through the pointer int_cfg
 * 
 * @param int_cfg 
 * @return En_INTx_Error_t 
 */
En_INTx_Error_t init_external_INTx(const St_interrupt_INTx_t *int_cfg);

/**
 * @brief this function De initializes the external interrupt
 * 
 * @param int_cfg 
 * @return En_INTx_Error_t 
 */
En_INTx_Error_t deinit_external_INTx(const St_interrupt_INTx_t *int_cfg);

#endif /* EXTI_H_ */