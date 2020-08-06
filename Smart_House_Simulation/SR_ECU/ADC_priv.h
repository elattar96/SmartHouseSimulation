/*
 * ADC_priv.h
 *
 * Created: 25-Jul-20 2:16:50 PM
 *  Author: Mohamed Elattar
 */ 

#ifndef _ADC_PRIV_H
#define _ADC_PRIV_H

// Resolution  selection options
#define EIGHT_BIT 	24
#define TEN_BIT		7

// Vref  selection options
#define  INTERNAL_VCC		5
#define	 EXTERNAL_AVCC		10
#define  INTERNAL_2		15

// mode selection options
#define	 SINGLE_CONVERSION_MODE				55
#define  FREE_RUNNING_MODE					1
#define  TRIGGER_WITH_ANALOG_COMPARATOR		2
#define  TRIGGER_WITH_EXTI0					3
#define  TRIGGER_WITH_TIM0_COMP				4
#define  TRIGGER_WITH_TIM0_OV				5
#define  TRIGGER_WITH_TIM_COM_B				6
#define  TRIGGER_WITH_TIM1_OV				7
#define  TRIGGER_WITH_TIM_CAPTURE			8

// Prescaler selection options
#define	PRESCALER_2			1
#define	PRESCALER_4			2
#define	PRESCALER_8			3
#define	PRESCALER_16		4
#define	PRESCALER_32		5
#define	PRESCALER_64		6
#define	PRESCALER_128		7



#endif
