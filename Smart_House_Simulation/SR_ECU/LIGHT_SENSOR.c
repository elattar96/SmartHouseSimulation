#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"
#include "ADC_int.h"

static uint32 ligth0;

void LIGHT_SENSOR1_read(void)
{
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_5,DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTD,DIO_PIN_5,DIO_OUTPUT);
	ADC_voidInitialize();	
	ADC_voidEnable();
	ADC_voidStartConv();
	ligth0=ADC_u8GetResult(7);
	ligth0=ligth0*(500/256);
	
	if (ligth0<30)
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_5,DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_5,DIO_LOW);
	}
}

void LIGHT_SENSOR2_read(void)
{
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_6,DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTD,DIO_PIN_6,DIO_OUTPUT);
	ADC_voidInitialize();
	ADC_voidEnable();
	ADC_voidStartConv();
	ligth0=ADC_u8GetResult(6);
	ligth0=ligth0*(500/256);
	
	if (ligth0<30)
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_6,DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_6,DIO_LOW);
	}
}

void LIGHT_SENSOR3_read(void)
{
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_7,DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTD,DIO_PIN_7,DIO_OUTPUT);
	ADC_voidInitialize();
	ADC_voidEnable();
	ADC_voidStartConv();
	ligth0=ADC_u8GetResult(5);
	ligth0=ligth0*(500/256);
	
	if (ligth0<30)
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_7,DIO_HIGH);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_7,DIO_LOW);
	}
}
