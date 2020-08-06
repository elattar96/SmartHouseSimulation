/*
 * UART.c
 *
 * Created: 27-Jul-20 4:46:33 PM
 *  Author: Mohamed Elattar
 */ 

#include "bitwise.h"
#include "std_types.h"
#include "DIO.h"
#include <avr/io.h>


void UART_voidInit()
{
	//INT
	SET_BIT(SREG,7);
	
	//REG A
	CLR_BIT(UCSRA,1);
	CLR_BIT(UCSRA,0);
	
	//REG B
	SET_BIT(UCSRB,7);
	CLR_BIT(UCSRB,6);
	CLR_BIT(UCSRB,5);
	SET_BIT(UCSRB,4);
	SET_BIT(UCSRB,3);
	CLR_BIT(UCSRB,2);
	
	//REG C
	UCSRC=0b10000110;
	
	
	UBRRH = 0x00;
	UBRRL = 51;

}

void UART_voidSendChar(uint8 byte)
{
	while(GET_BIT(UCSRA,5)==0);
	UDR = byte;

}

uint8 UART_uint8RecChar(void)
{
	uint8 Value;
	while (GET_BIT(UCSRA,7)==0);
	Value=UDR;
	return Value;
}

void UART_SendString(char *str)
{
	unsigned char j=0;
	
	while (str[j]!=0)		/* Send string till null */
	{
		UART_voidSendChar(str[j]);
		j++;
	}
}