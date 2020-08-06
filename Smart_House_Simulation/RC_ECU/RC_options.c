/*
 * RC_options.c
 *
 * Created: 30-Jul-20 2:37:53 AM
 *  Author: Mohamed Elattar
 */ 

#include "std_types.h"
#include "bitwise.h"
#include "LCD.h"
#include "keypad.h"
#include "UART.h"
#define F_CPU 8000000
#include "RC_options.h"
#include "fram_id.h"
#include <util/delay.h>
#include "CLOCK.h"
#include <avr/eeprom.h>



void rcoptions_void_selftest()
{
		
		uint8 i;
		uint8 selftest_msg[6]={'a','a','0','0','5','5'};
		uint8 uart_buffer;
		uint8 uart_rec[6];
		char welcome[]="Welcome";
		char home[]="Home";
		
		
		
		LCD_void_init();
		UART_voidInit();
		KEYPAD_void_Init();
		
		for (i=0;i<6;i++)
		{
			UART_voidSendChar(selftest_msg[i]);
			_delay_ms(50);
		}
		
		for (i=0;i<6;i++)
		{
			uart_buffer=UART_uint8RecChar();
			uart_rec[i]=uart_buffer;
			_delay_ms(50);
			
		}
		
		
		if ((uart_rec[0]=='a') && (uart_rec[1]=='a') && (uart_rec[2]=='0') && (uart_rec[3]=='0') && (uart_rec[4]=='5') && (uart_rec[5]=='5'))
		{
			
			LCD_void_SendCommand(0x84);
			LCD_void_WriteString(welcome);
			LCD_void_SendCommand(0xc6);
			LCD_void_WriteString(home);
		}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_securityaccess()
{
	DIO_void_SetPinDirection(DIO_PORTD, DIO_PIN_4, DIO_OUTPUT);
	char passmsg[]="Enter passkey";
	char wrongmsg[]="wrong passkey";
	char bye[]="Bye Bye";
	uint8 passkey [6];
	uint8 key, i=0, j=0;
	uint8 securityaccess_msg[13]={'a','a','0','1','6','0','0','0','0','0','0','5','5'};
	uint8 uart_buffer;
	uint8 uart_rec[8];	
	
	LCD_void_SendCommand(0x01);
	LCD_void_WriteString(passmsg);
	LCD_void_SendCommand(0xc5);
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		if((key != 0xff) && (i<6) && (key!='#') && (key!='*'))
		{
			passkey [i] = key;
			LCD_void_SendData('*');
			_delay_ms(250);
			i++;
		}
		if ((key=='#') && (i==6))
		{
			LCD_void_SendCommand(0x01);
			for (j=0;j<6;j++)
			{
				securityaccess_msg[j+5]=passkey[j];	
			}
			break;
			
		}
	}
	
	for (j=0; j<13; j++)
	{
		UART_voidSendChar(securityaccess_msg[j]);
		//LCD_void_SendData(securityaccess_msg[j]);
		_delay_ms(50);
	}
	
	for (i=0;i<8;i++)
	{
		uart_buffer=UART_uint8RecChar();
		uart_rec[i]=uart_buffer;
		//LCD_void_SendData(uart_rec[i]);
		_delay_ms(50);
	}
	
	if ((uart_rec[2]=='0') && (uart_rec[3]=='2') && (uart_rec[4]=='1') && (uart_rec[5]=='0'))
	{
		
		rcoptions_void_homepage();
	}
	if ((uart_rec[2]=='0') && (uart_rec[3]=='2') && (uart_rec[4]=='1') && (uart_rec[5]=='1'))
	{
		LCD_void_SendCommand(0x82);
		LCD_void_WriteString(wrongmsg);
		_delay_ms(500);
		UART_voidSendChar('a');
		UART_voidSendChar('a');
		UART_voidSendChar('a');
		rcoptions_void_securityaccess();
	}
	if ((uart_rec[2]=='0') && (uart_rec[3]=='4') && (uart_rec[4]=='1') && (uart_rec[5]=='0'))
	{
		LCD_void_SendCommand(0x83);
		LCD_void_WriteString(bye);
		_delay_ms(300);
		LCD_void_SendCommand(0x01);
		
	}
	
	
	
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rcoptions_void_homepage()
{
uint8 key;

LCD_void_SendCommand(0x80);
LCD_void_WriteString("Choose ur Option");
LCD_void_SendCommand(0xc0);
LCD_void_WriteString("* back   # next");

while (1)
{
	key=KEYPAD_uint8_GetKey();
	if(key != 0xff)
	{
		switch (key)
		{
			case '#':
			_delay_ms(250);
			rcoptions_void_home1();
			break;
			
			case '1':
			_delay_ms(250);
			rcoptions_void_changepasskey();
			break;
			
			case '2':
			_delay_ms(250);
			rcoptions_void_tempcontrol();
			break;
			
			case '3':
			_delay_ms(250);
			//SEND_Date_and_Time();
			LCD_void_SendCommand(0x01);
			LCD_void_WriteString("View date/time");
			_delay_ms(250);
			rcoptions_void_home1();
			break;
			
			case '4':
			_delay_ms(250);
			//SET_Date_and_Time();
			LCD_void_SendCommand(0x01);
			LCD_void_WriteString("set date/time");
			_delay_ms(250);
			rcoptions_void_home1();
			break;
			
			case '5':
			_delay_ms(250);
			rcoptions_void_doors();
			break;
			
			case '6':
			_delay_ms(250);
			rcoptions_void_RGB();
			break;
			
		}
	}
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_home1()
{
		uint8 key;
		char option1[]="1 Change Passkey";
		char option2[]="2 A/C Temp";
		LCD_void_SendCommand(0x01);
		LCD_void_SendCommand(0x80);
		LCD_void_WriteString(option1);
		LCD_void_SendCommand(0xc0);
		LCD_void_WriteString(option2);
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
				case '#':
				_delay_ms(250);
				rcoptions_void_home2();
					break;
					
					case '1':
					_delay_ms(250);
					rcoptions_void_changepasskey();
					break;
					
					case '2':
					_delay_ms(250);
					rcoptions_void_tempcontrol();
					break;
					
					case '3':
					_delay_ms(250);
					//SEND_Date_and_Time();
					LCD_void_SendCommand(0x01);
					LCD_void_WriteString("View date/time");
					_delay_ms(250);
					rcoptions_void_home1();
					break;
					
					case '4':
					_delay_ms(250);
					//SET_Date_and_Time();
					LCD_void_SendCommand(0x01);
					LCD_void_WriteString("set date/time");
					_delay_ms(250);
					rcoptions_void_home1();
					break;
					
					case '5':
					_delay_ms(250);
					rcoptions_void_doors();
					break;
					
					case '6':
					_delay_ms(250);
					rcoptions_void_RGB();
					break;
				}
			}			
		}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_home2()
{
	uint8 key;
	char option3[]="3 View Date/Time";
	char option4[]="4 Set Date/Time";
	LCD_void_SendCommand(0x01);
	LCD_void_SendCommand(0x80);
	LCD_void_WriteString(option3);
	LCD_void_SendCommand(0xc0);
	LCD_void_WriteString(option4);
	
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		if(key != 0xff)
		{
			switch (key)
			{
				case '#':
				_delay_ms(250);
				rcoptions_void_home3();
				break;
				
				case '*':
				_delay_ms(250);
				rcoptions_void_home1();
				break;
				
				case '1':
				_delay_ms(250);
				rcoptions_void_changepasskey();
				break;
				
				case '2':
				_delay_ms(250);
				rcoptions_void_tempcontrol();
				break;
				
				case '3':
				_delay_ms(250);
				//SEND_Date_and_Time();
				LCD_void_SendCommand(0x01);
				LCD_void_WriteString("View date/time");
				_delay_ms(250);
				rcoptions_void_home1();
				break;
				
				case '4':
				_delay_ms(250);
				//SET_Date_and_Time();
				LCD_void_SendCommand(0x01);
				LCD_void_WriteString("set date/time");
				_delay_ms(250);
				rcoptions_void_home1();
				break;
				
				case '5':
				_delay_ms(250);
				rcoptions_void_doors();
				break;
				
				case '6':
				_delay_ms(250);
				rcoptions_void_RGB();
				break;
				
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void rcoptions_void_home3()
{
	uint8 key;
	char option5[]="5 Doors Control";
	char option6[]="6 RGB Control";
	LCD_void_SendCommand(0x01);
	LCD_void_SendCommand(0x80);
	LCD_void_WriteString(option5);
	LCD_void_SendCommand(0xc0);
	LCD_void_WriteString(option6);
	
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					
					case '*':
					_delay_ms(250);
					rcoptions_void_home2();
					break;
					
					case '1':
					_delay_ms(250);
					rcoptions_void_changepasskey();
					break;
					
					case '2':
					_delay_ms(250);
					rcoptions_void_tempcontrol();
					break;
					
					case '3':
					_delay_ms(250);
					//SEND_Date_and_Time();
					LCD_void_SendCommand(0x01);
					LCD_void_WriteString("View date/time");
					_delay_ms(250);
					rcoptions_void_home1();
					break;
					
					case '4':
					_delay_ms(250);
					//SET_Date_and_Time();
					LCD_void_SendCommand(0x01);
					LCD_void_WriteString("set date/time");
					_delay_ms(250);
					rcoptions_void_home1();
					break;
					
					case '5':
					_delay_ms(250);
					rcoptions_void_doors();
					break;
					
					case '6':
					_delay_ms(250);
					rcoptions_void_RGB();
					break;
					
				}
			}

	
			
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_changepasskey()
{
	
	uint8 passkey [6];
	uint8 key, i=0, j=0;
	//uint8 changepasskey_msg[13]={'a','a','0','3','6','0','0','0','0','0','0','5','5'};
	uint8 changepasskey_msg[20]={'a','a','0','3','6','0','0','0','0','0','0','0','0','0','0','0','0','0','5','5'};
	
	
	LCD_void_SendCommand(0x01);
	LCD_void_WriteString("Set New Passkey");
	LCD_void_SendCommand(0xc5);
	
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		if((key != 0xff) && (i<6) && (key!='#') && (key!='*'))
		{
			passkey [i] = key;
			LCD_void_SendData('*');
			_delay_ms(250);
			i++;
		}
		if ((key=='#') && (i==6))
		{
			LCD_void_SendCommand(0x01);
			for (j=0;j<6;j++)
			{
				changepasskey_msg[j+5]=passkey[j];
			}
			break;
			
		}
	}
	
	for (j=0; j<20; j++)
	{
		UART_voidSendChar(changepasskey_msg[j]);
		_delay_ms(50);
	}
	LCD_void_SendCommand(0x82);
	LCD_void_WriteString("New Passkey");
	LCD_void_SendCommand(0xc4);
	LCD_void_WriteString("is set");
	_delay_ms(1000);
	rcoptions_void_home1();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_tempcontrol()
{
	uint8 i=0, key;
	uint32 rem1, temp1=21;
	uint32 rem2, temp2=21;
	uint32 rem3, temp3=21;
	
	
	
	uint8 tempcontrol_msg[20]={'a','a','0','8','6','0','0','0','0','0','0','5','5'};
		
		
	LCD_void_SendCommand(0x01);
	
	LCD_void_WriteString("Room1");
	LCD_void_SendCommand(0xC0);
	LCD_void_WriteString("A/C Temp: ");
	LCD_void_SendValue(temp1,0xCC);
	
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		if(key != 0xff)
		{
			switch (key)
			{
				case '2':
				if (temp1<30)
				{
					_delay_ms(250);
					temp1++;
					LCD_void_SendValue(temp1,0xCC);
					
				}
				break;
				
				case '8':
				if (temp1>16)
				{
					_delay_ms(250);
					temp1--;
					LCD_void_SendValue(temp1,0xCC);
					
				}
				break;	
				
				case '#':
				_delay_ms(250);
				rem1=temp1%10;
				temp1=temp1/10;
				tempcontrol_msg[5]=temp1+0x30;
				tempcontrol_msg[6]=rem1+0x30;
				
				
				// room2 /////////////
				
					LCD_void_SendCommand(0x01);
					
					LCD_void_WriteString("Room2");
					LCD_void_SendCommand(0xC0);
					LCD_void_WriteString("A/C Temp: ");
					LCD_void_SendValue(temp2,0xCC);
					
					while (1)
					{
						key=KEYPAD_uint8_GetKey();
						if(key != 0xff)
						{
							switch (key)
							{
								case '2':
								if (temp2<30)
								{
									_delay_ms(250);
									temp2++;
									LCD_void_SendValue(temp2,0xCC);
									
								}
								break;
								
								case '8':
								if (temp2>16)
								{
									_delay_ms(250);
									temp2--;
									LCD_void_SendValue(temp2,0xCC);
									
								}
								break;
								
								case '#':
								_delay_ms(250);
								rem2=temp2%10;
								temp2=temp2/10;
								tempcontrol_msg[7]=temp2+0x30;
								tempcontrol_msg[8]=rem2+0x30;
								
								
								
								// room3 ///////////////////////////////////////////////
								
								LCD_void_SendCommand(0x01);
								
								LCD_void_WriteString("Room3");
								LCD_void_SendCommand(0xC0);
								LCD_void_WriteString("A/C Temp: ");
								LCD_void_SendValue(temp3,0xCC);
								
								while (1)
								{
									key=KEYPAD_uint8_GetKey();
									if(key != 0xff)
									{
										switch (key)
										{
											case '2':
											if (temp3<30)
											{
												_delay_ms(250);
												temp3++;
												LCD_void_SendValue(temp3,0xCC);
												
											}
											break;
											
											case '8':
											if (temp3>16)
											{
												_delay_ms(250);
												temp3--;
												LCD_void_SendValue(temp3,0xCC);
												
											}
											break;
											
											case '#':
											_delay_ms(250);
											rem3=temp3%10;
											temp3=temp3/10;
											tempcontrol_msg[9]=temp3+0x30;
											tempcontrol_msg[10]=rem3+0x30;
											
											
											//////////////////////////////////////////////////
												LCD_void_SendCommand(0x01);
												for (i=0;i<20;i++)
												{
													UART_voidSendChar(tempcontrol_msg[i]);
													_delay_ms(50);
												}
												
												rcoptions_void_home1();
											
											
											///////////////////////////////////////////////////////
											break;
											
										}
										
									}
									
								}
								
								
								
								
								
								break;
								
							}
						}
						
					}
				
				
				break;
				
			}
			
		}
		
	}
	
  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_setcal()
{
	LCD_void_SendCommand(0x01);
	LCD_void_WriteString("set date/time");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_viewcal()
{
	LCD_void_SendCommand(0x01);
	LCD_void_WriteString("view date/time");
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_doors()
{
	uint8 i=0, key;
	uint8 doorcontrol_msg[20]={'a','a','0','9','6','1','0','2','0','3','0','0','0','0','0','0','0','0','5','5'};
	LCD_void_SendCommand(0x01);
	
	LCD_void_SendCommand(0x80);
	LCD_void_WriteString("Room1");
	LCD_void_SendCommand(0xc0);
	LCD_void_WriteString("0 close  1 open");
		
	while (1)
	{
		key=KEYPAD_uint8_GetKey();
		if(key != 0xff)
		{
			switch (key)
			{
				case '1':
				_delay_ms(250);
				doorcontrol_msg[6]='1';
				break;
					
				case '0':
				_delay_ms(250);
				doorcontrol_msg[6]='0';
				break;
							
			}
			break;
		}
	}
	
	LCD_void_SendCommand(0x80);
	LCD_void_WriteString("Room2");
	LCD_void_SendCommand(0xc0);
	LCD_void_WriteString("0 close  1 open");
	
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '1':
					_delay_ms(250);
					doorcontrol_msg[8]='1';
					break;
					
					case '0':
					_delay_ms(250);
					doorcontrol_msg[8]='0';
					break;
					
				}
				break;
			}
		}
	
		LCD_void_SendCommand(0x80);
		LCD_void_WriteString("Room3");
		LCD_void_SendCommand(0xc0);
		LCD_void_WriteString("0 close  1 open");
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '1':
					_delay_ms(250);
					doorcontrol_msg[10]='1';
					break;
					
					case '0':
					_delay_ms(250);
					doorcontrol_msg[10]='0';
					break;
					
				}
				break;
			}
		}
	
				
	for (i=0; i<20; i++)
	{
		UART_voidSendChar(doorcontrol_msg[i]);
		_delay_ms(50);
	}
	
	LCD_void_SendCommand(0x01);
	LCD_void_SendCommand(0x82);
	LCD_void_WriteString("Doors control");
	LCD_void_SendCommand(0xc4);
	LCD_void_WriteString("is set");
	_delay_ms(1000);
	rcoptions_void_home1();
}

	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rcoptions_void_RGB()
{
		uint8 i=0, key;
		uint8 rgbcontrol_msg[20]={'a','a','0','c','c','1','0','0','0','2','0','0','0','3','0','0','0','0','5','5'};
		
		
		// room 1	
		LCD_void_SendCommand(0x01);
		LCD_void_SendCommand(0x80);
		LCD_void_WriteString("Room1");
		LCD_void_SendCommand(0xc0);
		LCD_void_WriteString("R ");
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[6]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[6]='1';
					break;
					
				}
				break;
			}
		}
		
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[7]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[7]='1';
					break;
					
				}
				break;
			}
		}
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					rgbcontrol_msg[8]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					rgbcontrol_msg[8]='1';
					break;
					
				}
				break;
			}
		}
		_delay_ms(250);
		
		// room 2
		LCD_void_SendCommand(0x01);
		LCD_void_SendCommand(0x80);
		LCD_void_WriteString("Room2");
		LCD_void_SendCommand(0xc0);
		LCD_void_WriteString("R ");

		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[10]='0';
					break;
			
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[10]='1';
					break;
			
				}
				break;
			}
		}


		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[11]='0';
					break;
			
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[11]='1';
					break;
			
				}
				break;
			}
		}

		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					rgbcontrol_msg[12]='0';
					break;
			
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					rgbcontrol_msg[12]='1';
					break;
			
				}
				break;
			}
		}
		
		_delay_ms(250);
		// room 3
		LCD_void_SendCommand(0x01);
		LCD_void_SendCommand(0x80);
		LCD_void_WriteString("Room3");
		LCD_void_SendCommand(0xc0);
		LCD_void_WriteString("R ");
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[14]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  G ");
					rgbcontrol_msg[14]='1';
					break;
					
				}
				break;
			}
		}
		
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[15]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					LCD_void_WriteString("  B ");
					rgbcontrol_msg[15]='1';
					break;
					
				}
				break;
			}
		}
		
		while (1)
		{
			key=KEYPAD_uint8_GetKey();
			if(key != 0xff)
			{
				switch (key)
				{
					case '0':
					_delay_ms(250);
					LCD_void_SendData('0');
					rgbcontrol_msg[16]='0';
					break;
					
					case '1':
					_delay_ms(250);
					LCD_void_SendData('1');
					rgbcontrol_msg[16]='1';
					break;
					
				}
				break;
			}
		}
		_delay_ms(250);
			
		for (i=0; i<20; i++)
		{
			UART_voidSendChar(rgbcontrol_msg[i]);
			_delay_ms(50);
		}
		
			LCD_void_SendCommand(0x01);
			LCD_void_SendCommand(0x82);
			LCD_void_WriteString("RGB control");
			LCD_void_SendCommand(0xc4);
			LCD_void_WriteString("is set");
			_delay_ms(1000);
			rcoptions_void_home1();
				
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



