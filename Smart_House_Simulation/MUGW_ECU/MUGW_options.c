/*
 * MUGW_options.c
 *
 * Created: 01-Aug-20 9:23:00 PM
 *  Author: Mohamed Elattar
 */ 
#include "std_types.h"
#include "bitwise.h"
#include "UART.h"
#include "I2C_Master.h"
#include <util/delay.h>
#include "MUGW_options.h"
#include "CLOCK.h"
#include "GIE_int.h"
#include "TIM0_int.h"
#include <avr/eeprom.h> 

#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21



void mugwoptions_void_selftest()
{
	uint8 i;
	uint8 uart_buffer, i2cad_buffer;
	uint8 uart_rec[6], i2cad_rec[6];
	
	UART_voidInit();
	I2C_Init();
	
	
	
	// MUGW rec from RC
	for (i=0;i<6;i++)
	{
		uart_buffer=UART_uint8RecChar();
		uart_rec[i]=uart_buffer;
		_delay_ms(50);
	}
	
	
	// MUGW send to AD
	if ((uart_rec[0]=='a') && (uart_rec[1]=='a') && (uart_rec[2]=='0') && (uart_rec[3]=='0') && (uart_rec[4]=='5') && (uart_rec[5]=='5'))
	{
		
		I2C_Start_Wait(Slave_Write_Address);
		_delay_ms(5);
		
		for (i=0; i<6; i++)
		{
			I2C_Write(uart_rec[i]);
			_delay_ms(50);
		}
		
		// MUGW rec from AD
		I2C_Repeated_Start(Slave_Read_Address);
		_delay_ms(5);
		for (i=0; i<7; i++)
		{
			if ((i<7))
			{
				i2cad_buffer=I2C_Read_Ack();
				i2cad_rec[i-1]=i2cad_buffer;
			}
			else 
			{
				i2cad_buffer=I2C_Read_Nack();
				i2cad_rec[i-1]=i2cad_buffer;	
			}
			_delay_ms(50);
		}
		
	}
	I2C_Stop();
	
	
	// 
	if ((i2cad_rec[0]=='a') && (i2cad_rec[1]=='a') && (i2cad_rec[2]=='0') && (i2cad_rec[3]=='0') && (i2cad_rec[4]=='5') && (i2cad_rec[5]=='5'))
	{
;
		for (i=0; i<6; i++)
		{
			UART_voidSendChar(i2cad_rec[i]);
			_delay_ms(300);
		}
	} 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_securityaccess(uint8 wrongpass)
{
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_4, DIO_OUTPUT);
	uint8 i;
	uint8 uart_buffer;
	uint8 uart_rec[16];
	char correctpasskey_msg[8]={'a','a','0','2','1','0','5','5'};
	char wrongpasskey_msg[8]={'a','a','0','2','1','1','5','5'};	
	char maxwrong_msg[8]={'a','a','0','4','1','0','5','5'};
    uint8_t newpass[6];
	
	for (i=0;i<16;i++)
	{
		uart_buffer=UART_uint8RecChar();
		uart_rec[i]=uart_buffer;
		
		_delay_ms(50);
	}
	
	for (i=3;i<16;i++)
	{
		uart_rec[i-3]=uart_rec[i];
	}

	
	for (i=0;i<6;i++)
	{
		newpass[i]=eeprom_read_byte((const uint8_t*) 64+i);
	}
	
	if ((uart_rec[5]=='0') && (uart_rec[6]=='0') && (uart_rec[7]=='0') && (uart_rec[8]=='0') && (uart_rec[9]=='0') && (uart_rec[10]=='0'))
	{
		
			for (i=0; i<8; i++)
			{
				UART_voidSendChar(correctpasskey_msg[i]);
				_delay_ms(50);
			}
			mugwoptions_void_homepage();
	} 
	
	else if ((uart_rec[5]==newpass[0]) && (uart_rec[6]==newpass[1]) && (uart_rec[7]==newpass[2]) && (uart_rec[8]==newpass[3]) && (uart_rec[9]==newpass[4]) && (uart_rec[10]==newpass[5]))
	
	{
			for (i=0; i<8; i++)
			{
				UART_voidSendChar(correctpasskey_msg[i]);
				_delay_ms(50);
			}
			mugwoptions_void_homepage();
	}
	else
	{
		if (wrongpass>0)
		{
				
				for (i=0; i<8; i++)
				{
					UART_voidSendChar(wrongpasskey_msg[i]);
					
					_delay_ms(50);
					
				}
				_delay_ms(500);
				mugwoptions_void_securityaccess(wrongpass-1);
		}
		else
		{
			for (i=0; i<8; i++)
			{
				UART_voidSendChar(maxwrong_msg[i]);
				_delay_ms(50);
			}	
		}
		
	
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void mugwoptions_void_homepage()
{
		
		uint8 i;
		uint8 uart_buffer;
		uint8 uart_rec[20];
		
		for (i=0;i<20;i++)
		{
			uart_buffer=UART_uint8RecChar();
			uart_rec[i]=uart_buffer;
			_delay_ms(50);
		}	
		
		switch (uart_rec[3])
		{
		case '3':
		mugwoptions_void_changepasskey(uart_rec);
			break;
			
		case '8':
		mugwoptions_void_tempcontrol(uart_rec);
			break;	
			
		
		case '5':
		mugwoptions_void_setcal(uart_rec);
			break;
			
		case '9':
		mugwoptions_void_doors(uart_rec);
			break;
		
		
		case 'c':
		mugwoptions_void_RGB(uart_rec);
		
			break;
			
		}	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_changepasskey(uint8 newpass[])
{
	uint8 i;
	for (i=0;i<6;i++)
	{
		eeprom_update_byte((uint8_t*)64+i,newpass[i+5]);
	}
	mugwoptions_void_homepage();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_tempcontrol(uint8 tempcontrol[])
{
		uint8 i;
		//uint8 i2cad_buffer;
		I2C_Start(Slave_Write_Address);
		_delay_ms(5);
		for (i=0; i<20; i++)
		{
			I2C_Write(tempcontrol[i]);
			_delay_ms(50);
		}
		I2C_Stop();
		mugwoptions_void_homepage();
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_viewcal()
{
	//LCD_void_WriteString("Date/Time");
	_delay_ms(300);
	mugwoptions_void_homepage();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_setcal(uint8 setcal[])
{
	
	uint8 i;
	for (i = 0; i < 20; i++)
	{
		RES_Date_and_Time(setcal[i]);
	}
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_doors(uint8 doorcontrol[])
{
	uint8 i;
	//uint8 i2cad_buffer;
	I2C_Start(Slave_Write_Address);
	_delay_ms(5);
	for (i=0; i<20; i++)
	{
		I2C_Write(doorcontrol[i]);
		_delay_ms(50);
	}
	I2C_Stop();
	mugwoptions_void_homepage();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mugwoptions_void_RGB(uint8 rgbcontrol[])
{
	uint8 i;
	//uint8 i2cad_buffer;
	I2C_Start(Slave_Write_Address);
	_delay_ms(5);
	for (i=0; i<20; i++)
	{
		I2C_Write(rgbcontrol[i]);
		_delay_ms(50);
	}
	I2C_Stop();
	mugwoptions_void_homepage();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

