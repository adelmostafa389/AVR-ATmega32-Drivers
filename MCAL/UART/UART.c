/*
 * UART.c
 *
 * Created: 9/25/2022 4:10:15 AM
 *  Author: ADEL
 */ 

#include "UART.h"

volatile uint8_t* UART_receivedVal = 0;

static void UART_setBaudRate(uint16_t baudrate);
static void UART_setInterrupt(St_UART_config_t* uart_cfg);

static PtrTo_func_t l_RXC_DefaultInterruptHandler;
static PtrTo_func_t l_TXC_DefaultInterruptHandler;
static PtrTo_func_t l_UDRE_DefaultInterruptHandler;

En_UART_Error_t UART_ASYNC_Init(St_UART_config_t* uart_cfg){
	En_UART_Error_t retVal= UART_OK;
	if(NULL == uart_cfg){
		retVal = UART_NULL_POINTER;
	}
	else{
		UART_setBaudRate(uart_cfg->buadrate);
		// select to write to UCSRC register(1 to bit URSEL register UCSRC)
		UART_WRITE_TO_UCSRC_REG();
		// select Asynchronous operation mode( 0 to bit UMSEL register UCSRC)
		UART_SELECT_ASYNCH_MODE();
		// enable Even Parity Mode (0 to UPM0 and 1 to UPM1 register UCSRC)
		UART_ENABLE_EVEN_PARITY();
		// select the USART transmission to normal speed(0 to bit U2X register UCSRA)
		UART_SELECT_NORMAL_TRANS_SPEED();
		// disable multi processor communication mode(0 to bit MPCM register UCSRA)
		UART_DISABLE_MULTIPROCESSOR_MODE();
		// set character size to 8 bits(1 to both bits UCSZ1, UCSZ2 in register UCSRC)and(0 to bit UCSZ2 register UCSRB)
		UART_SET_CHAR_SIZE_TO_8BITS();
		// set stop bit size to one bit(0 to bit USBS register UCSRC)
		UART_SET_STOP_BIT_SIZE_TO_ONE_BYTE();
		// enable receiver (bit RXEN register UCSRB)
		UART_ENABLE_RECEIVER();
		// enable transmit (bit TXEN register UCSRB)
		UART_ENABLE_TRANSMIT();
		// enable UART interrupts
		UART_setInterrupt(uart_cfg);
	}
	return retVal;
}

En_UART_Error_t UART_ASYNC_DeInit(void){
	UART_DISABLE_RECEIVER();
	UART_DISABLE_TRANSMIT();
	UART_DISABLE_TXC_INTERRUPT();
	UART_DISABLE_RXC_INTERRUPT();
	UART_DISABLE_UDR_EMPTY_INTERRUPT();
	return UART_OK;
}

En_UART_Error_t UART_ASYNC_ReadByteBlocking(uint8_t* data){
	En_UART_Error_t retVal = UART_OK;
	if(NULL == data){
		retVal = UART_NULL_POINTER;
	}
	else{
		while(!UCSRAbits.RXC);
		*data = UDR;
	}
	return retVal;
}

En_UART_Error_t UART_ASYNC_ReadByteNonBlocking(uint8_t* data){
	En_UART_Error_t retVal = UART_OK;
	if(NULL == data){
		retVal = UART_NULL_POINTER;
	}
	else{
		UART_receivedVal = data;
	}
	return retVal;
}

En_UART_Error_t UART_ASYNC_WriteByteBlocking(uint8_t data){
	while(!UCSRAbits.UDRE);
	UDR = data;
	return UART_OK;
}
En_UART_Error_t UART_ASYNC_WriteStringBlocking(uint8_t* data, uint8_t str_len){
	En_UART_Error_t retVal = UART_OK;
	uint8_t counter = 0;
	if(NULL == data){
		retVal = UART_NULL_POINTER;
	}
	else{
		for(counter = 0; counter<str_len; counter++){
			UART_ASYNC_WriteByteBlocking(data[counter]);
		}
	}
	return retVal;
}

En_UART_Error_t UART_ASYNC_WriteByteNonBlocking(uint8_t data){
	return UART_NULL_POINTER;
}

En_UART_Error_t UART_ASYNC_WriteStringNonBlocking(uint8_t* data, uint8_t str_len){
	En_UART_Error_t retVal = UART_OK;
	uint8_t counter = 0;
	if(NULL == data){
		retVal = UART_NULL_POINTER;
	}
	else{
		for(counter = 0; counter<str_len; counter++){
			UART_ASYNC_WriteByteNonBlocking(data[counter]);
		}
	}
	return retVal;
}


static void UART_setBaudRate(uint16_t baudrate){
	float UDR_value = 0;
	// select to write to UBRRH register(0 to bit URSEL register UCSRC)
	UART_WRITE_TO_UBRRH_REG();
	// set the Baud Rate with frequency 8MHz and with normal speed (UBRR = (8000000/(16*baudrate))-1 )
	UDR_value = (8000000/(16*(float)baudrate))-1;
	UBRRL = (uint8_t)(uint32_t)(UDR_value);
	UBRRH = ((uint32_t)(UDR_value)) >> 8;
}

static void UART_setInterrupt(St_UART_config_t* uart_cfg){
#if GLOBAL_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    ENABLE_GLOBAL_INTERRUPT();
	#if UART_RXC_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	//enable UART Interrupt on Receiving complete
	UART_ENABLE_RXC_INTERRUPT();
	l_RXC_DefaultInterruptHandler = uart_cfg->RXC_DefaultInterruptHandler;
	#endif
	#if UART_TXC_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	// enable UART Interrupt on Transmitting complete
	UART_ENABLE_TXC_INTERRUPT();
	l_TXC_DefaultInterruptHandler = uart_cfg->TXC_DefaultInterruptHandler;
	#endif
	#if UART_UDRE_INTERRUPT_ENABLE == INTERRUPT_FEATURE_ENABLE
	// enable UART Interrupt when UDR register is empty
	UART_ENABLE_UDR_EMPTY_INTERRUPT();
	l_UDRE_DefaultInterruptHandler = uart_cfg->UDRE_DefaultInterruptHandler;
	#endif
#endif

}

ISR(UART_RX_COMPLETE_VECTOR){
	*UART_receivedVal = UDR;
	if(NULL == l_RXC_DefaultInterruptHandler){
		/* Nothing */
	}
	else{
		l_RXC_DefaultInterruptHandler();
	}
}
ISR(UART_TX_COMPLETE_VECTOR){
	if(NULL == l_TXC_DefaultInterruptHandler){
		/* Nothing */
	}
	else{
		l_TXC_DefaultInterruptHandler();
	}
}
ISR(UART_UDRE_VECTOR){
	if(NULL == l_UDRE_DefaultInterruptHandler){
		/* Nothing */
	}
	else{
		l_UDRE_DefaultInterruptHandler();
	}
}