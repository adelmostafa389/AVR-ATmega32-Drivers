/*
 * registers.h
 *
 * Created: 8/29/2022 9:36:13 AM
 *  Author: ADEL
 */ 

/***********************************************************************************/
/*                          All Microcontroller registers                          */
/***********************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "types.h"

// STATUS register  
#define SREG *((volatile uint8_t*) 0x5F) //8-bit register
typedef union { // STATUS 8-bit Register bits
	struct {
		unsigned C             :1;
		unsigned Z             :1;
		unsigned N             :1;
		unsigned V             :1;
		unsigned S             :1;
		unsigned H             :1;
		unsigned T             :1;
		unsigned I             :1;
	};
} SREGbits_t;
#define SREGbits (*(volatile SREGbits_t*)(0x5F))

/***********************************************************************************/
/*                            External Interrupt registers                         */
/***********************************************************************************/
// MCU MicroController Control Register
#define MCUCR *((volatile uint8_t*) 0x55) //8-bit register
typedef union { // MCUCR 8-bit MCU Control Register bits
	struct {
		unsigned ISC00         :1;
		unsigned ICS01         :1;
		unsigned ISC10         :1;
		unsigned ICS11         :1;
		unsigned SM0           :1;
		unsigned SM1           :1;
		unsigned SM2           :1;
		unsigned SE            :1;
	};
	struct {
		unsigned ISC0          :2;
		unsigned ISC1          :2;
		unsigned SM            :3;
		unsigned               :1;
	};
} MCUCRbits_t;
#define MCUCRbits (*(volatile MCUCRbits_t*)(0x55))

// MCU MicroController Control and Status Register
#define MCUCSR *((volatile uint8_t*) 0x54) //8-bit register
typedef union { // MCUCSR 8-bit MCU Control and Status Register bits
	struct {
		unsigned PORF          :1;
		unsigned EXTRF         :1;
		unsigned BORF          :1;
		unsigned WDRF          :1;
		unsigned JTRF          :1;
		unsigned               :1;
		unsigned ISC2          :1;
		unsigned JTD           :1;
	};
} MCUCSRbits_t;
#define MCUCSRbits (*(volatile MCUCSRbits_t*)(0x54))


// GICR General Interrupt Control Register
#define GICR *((volatile uint8_t*) 0x5B) //8-bit register
typedef union { // GICR 8-bit General Interrupt Control Register bits
	struct {
		unsigned IVCE          :1;
		unsigned IVSEL         :1;
		unsigned               :3;
		unsigned INT2          :1;
		unsigned INT0          :1;
		unsigned INT1          :1;
	};
} GICRbits_t;
#define GICRbits (*(volatile GICRbits_t*)(0x5B))

// GIFR General Interrupt Flag Register
#define GIFR *((volatile uint8_t*) 0x5A) //8-bit register
typedef union { // GIFR 8-bit General Interrupt Control Register bits
	struct {
		unsigned               :5;
		unsigned INTF2         :1;
		unsigned INTF0         :1;
		unsigned INTF1         :1;
	};
} GIFRbits_t;
#define GIFRbits (*(volatile GIFRbits_t*)(0x5A))


/***********************************************************************************/
/*                                  ADC registers                               */
/***********************************************************************************/

#define ADC_H *((volatile uint8_t*) 0x25) //8-bit register
#define ADC_L *((volatile uint8_t*) 0x24) //8-bit register

// ADMUX ADC  Multiplexer Selection Register
#define ADMUX *((volatile uint8_t*) 0x27) //8-bit register
typedef union { // ADMUSX ADC  Multiplexer Selection Register bits
	struct {
		unsigned MUX0           :1;
		unsigned MUX1           :1;
		unsigned MUX2           :1;
		unsigned MUX3           :1;
		unsigned MUX4           :1;
		unsigned ADLAR          :1;
		unsigned REFS0          :1;
		unsigned REFS1          :1;
	};
	struct {
		unsigned MUX            :5;
		unsigned                :1;
		unsigned REFS           :2;
	};
} ADMUXbits_t;
#define ADMUXbits (*(volatile ADMUXbits_t*)(0x27))


// ADCSRA ADC Control and Status Register
#define ADCSRA *((volatile uint8_t*) 0x26) //8-bit register
typedef union { // ADCSRA ADC Control and Status Register bits
	struct {
		unsigned ADPS0          :1;
		unsigned ADPS1          :1;
		unsigned ADPS2          :1;
		unsigned ADIE           :1;
		unsigned ADIF           :1;
		unsigned ADATE          :1;
		unsigned ADSC           :1;
		unsigned ADEN           :1;
	};
	struct {
		unsigned ADPS           :3;
		unsigned                :5;
	};
} ADCSRAbits_t;
#define ADCSRAbits (*(volatile ADCSRAbits_t*)(0x26))

// SFIOR Special FunctionIO Register
#define SFIOR *((volatile uint8_t*) 0x50) //8-bit register
typedef union { // SFIOR Special FunctionIO Register bits
	struct {
		unsigned PSR10          :1;
		unsigned PSR2           :1;
		unsigned PUD            :1;
		unsigned ACME           :1;
		unsigned                :1;
		unsigned ADTS0          :1;
		unsigned ADTS1          :1;
		unsigned ADTS2          :1;
};
	struct {
		unsigned                :5;
		unsigned ADTS           :3;
	};
} SFIORbits_t;
#define SFIORbits (*(volatile SFIORbits_t*)(0x50))

/***********************************************************************************/
/*                                   DIO registers                                 */
/***********************************************************************************/

