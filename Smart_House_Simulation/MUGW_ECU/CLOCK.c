#include "STD_types.h"
#include "bitwise.h"
#include "LCD.h"
#include "keypad.h"
#include "UART.h"
#include "avr\delay.h"

static uint8 setclock_msg[20];
static uint8 j=0;	
	
void RUN_Date_and_Time (void)
{
	// TIME RUN
	
	if(setclock_msg[13]<='9')
	{
		setclock_msg[13]++;
		if (setclock_msg[13]==':')
		{
			setclock_msg[13]='0';
		}
	}
	
	if (setclock_msg[13]=='0')
	{
		if (setclock_msg[12]=='5')
		{
			setclock_msg[12]='0';
			setclock_msg[15]++;
		}
		else if (setclock_msg[12]<='6')
		{
			setclock_msg[12]++;
		}
	}
	
	if (setclock_msg[15]==':')
	{
		setclock_msg[15]='0';
		setclock_msg[14]++;
	}
	
	if (setclock_msg[14]=='6')
	{
		setclock_msg[14]='0';
		setclock_msg[17]++;
	}
	
	if (setclock_msg[17]==':')
	{
		setclock_msg[17]='0';
		setclock_msg[16]++;
	}
	if ((setclock_msg[16]=='2') && (setclock_msg[17]=='4'))
	{
		setclock_msg[17]='0';
		setclock_msg[16]='0';
		setclock_msg[15]='0';
		setclock_msg[14]='0';
		setclock_msg[13]='0';
		setclock_msg[12]='0';
		setclock_msg[5]++;
	}
	
	// DATE RUN
	
	if (setclock_msg[5]==':')
	{
		setclock_msg[4]++;
		setclock_msg[5]='0';
	}
	
	if ((setclock_msg[4]=='3') && (setclock_msg[5]=='1'))
	{
		setclock_msg[7]++;
		setclock_msg[4]='0';
		setclock_msg[5]='1';
	}
	
	if (setclock_msg[7]==':')
	{
		setclock_msg[6]++;
		setclock_msg[7]='0';
	}
	
	if ((setclock_msg[6]=='1') && (setclock_msg[7]=='3'))
	{
		setclock_msg[11]++;
		setclock_msg[6]='0';
		setclock_msg[7]='1';
	}
	
	if (setclock_msg[11]==':')
	{
		setclock_msg[10]++;
		setclock_msg[11]='0';
	}
	
	if (setclock_msg[10]==':')
	{
		setclock_msg[9]++;
		setclock_msg[10]='0';
	}
	
	if (setclock_msg[9]==':')
	{
		setclock_msg[8]++;
		setclock_msg[9]='0';
	}
	
	
	// DISPLAY Date and Time
	
	LCD_void_SendCommand(0x01);
	LCD_void_SendData(setclock_msg[4]);
	LCD_void_SendData(setclock_msg[5]);
	LCD_void_SendData('/');
	LCD_void_SendData(setclock_msg[6]);
	LCD_void_SendData(setclock_msg[7]);
	LCD_void_SendData('/');
	LCD_void_SendData(setclock_msg[8]);
	LCD_void_SendData(setclock_msg[9]);
	LCD_void_SendData(setclock_msg[10]);
	LCD_void_SendData(setclock_msg[11]);
	LCD_void_SendCommand(0xC0);
	LCD_void_SendData(setclock_msg[16]);
	LCD_void_SendData(setclock_msg[17]);
	LCD_void_SendData(':');
	LCD_void_SendData(setclock_msg[14]);
	LCD_void_SendData(setclock_msg[15]);
	LCD_void_SendData(':');
	LCD_void_SendData(setclock_msg[12]);
	LCD_void_SendData(setclock_msg[13]);
	j=0;

}

void RES_Date_and_Time(uint8 res)
{
	setclock_msg[j]=res;
	j++;
}

void SEND_Date_and_Time(void)
{
	uint8 i;
	for (i=0;i<20;i++)
	{
		UART_voidSendChar(setclock_msg[i]);
		_delay_ms(500);
	}
}