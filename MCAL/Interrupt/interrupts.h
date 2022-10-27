/*
 * interrupts.h
 *
 * Created: 9/4/2022 2:01:54 PM
 *  Author: ADEL
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../Utilities/registers.h"
#include "Interrupt_gen_config.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

/*******************************     Interrupts' Vectors    *********************************/
// external Interrupt Request 0
#define EXT_INT_0_VECTOR        __vector_1
// external Interrupt Request 1
#define EXT_INT_1_VECTOR        __vector_2
// external Interrupt Request 2
#define EXT_INT_2_VECTOR        __vector_3


// Timer0 Compare match Interrupt Request vector
#define TIMER0_COMP_VECTOR      __vector_10
// Timer0 overflow Interrupt Request vector
#define TIMER0_OVERFLOW_VECTOR  __vector_11

// ADC Interrupt Request when Conversion is complete
#define ADC_INT_REQ_VECTOR      __vector_16


// UART Interrupt request when the Receiving process is completed
#define UART_RX_COMPLETE_VECTOR __vector_13
// UART Interrupt request when the UDR Register is empty
#define UART_UDRE_VECTOR        __vector_14
// UART Interrupt request when the Transmitting process is completed
#define UART_TX_COMPLETE_VECTOR __vector_15

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************    Interrupt Handler Declaration and Definition    ********************/
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

// Enable global interrupt bit in the Status Register SREG
#define ENABLE_GLOBAL_INTERRUPT()  (SREGbits.I = 1)
// Disable global interrupt bit in the Status Register SREG
#define DISABLE_GLOBAL_INTERRUPT()  (SREGbits.I = 1)

#endif /* INTERRUPTS_H_ */