/*
 * SR_ECU.c
 *
 * Created: 30-Jul-20 1:20:08 AM
 * Author : Mohamed Elattar
 */ 

#include "std_types.h"
#include "bitwise.h"
#include <avr/io.h>
#include "DIO.h"
#include "I2C_Slave.h"
#include <stdio.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <string.h>
#include "ADC_int.h"
#include <avr/eeprom.h>
#include "LIGHT_SENSOR.h"


#define Slave_Address		0x20
void tempsensor();
void temp_sensor();
uint8 i2c_rec[20];
uint8 temp_thr1, temp_thr2, temp_thr3;
uint8 temp1, temp2, temp3;
uint8 rem1, rem2, rem3;
uint8_t listen;

 int main(void)
{
	
	uint8 i;
	uint8 i2c_buffer;


	
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_0,DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_3,DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTA,DIO_PIN_2,DIO_INPUT);

	
	DIO_void_SetPinDirection(DIO_PORTC,DIO_PIN_2,DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC,DIO_PIN_3,DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC,DIO_PIN_4,DIO_OUTPUT);
	
	
	temp1=eeprom_read_byte((const uint8_t*)64);
	rem1=eeprom_read_byte((const uint8_t*)65);
	temp1=temp1-0x30;
	rem1=rem1-0x30;
	temp_thr1=temp1*10+rem1;
	
	temp2=eeprom_read_byte((const uint8_t*)66);
	rem2=eeprom_read_byte((const uint8_t*)67);
	temp2=temp2-0x30;
	rem2=rem2-0x30;
	temp_thr2=temp2*10+rem2;
	
	temp3=eeprom_read_byte((const uint8_t*)68);
	rem3=eeprom_read_byte((const uint8_t*)69);
	temp3=temp3-0x30;
	rem3=rem3-0x30;
	temp_thr3=temp3*10+rem3;
	
	I2C_Slave_Init(Slave_Address);
	_delay_ms(2000);
	
	while(1)
	{
		
	listen = I2C_Slave_Listen();
	
		switch (listen)
		{
			// REC
			case 0:
			for (i=0;i<20;i++)
			{
				i2c_buffer=I2C_Slave_Receive();
				i2c_rec[i]=i2c_buffer;
				_delay_ms(50);
			}
			
		
				switch (i2c_rec[3])
				{
					case '8':
					temp1=i2c_rec[5];
					rem1=i2c_rec[6];
					eeprom_write_byte((uint8_t*)64,temp1);
					eeprom_write_byte((uint8_t*)65,rem1);
					temp1=temp1-0x30;
					rem1=rem1-0x30;
					temp_thr1=temp1*10+rem1;
				
					temp2=i2c_rec[7];
					rem2=i2c_rec[8];
					eeprom_write_byte((uint8_t*)66,temp2);
					eeprom_write_byte((uint8_t*)67,rem2);
					temp2=temp2-0x30;
					rem2=rem2-0x30;
					temp_thr2=temp2*10+rem2;
				
					temp3=i2c_rec[9];
					rem3=i2c_rec[10];
					eeprom_write_byte((uint8_t*)68,temp3);
					eeprom_write_byte((uint8_t*)69,rem3);
					temp3=temp3-0x30;
					rem3=rem3-0x30;
					temp_thr3=temp3*10+rem3;
					listen=5;
				}
		
			case 5:
			temp_sensor();
			break;
		
			default:
			tempsensor();
			break;
		}	
	}
}


void tempsensor()
{
	uint32 tempsensor1;
	uint32 tempsensor2;
	uint32 tempsensor3;
	
	temp1=eeprom_read_byte((const uint8_t*)64);
	rem1=eeprom_read_byte((const uint8_t*)65);
	temp1=temp1-0x30;
	rem1=rem1-0x30;
	temp_thr1=temp1*10+rem1;
		
	temp2=eeprom_read_byte((const uint8_t*)66);
	rem2=eeprom_read_byte((const uint8_t*)67);
	temp2=temp2-0x30;
	rem2=rem2-0x30;
	temp_thr2=temp2*10+rem2;
		
	temp3=eeprom_read_byte((const uint8_t*)68);
	rem3=eeprom_read_byte((const uint8_t*)69);
	temp3=temp3-0x30;
	rem3=rem3-0x30;
	temp_thr3=temp3*10+rem3;
	
	
		ADC_voidInitialize();
		ADC_voidEnable();
		ADC_voidStartConv();
		tempsensor1=ADC_u8GetResult(0);
		tempsensor1=tempsensor1*(500/256);
		if (tempsensor1>temp_thr1)
		{
			DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_4,DIO_HIGH);
		}
		else
		{
			DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_4,DIO_LOW);
		
		}
		
			
			ADC_voidInitialize();
			ADC_voidEnable();
			ADC_voidStartConv();
			tempsensor2=ADC_u8GetResult(3);
			tempsensor2=tempsensor2*(500/256);
			if (tempsensor2>temp_thr2)
			{
				DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_3,DIO_HIGH);
			}
			else
			{
				DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_3,DIO_LOW);
			}
			
			
	
	
	ADC_voidInitialize();
	ADC_voidEnable();
	ADC_voidStartConv();
	tempsensor3=ADC_u8GetResult(2);
	tempsensor3=tempsensor3*(500/256);
	
	if (tempsensor3>temp_thr3)
	{
		DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_2,DIO_HIGH);
		
	}
	else
	{
		DIO_void_SetPinValue(DIO_PORTC,DIO_PIN_2,DIO_LOW);
	}
	


	
	
	LIGHT_SENSOR1_read();
	LIGHT_SENSOR2_read();
	LIGHT_SENSOR3_read();
	
}



void temp_sensor()
{
	while (1)
	{
		tempsensor();
	}
}