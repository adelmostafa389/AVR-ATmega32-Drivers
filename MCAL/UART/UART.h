/*
 * UART.h
 *
 * Created: 9/25/2022 4:10:29 AM
 *  Author: ADEL
 */ 


#ifndef UART_H_
#define UART_H_


/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../DIO/dio.h"
#include "../Interrupt/interrupts.h"

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

// select to write to UBRRH register(0 to bit URSEL register UCSRC)
#define UART_WRITE_TO_UBRRH_REG()            (UCSRCbits.URSEL = 0)
// select to write to UCSRC register(1 to bit URSEL register UCSRC)
#define UART_WRITE_TO_UCSRC_REG()            (UCSRCbits.URSEL = 1)
// select Asynchronous operation mode( 0 to bit UMSEL register UCSRC)
#define UART_SELECT_ASYNCH_MODE()            (UCSRCbits.UMSEL = 0)
// enable Even Parity Mode (0 to UPM0 and 1 to UPM1 register UCSRC)
#define UART_ENABLE_EVEN_PARITY()             UCSRCbits.UPM0 = 0;\
                                              UCSRCbits.UPM1 = 0
// set the USART transmission to normal speed(0 to bit U2X register UCSRA)
#define UART_SELECT_NORMAL_TRANS_SPEED()     (UCSRAbits.U2X = 0)
// disable multi processor communication mode(0 to bit MPCM register UCSRA)
#define UART_DISABLE_MULTIPROCESSOR_MODE()   (UCSRAbits.MPCM = 0)
// set character size to 8 bits(1 to both bits UCSZ1:2 in register UCSRC)and(0 to bit UCSZ2 register UCSRB)
#define UART_SET_CHAR_SIZE_TO_8BITS()         UCSRCbits.UCSZ0 = 1;\
                                              UCSRCbits.UCSZ1 = 1;\
                                              UCSRBbits.UCSZ2 = 0
// set stop bit size to one bit(0 to bit USBS register UCSRC)
#define UART_SET_STOP_BIT_SIZE_TO_ONE_BYTE() (UCSRCbits.USBS = 0)
// enable receiver (bit RXEN register UCSRB)
#define UART_ENABLE_RECEIVER()               (UCSRBbits.RXEN = 1)
// Disable receiver (bit RXEN register UCSRB)
#define UART_DISABLE_RECEIVER()               (UCSRBbits.RXEN = 0)
// enable transmit (bit TXEN register UCSRB)
#define UART_ENABLE_TRANSMIT()               (UCSRBbits.TXEN = 1)
// Disable transmit (bit TXEN register UCSRB)
#define UART_DISABLE_TRANSMIT()               (UCSRBbits.TXEN = 0)

// enable UART Interrupt on Receiving complete
#define UART_ENABLE_RXC_INTERRUPT()          (UCSRBbits.RXCIE = 1)
// disable UART Interrupt on Receiving complete
#define UART_DISABLE_RXC_INTERRUPT()          (UCSRBbits.RXCIE = 0)
// enable UART Interrupt on Transmitting complete
#define UART_ENABLE_TXC_INTERRUPT()          (UCSRBbits.TXCIE = 1)
// disable UART Interrupt on Transmitting complete
#define UART_DISABLE_TXC_INTERRUPT()          (UCSRBbits.TXCIE = 0)
// enable UART Interrupt when UDR register is empty
#define UART_ENABLE_UDR_EMPTY_INTERRUPT()    (UCSRBbits.UDRIE = 1)
// disable UART Interrupt when UDR register is empty
#define UART_DISABLE_UDR_EMPTY_INTERRUPT()    (UCSRBbits.UDRIE = 0)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	UART_OK,
	UART_NULL_POINTER,
}En_UART_Error_t;

typedef struct{	
	
#if UART_RXC_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	PtrTo_func_t RXC_DefaultInterruptHandler;
#endif
#if UART_TXC_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	PtrTo_func_t TXC_DefaultInterruptHandler;
#endif
#if UART_UDRE_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	PtrTo_func_t UDRE_DefaultInterruptHandler;
#endif
	uint16_t buadrate;
}St_UART_config_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

En_UART_Error_t UART_ASYNC_Init(St_UART_config_t* uart_cfg);
En_UART_Error_t UART_ASYNC_DeInit(void);

En_UART_Error_t UART_ASYNC_ReadByteBlocking(uint8_t* data);
En_UART_Error_t UART_ASYNC_ReadByteNonBlocking(uint8_t* data);

En_UART_Error_t UART_ASYNC_WriteByteBlocking(uint8_t data);
En_UART_Error_t UART_ASYNC_WriteStringBlocking(uint8_t* data, uint8_t str_len);
En_UART_Error_t UART_ASYNC_WriteByteNonBlocking(uint8_t data);
En_UART_Error_t UART_ASYNC_WriteStringNonBlocking(uint8_t* data, uint8_t str_len);



#endif /* UART_H_ */