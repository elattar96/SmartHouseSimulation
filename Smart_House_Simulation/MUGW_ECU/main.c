/*
 * MUGW_ECU.c
 *
 * Created: 30-Jul-20 1:18:16 AM
 * Author : Mohamed Elattar
 */ 
#include "std_types.h"
#include "bitwise.h"
#include <avr/io.h>
#include "LCD.h"
#include "keypad.h"
#include "UART.h"
#include "I2C_Master.h"
#include <util/delay.h>
#include "MUGW_options.h"
#include "DIO.h"
#include "CLOCK.h"
#include "GIE_int.h"
#include "TIM0_int.h"


#define Slave_Write_Address		0x20
#define Slave_Read_Address		0x21

//void second (void);
//volatile uint8 counter=0;


int main(void)
{
	//GIE_voidEnable();
	//TIM0_voidInitialize();
	//TIM0_voidEnableInt();
	//TIM0_voidSetRegister(238);
	//TIM0_voidSetCallBack(second);
	
	
	uint8 wrongpass=2;
	mugwoptions_void_selftest();
	//_delay_ms(300);
	mugwoptions_void_securityaccess(wrongpass);
	
	
	

		
	
	
	//while (1)
	//{
		
	//}
	

}

/*void second (void)
{
	counter++;
	if (counter==85)
	{
		RUN_Date_and_Time();
		counter=0;
		TIM0_voidSetRegister(238);
	}
}*/

	














/*int main(void)
{

	uint8 i;
	uint8 uart_buffer, i2cad_buffer;
	uint8 uart_rec[6], i2cad_rec[6];
	
	UART_voidInit();
	I2C_Init();
	LCD_void_init();
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_4, DIO_OUTPUT);
	//DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_5, DIO_HIGH);
	
	// MUGW rec from RC
	for (i=0;i<6;i++)
	{
		uart_buffer=UART_uint8RecChar();
		uart_rec[i]=uart_buffer;
		_delay_ms(500);
	}
	
	for (i=0;i<6;i++)
	{
		LCD_void_SendData(uart_rec[i]);
	}
	
	// MUGW send to AD
	if ((uart_rec[0]=='a') && (uart_rec[1]=='a') && (uart_rec[2]=='0') && (uart_rec[3]=='0') && (uart_rec[4]=='5') && (uart_rec[5]=='5'))
	{
		DIO_void_SetPinValue(DIO_PORTD, DIO_PIN_4, DIO_HIGH);
		
		I2C_Start_Wait(Slave_Write_Address);
		_delay_ms(5);
		
		for (i=0; i<6; i++)
		{
			I2C_Write(uart_rec[i]);
			_delay_ms(500);
		}
		
		// MUGW rec from AD
		I2C_Repeated_Start(Slave_Read_Address);
		_delay_ms(5);
		for (i=0; i<6; i++)
		{
			if (i!=5)
			{
				i2cad_buffer=I2C_Read_Ack();
				i2cad_rec[i]=i2cad_buffer;
			}
			if (i==5)
			{
				i2cad_buffer=I2C_Read_Nack();
				i2cad_rec[i]=i2cad_buffer;
			}
			_delay_ms(500);
		}
		
	}
	I2C_Stop();
	
	//
	if ((i2cad_rec[0]=='a') && (i2cad_rec[1]=='a') && (i2cad_rec[2]=='0') && (i2cad_rec[3]=='0') && (i2cad_rec[4]=='5') && (i2cad_rec[5]=='5'))
	{
		for (i=0; i<6; i++)
		{
			UART_voidSendChar(uart_rec[i]);
			_delay_ms(500);
		}
	}
}*/








/*int main(void)
{
	uint8 key;
	
	KEYPAD_void_Init();
	LCD_void_init();
	UART_voidInit();
	
	uint8 send1[3]={'a','0','5'};
	uint8 send2[3]={'f','f','c'};
	uint8 i;
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		
		if (key=='1')
		{
			for (i=0;i<3;i++)
			{
				UART_voidSendChar(send1[i]);
				LCD_void_SendData(send1[i]);
				_delay_ms(500);
			}
		}
		if (key=='2')
		{
			for (i=0;i<3;i++)
			{
				UART_voidSendChar(send2[i]);
				LCD_void_SendData(send2[i]);
				_delay_ms(500);
			}
		}
	}

}*/





/*int main(void)
{
	uint8 x,i=0;
	uint8 res[10];
	uint8 i2c_x;
	uint8 i2c_rec[10];
	
	
	UART_voidInit();
	LCD_void_init();
	I2C_Init();
	DIO_void_SetPinDirection(DIO_PORTD,DIO_PIN_4,DIO_OUTPUT);
	//DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_4,DIO_HIGH);
	
	while (i<6)
	{
		x=UART_uint8RecChar();
		res[i]=x;
		i++;
		_delay_ms(500);
	}
	
	//LCD print data
	for (i=0;i<6;i++)
	{
		LCD_void_SendData(res[i]);
	}
	
	//DIO output
	if ((res[0]=='a') && (res[1]=='a') && (res[2]=='0') && (res[3]=='0') && (res[4]=='5') && (res[5]=='5'))
	{
		
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_4,DIO_HIGH);
	}
	
	if ((res[0]=='f') && (res[1]=='f') && (res[2]=='c'))
	{
		DIO_void_SetPinValue(DIO_PORTD,DIO_PIN_5,DIO_HIGH);
	}
	
	// I2C send data
	I2C_Start_Wait(Slave_Write_Address);
	_delay_ms(5);
	for (i=0;i<3;i++)
	{
		I2C_Write(res[i]);
		_delay_ms(500);
	}
	
	//I2C rec data
	I2C_Repeated_Start(Slave_Read_Address);
	_delay_ms(5);
	for (i=0;i<3;i++)
	{
		i2c_x=UART_uint8RecChar();
		if (i!=2);
		{
			i2c_rec[i]=I2C_Read_Ack();
		}
		if (i==2)
		{
			i2c_rec[i]=I2C_Read_Nack();
		}
		_delay_ms(500);
	}
	I2C_Stop();
	
	
}*/

