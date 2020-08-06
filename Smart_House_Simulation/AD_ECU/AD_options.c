/*
 * AD_options.c
 *
 * Created: 02-Aug-20 3:47:02 AM
 *  Author: Mohamed Elattar
 */ 

#include "std_types.h"
#include "bitwise.h"
#include "LCD.h"
#include "I2C_Slave.h"
#include "AD_options.h"
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/eeprom.h> 

#define Slave_Address		0x20



void adoptions_void_selftest()
{
	uint8 i;
	uint8 i2c_buffer;
	uint8 i2c_rec[6];
	
	I2C_Slave_Init(Slave_Address);
	LCD_void_init();
	
	
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_4, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_5, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_6, DIO_OUTPUT);
	
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_7, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_0, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_1, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_2, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_3, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_4, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_5, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_6, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_7, DIO_OUTPUT);
	
	_delay_ms(5);
	
	while (1)
	{
		
		switch (I2C_Slave_Listen())
		{
			case 0:
			for (i=0;i<6;i++)
			{
				i2c_buffer=I2C_Slave_Receive();
				i2c_rec[i]=i2c_buffer;
				_delay_ms(50);
			}
			
			for (i=0;i<6;i++)
			{
				LCD_void_SendData(i2c_rec[i]);
			}
			
			case 1:
			if ((i2c_rec[0]=='a') && (i2c_rec[1]=='a') && (i2c_rec[2]=='0') && (i2c_rec[3]=='0') && (i2c_rec[4]=='5') && (i2c_rec[5]=='5'))
			{
				LCD_void_SendCommand(0xC0);
				for (i=0;i<6;i++)
				{
					I2C_Slave_Transmit(i2c_rec[i]);
					_delay_ms(5);
				}
			}
			default:
			break;
		
		}
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adoptions_void_lastrun()
{
	uint8 i, lastcontrol[12];
	for (i=0;i<12;i++)
	{
		lastcontrol[i]=eeprom_read_byte((const uint8_t*)64+i);
	}
	 
	 // door control
	if (lastcontrol[0]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_6, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_6, DIO_HIGH);
	}
	
	if (lastcontrol[1]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_5, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_5, DIO_HIGH);
	}
	
	if (lastcontrol[2]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_4, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_4, DIO_HIGH);
	}
	
	                                   ////////////////////////////////////////////////////////
									  
	// room 1
	if (lastcontrol[3]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_7, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_7, DIO_HIGH);
	}
	
	if (lastcontrol[4]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_0, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_0, DIO_HIGH);
	}
	
	if (lastcontrol[5]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_1, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_1, DIO_HIGH);
	}
	
	// room 2
	if (lastcontrol[6]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_2, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_2, DIO_HIGH);
	}
	
	if (lastcontrol[7]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_3, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_3, DIO_HIGH);
	}
	
	if (lastcontrol[8]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_4, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_4, DIO_HIGH);
	}
	
	
	//room 3
	if (lastcontrol[9]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_5, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_5, DIO_HIGH);
	}
	
	if (lastcontrol[10]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_6, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_6, DIO_HIGH);
	}
	
	
	if (lastcontrol[11]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_7, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_7, DIO_HIGH);
	}							  

	
	
	
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adoptions_void_homepage()
{
	
	LCD_void_SendCommand(0x01);
	uint8 i;
	
	uint8 i2c_buffer;
	uint8 i2c_rec[20];
	
	while (1)
	{
		
		switch (I2C_Slave_Listen())
		{
			// REC
			case 0:
			for (i=0;i<20;i++)
			{
				i2c_buffer=I2C_Slave_Receive();
				i2c_rec[i]=i2c_buffer;
				_delay_ms(50);
			}
			
			for (i=0;i<20;i++)
			{
				LCD_void_SendData(i2c_rec[i]);
			}
			
				switch (i2c_rec[3])
				{
				case '9':
				adoptions_void_doorcontrol(i2c_rec);
					break;
					
				case 'c':
				adoptions_void_rgbcontrol(i2c_rec);
					break;
					
				}
			
		
			
			default:
			break;
			
		}
		break;
	}
	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adoptions_void_doorcontrol(uint8 doorcontrol[])
{
	
		uint8 i, value[3];
		value[0]=doorcontrol[6];
		value[1]=doorcontrol[8];
		value[2]=doorcontrol[10];
		
		
		for (i=0;i<3;i++)
		{
			eeprom_update_byte((uint8_t*)64+i,value[i]);
		}
		
		if (doorcontrol[6]=='0')
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_6, DIO_LOW);
		}
		else
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_6, DIO_HIGH);
		}
		
		if (doorcontrol[8]=='0')
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_5, DIO_LOW);
		}
		else
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_5, DIO_HIGH);
		}
		
		if (doorcontrol[10]=='0')
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_4, DIO_LOW);
		}
		else
		{
			DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_4, DIO_HIGH);
		}
		
		adoptions_void_homepage();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void adoptions_void_rgbcontrol(uint8 rgbcontrol[])
{
	uint8 i, value[9];
	
	value[0]=rgbcontrol[6];
	value[1]=rgbcontrol[7];
	value[2]=rgbcontrol[8];	
	
	value[3]=rgbcontrol[10];
	value[4]=rgbcontrol[11];
	value[5]=rgbcontrol[12];
	
	value[6]=rgbcontrol[14];
	value[7]=rgbcontrol[15];
	value[8]=rgbcontrol[16];
	
	for (i=0;i<9;i++)
	{
		eeprom_update_byte((uint8_t*)67+i,value[i]);
	}
	
	// room 1
	if (rgbcontrol[6]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_7, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_7, DIO_HIGH);
	}
	
	if (rgbcontrol[7]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_0, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_0, DIO_HIGH);
	}
	
	if (rgbcontrol[8]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_1, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_1, DIO_HIGH);
	}
	
	// room 2
	if (rgbcontrol[10]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_2, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_2, DIO_HIGH);
	}
	
	if (rgbcontrol[11]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_3, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_3, DIO_HIGH);
	}
	
	if (rgbcontrol[12]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_4, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_4, DIO_HIGH);
	}
	
	
	//room 3
	if (rgbcontrol[14]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_5, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_5, DIO_HIGH);
	}
	
	if (rgbcontrol[15]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_6, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_6, DIO_HIGH);
	}
	
	
	if (rgbcontrol[16]=='0')
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_7, DIO_LOW);
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_7, DIO_HIGH);
	}
	
	
	adoptions_void_homepage();
}
