/*
 * ADC.h
 *
 * Created: 9/7/2022 2:22:16 PM
 *  Author: ADEL
 */ 


#ifndef ADC_H_
#define ADC_H_

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include "../../Utilities/types.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/bit_manipulation.h"
#include "../Interrupt/interrupts.h"
#include "../DIO/dio.h"

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/

#define ADC_STEP (float)5/1024.0

#define ADC_RESULT_RIGHT_ADJUST   0
#define ADC_RESULT_LEFT_ADJUST    1

#define ADC_RESULT_ADJUSTMENT    ADC_RESULT_RIGHT_ADJUST

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/
// Enable ADC Peripheral
#define ADC_ENABLE()             (ADCSRAbits.ADEN = 1)
// Disable ADC Peripheral
#define ADC_DISABLE()            (ADCSRAbits.ADEN = 0)
// Start Analog to Digital Conversion
#define ADC_START()              (ADCSRAbits.ADSC = 1)
// Enable ADC Auto trigger
#define ADC_ENABLE_AUTO_TRIG()   (ADCSRAbits.ADATE = 1)
// Disable ADC Auto trigger
#define ADC_DISABLE_AUTO_TRIG()  (ADCSRAbits.ADATE = 0)
// Adjust ADC conversion result to the right ADCH| -- -- -- -- -- -- R9 R8    ADHL| R7 R6 R5 R4 R3 R2 R1 R0
// Adjust ADC conversion result to the left  ADCH| R9 R8 R7 R6 R5 R4 R3 R2    ADHL| R1 R0 -- -- -- -- -- --
#define ADC_ADJUST_RESUTLT()     (ADMUXbits.ADLAR = ADC_RESULT_ADJUSTMENT)
// Check if the ADC Flag is set
#define ADC_IS_FLAG_SET()        (ADCSRAbits.ADIF)
// Clear the ADC Flag
#define ADC_CLEAR_FLAG()         (ADCSRAbits.ADIF = 1)
// Enable ADC Interrupt
#define ADC_ENABLE_INTERRUPT()   (ADCSRAbits.ADIE = 1)
// Disable ADC Interrupt
#define ADC_DIABLE_INTERRUPT()   (ADCSRAbits.ADIE = 0)

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/

typedef enum{
	ADC_AREF = 0,
	ADC_AVCC,
	ADC_reserved,
	ADC_INTERNAL_VREF
}en_adc_ref_t;

typedef enum{
	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
}en_adc_channel_t;

typedef enum{
	ADC_CLK_DIV_BY_2 = 0,
	ADC_CLK_DIV_BY_4 = 2,
	ADC_CLK_DIV_BY_8,
	ADC_CLK_DIV_BY_16,
	ADC_CLK_DIV_BY_32,
	ADC_CLK_DIV_BY_64,
	ADC_CLK_DIV_BY_128,
}en_adc_freq_prescale_t;

typedef struct  {
	en_adc_ref_t adc_reference;
	en_adc_channel_t channel;
	en_adc_freq_prescale_t prescaler;
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
	PtrTo_func_t interruptHandler;
#endif
}st_adc_config_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

En_Std_ReturnType_t init_ADC(const st_adc_config_t* adc_cfg);
En_Std_ReturnType_t start_ADC(const st_adc_config_t* adc_cfg, float* result);

#endif /* ADC_H_ */