/********************  PORTA registers  ********************/
#define PORTA *((volatile uint8_t*) 0x3B) //8-bit register
#define DDRA *((volatile uint8_t*) 0x3A)  //8-bit register
#define PINA *((volatile uint8_t*) 0x39)  //8-bit register

/********************  PORTB registers  ********************/
#define PORTB *((volatile uint8_t*) 0x38) //8-bit register
#define DDRB *((volatile uint8_t*) 0x37)  //8-bit register
#define PINB *((volatile uint8_t*) 0x36)  //8-bit register

/********************  PORTC registers  ********************/
#define PORTC *((volatile uint8_t*) 0x35) //8-bit register
#define DDRC *((volatile uint8_t*) 0x34)  //8-bit register
#define PINC *((volatile uint8_t*) 0x33)  //8-bit register

/********************  PORTD registers  ********************/
#define PORTD *((volatile uint8_t*) 0x32) //8-bit register
#define DDRD *((volatile uint8_t*) 0x31)  //8-bit register
#define PIND *((volatile uint8_t*) 0x30)  //8-bit register

/***********************************************************************************/
/*                                  Timers registers                               */
/***********************************************************************************/

// Timer/Counter Interrupt Mask Register
#define TIMSK *((volatile uint8_t*) 0x59) //8-bit register
typedef union { // TIMSK 8-bit Timer/Counter Interrupt Mask Register bits
	struct {
		unsigned TOIE0         :1;
		unsigned OCIE0         :1;
		unsigned TOIE1         :1;
		unsigned OCIE1B        :1;
		unsigned OCIE1A        :1;
		unsigned TICIE1        :1;
		unsigned TOIE2         :1;
		unsigned OCIE2         :1;
	};
} TIMSKbits_t;
#define TIMSKbits (*(volatile TIMSKbits_t*)(0x59))

// Timer/Counter Interrupt Flag Register
#define TIFR *((volatile uint8_t*) 0x58)  // TIFR 8-bit Timer/Counter Interrupt Flag Register
typedef union { // TIFR 8-bit Timer/Counter0 Interrupt Flag Register bits
	struct {
		unsigned TOV0          :1;
		unsigned OCF0          :1;
		unsigned TOV1          :1;
		unsigned OCF1B         :1;
		unsigned OCF1A         :1;
		unsigned ICF1          :1;
		unsigned TOV2          :1;
		unsigned OCF2          :1;
	};
} TIFRbits_t;
#define TIFRbits (*(volatile TIFRbits_t*)(0x58))

/********************  TIMER0 registers  ********************/
#define OCR0 *((volatile uint8_t*) 0x5C)  // OCR0 8-bit Output Compare Register
#define TCNT0 *((volatile uint8_t*) 0x52) // TCNT0 8-bit Timer/Counter0 Register
#define TCCR0 *((volatile uint8_t*) 0x53) //TCCR0 8-bit Timer/Counter0 Control Register
typedef union { // TCCR0 8-bit Timer/Counter0 Control Register bits
	struct {
		unsigned CS00          :1;
		unsigned CS01          :1;
		unsigned CS02          :1;
		unsigned WGM01         :1;
		unsigned COM00         :1;
		unsigned COM01         :1;
		unsigned WGM00         :1;
		unsigned FOC0          :1;
	};
	struct {
		unsigned CS0           :3;
		unsigned               :1;
		unsigned COM0          :2;
		unsigned               :2;
	};
} TCCR0bits_t;
#define TCCR0bits (*(volatile TCCR0bits_t*)(0x53))

/***********************************************************************************/
/*                                   UART registers                                */
/***********************************************************************************/

// UART I/O Data Register( Transmit Data Buffer and Receive Data Buffer)
#define UDR *((volatile uint8_t*) 0x2C) //8-bit register

// UART Control and Status Register A
#define UCSRA *((volatile uint8_t*) 0x2B) //8-bit register
typedef union { // UART Control and Status Register A bits
	struct {
		unsigned MPCM          :1;
		unsigned U2X           :1;
		unsigned PE            :1;
		unsigned DOR           :1;
		unsigned FE            :1;
		unsigned UDRE          :1;
		unsigned TXC           :1;
		unsigned RXC           :1;
	};
} UCSRAbits_t;
#define UCSRAbits (*(volatile UCSRAbits_t*)(0x2B))

// UART Control and Status Register B
#define UCSRB *((volatile uint8_t*) 0x2A) //8-bit register
typedef union { // UART Control and Status Register B bits
	struct {
		unsigned TXB8          :1;
		unsigned RXB8          :1;
		unsigned UCSZ2         :1;
		unsigned TXEN          :1;
		unsigned RXEN          :1;
		unsigned UDRIE         :1;
		unsigned TXCIE         :1;
		unsigned RXCIE         :1;
	};
} UCSRBbits_t;
#define UCSRBbits (*(volatile UCSRBbits_t*)(0x2A))

// UART Control and Status Register C shares the same I/O location as the UCSRC Register
#define UCSRC *((volatile uint8_t*) 0x40) //8-bit register
typedef union { // UART Control and Status Register C bits
	struct {
		unsigned UCPOL         :1;
		unsigned UCSZ0         :1;
		unsigned UCSZ1         :1;
		unsigned USBS          :1;
		unsigned UPM0          :1;
		unsigned UPM1          :1;
		unsigned UMSEL         :1;
		unsigned URSEL         :1;
	};
} UCSRCbits_t;
#define UCSRCbits (*(volatile UCSRCbits_t*)(0x40))

// UART Baud Rate Register shares the same I/O location as the UCSRC Register
#define UBRRH *((volatile uint8_t*) 0x40) //8-bit register

// UART Baud Rate Register
#define UBRRL *((volatile uint8_t*) 0x29) //8-bit register

#endif /* REGISTERS_H_ */