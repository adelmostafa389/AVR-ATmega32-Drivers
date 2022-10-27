/*
 * types.h
 *
 * Created: 8/29/2022 10:12:48 AM
 *  Author: ADEL
 */ 

#ifndef MCAL_STD_TYPES_H_H
#define	MCAL_STD_TYPES_H_H

/********************************************************************************************/
/*                                         Includes                                         */
/********************************************************************************************/
#include <stdio.h>

/********************************************************************************************/
/*                                    Macros Declarations                                   */
/********************************************************************************************/
#define ZERO_INIT       0x00

/********************************************************************************************/
/*                                Macro Functions Declarations                              */
/********************************************************************************************/

/********************************************************************************************/
/*                                  Data Type Declarations                                  */
/********************************************************************************************/
typedef unsigned char uint8_t;
//typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef signed char sint8_t;
typedef signed short sint16_t;
typedef signed long sint32_t;

typedef void(*PtrTo_func_t)(void);

typedef enum{
	OK,
	NOT_OK,
	NULL_POINTER	
}En_Std_ReturnType_t;

typedef union{
    struct{
        uint8_t LSbits8;
        uint8_t MSbits8;
    };
    struct{
        uint16_t REG16;
    };
}Un_16bits_register_t;

/********************************************************************************************/
/*                             Software Interface Declarations "APIs"                       */
/********************************************************************************************/

#endif	/* MCAL_STD_TYPES_H_H */

