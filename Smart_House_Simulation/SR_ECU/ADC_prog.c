/*
 * ADC_prog.c
 *
 * Created: 25-Jul-20 2:17:45 PM
 *  Author: Mohamed Elattar
 */ 

// zabat e AREF
// me7tag te7aded el channel
#include "ADC_reg.h"
#include "avr/io.h"
#include "ADC_priv.h"
#include "ADC_config.h"
#include "ADC_int.h"
#include "std_types.h"
#include "bitwise.h"

static void(*ADC_CallBack)(void);

void ADC_voidInitialize(void)

{
	//ADMUX |= ((1 << MUX1)) ;  //| (1 << MUX2) | (1 << MUX3) | (1 << MUX4));		//internal channel (1.22V)
	//	ADMUX |= ((1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));		//internal channel (1.22V)

	#if(REF_VOLTAGE == INTERNAL_VCC)

	ADMUX |= (1<<REFS0);

	#elif(REF_VOLTAGE == EXTERNAL_AVCC)
	// do nothing as it is default

	#elif(REF_VOLTAGE == INTERNAL_2)

	ADMUX |= ((1<<REFS0) | (1<<REFS1));

	#else

	#error "ADC >> wrong voltage reference selection"

	#endif
	
	
	
	#if(RESOLUTION == EIGHT_BIT)

	ADMUX |= 1<< ADLAR;  // LEFT Adjustment

	#elif(RESOLUTION == TEN_BIT)

	// do nothing as it is right adjustment by default

	#else

	#error "ADC >> wrong Resolution selection"

	#endif
	
	
	
	#if(MODE == SINGLE_CONVERSION_MODE)

	// do nothing (default)

	#elif (MODE == FREE_RUNNING_MODE)

	ADCSRA |= (1 << ADATE);
	// do no thing to SFIOR as it is the default source

	#elif (MODE == TRIGGER_WITH_ANALOG_COMPARATOR)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS0));
	
	#elif (MODE == TRIGGER_WITH_EXTI0)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS1));
	#elif (MODE == TRIGGER_WITH_TIM0_COMP)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS1) | (1 << ADTS0));

	#elif (MODE == TRIGGER_WITH_TIM0_OV)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS2));

	#elif (MODE == TRIGGER_WITH_TIM_COM_B)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS0) | (1 << ADTS2));

	#elif (MODE == TRIGGER_WITH_TIM1_OV)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS1) | (1 << ADTS2));

	#elif (MODE == TRIGGER_WITH_TIM_CAPTURE)
	ADCSRA |= (1 << ADATE);
	SFIOR |= ((1 << ADTS1) | (1 << ADTS2) | (1 << ADTS0));
	
	#else
	#error "ADC >> wrong MODE selection"
	#endif
	
	
	#if (PRESCALER == PRESCALER_2)
	// do nothing (default)
	#elif (PRESCALER == PRESCALER_4)
	ADCSRA |= ((1 << ADPS1));

	#elif (PRESCALER == PRESCALER_8)
	ADCSRA |= ((1 << ADPS1) | (1 << ADPS0));

	#elif (PRESCALER == PRESCALER_16)
	ADCSRA |= ((1 << ADPS2));

	#elif (PRESCALER == PRESCALER_32)
	ADCSRA |= ((1 << ADPS0) | (1 << ADPS2));

	#elif (PRESCALER == PRESCALER_64)
	ADCSRA |= ((1 << ADPS1) | (1 << ADPS2));

	#elif (PRESCALER == PRESCALER_128)
	ADCSRA |= ((1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));

	#else
	#error "ADC >> wrong PRESCALER selection"
	#endif
}


void ADC_voidEnable(void)
{
	ADCSRA |= (1<< ADEN);
	
}

void ADC_voidDisable(void)
{
	ADCSRA &= ~(1<< ADEN);
}

void ADC_voidStartConv (void)
{
	ADCSRA |= (1<< ADSC);
}



void ADC_voidIntEnable(void)
{
	ADCSRA |= (1 << ADIE);
}
void ADC_voidIntDisable(void)
{
	ADCSRA &= ~(1 << ADIE);
}



#if (RESOLUTION == EIGHT_BIT)
uint8 ADC_u8GetResult(uint8 channel)
{
	ADMUX &= 0b11100000;

	if(channel == 0)
	{
		ADMUX &= (~(1 << MUX0) & ~(1 << MUX1) & ~(1 << MUX2) & ~(1 << MUX3) & ~(1 << MUX4));
	}
	else if(channel == 1)
	{
		ADMUX |= ((1 << MUX0));
	}
	else if(channel == 2)
	{
		ADMUX |= ((1 << MUX1));
	}
	else if (channel == 3)
	{
		SET_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
	}
	else if (channel == 4)
	{
		SET_BIT(ADMUX,2);
	}
	else if (channel == 5)
	{
		SET_BIT(ADMUX,0);
		SET_BIT(ADMUX,2);
	}
	else if (channel == 6)
	{
		SET_BIT(ADMUX,2);
		SET_BIT(ADMUX,1);
	}
	else if (channel == 7)
	{
		SET_BIT(ADMUX,0);
		SET_BIT(ADMUX,1);
		SET_BIT(ADMUX,2);
	}
	
	
	//	ADMUX |= ((1 << MUX1) | (1 << MUX2) | (1 << MUX3) | (1 << MUX4));		//internal channel (1.22V)
	while (GET_BIT(ADCSRA,ADIF) == 0)
	{
	}
	CLR_BIT(ADCSRA,ADIF);
	return ADCH;
}
#else

uint16 ADC_u16GetResult(uint16 channel)
{
	return ADCDATA;
}
#endif

void ADC_voidSetCallBack(void (*Copy_ptr) (void))
{
	ADC_CallBack = Copy_ptr;
}


void __vector_16(void) __attribute__((signal,used));
void __vector_16(void)
{
	ADC_CallBack();
}