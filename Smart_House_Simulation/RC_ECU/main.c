/*
 * RC_ECU.c
 *
 * Created: 30-Jul-20 1:16:48 AM
 * Author : Mohamed Elattar
 */ 


#include "std_types.h"
#include "bitwise.h"
#include "CLOCK.h"
#include <avr/io.h>
#include "LCD.h"
#include "keypad.h"
#include "UART.h"
#define F_CPU 8000000
#include <util/delay.h>
#include "RC_options.h"

int main(void)
{
	rcoptions_void_selftest();
	_delay_ms(300);
	rcoptions_void_securityaccess();
}










