/*
 * ADC_reg.h
 *
 * Created: 25-Jul-20 2:19:01 PM
 *  Author: Mohamed Elattar
 */ 


#ifndef _ADC_REG_H
#define _ADC_REG_H


#define ADMUX   	*((volatile uint8*)0x27)
#define ADCSRA		*((volatile uint8*)0x26)
#define ADCH		*((volatile uint8*)0x25
#define ADCL		*((volatile uint8*)0x24)
#define ADCDATA 	*((volatile uint16*)0x24)
#define SFIOR		*((volatile uint8*)0x50)



#endif