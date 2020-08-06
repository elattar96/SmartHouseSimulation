/*
 * ADC_int.h
 *
 * Created: 25-Jul-20 2:15:14 PM
 *  Author: Mohamed Elattar
 */ 

#include "std_types.h"

#ifndef _ADC_INT_H
#define _ADC_INT_H




void ADC_voidInitialize(void);
void ADC_voidEnable(void);
void ADC_voidDisable(void);
void ADC_voidStartConv (void);
void ADC_voidIntEnable(void);
void ADC_voidIntDisable(void);
void ADC_voidSetCallBack(void (*Copy_ptr) (void));
uint8 ADC_u8GetResult(uint8 channel);
uint16 ADC_u16GetResult(uint16 channel);




#endif