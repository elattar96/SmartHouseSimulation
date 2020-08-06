/*
 * AD_ECU.c
 *
 * Created: 30-Jul-20 1:18:54 AM
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
#include "AD_options.h"


#define Slave_Address		0x20

int main(void)
{
		adoptions_void_selftest();	
		adoptions_void_lastrun();	
		adoptions_void_homepage();
}


