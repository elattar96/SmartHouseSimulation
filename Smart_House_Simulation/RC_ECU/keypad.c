/*
 * keypad.c
 *
 * Created: 23-Jul-20 3:42:57 PM
 *  Author: Mohamed Elattar
 */ 


/*
	Port rows 0->3, columns 4->7
*/

#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"

// Initialize Keypad pins.
void KEYPAD_void_Init(){
	

	
	// Rows
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_0, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_1, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_2, DIO_OUTPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_3, DIO_OUTPUT);
	
	// Columns
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_4, DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_5, DIO_INPUT);
	DIO_void_SetPinDirection(DIO_PORTC, DIO_PIN_6, DIO_INPUT);
	
	// Put 1 on input pins -> to activate pull-up resistance.
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_4, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_5, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_6, DIO_HIGH);
	
}

uint8 KEYPAD_uint8_GetKey(){
	
	uint8 buffer;
	
//---------------------------------------------FIRST ROW-------------------------------------------------

	// First Row.
	// Convert high to low and low to high, because you are working on active low configuration.
	// Need calibration.
	// Calibrate the cases also.
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_0, DIO_LOW);
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
	DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);
	
	// Hold data of all switches, each switch will take a separate bit.
	// 1st switch 3rd switch 4th switch -> buffer = 0b00001101
	// DIO_func gives use 1 or 0, remember that.
	buffer = 0;
	buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_4));
	buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_5) << 1);
	buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_6) << 2);
	
	
	// See which switch is pushed.
	switch(buffer){
		
		// Update -> Proteus works on active low, change cases on active low configurations.
		// buffer = 1 meaning, first button or switch is on ONLY.
		// put case 14 instead, next 13, next 11, next 7
		case 6:
			return '1';
			break;
			
		// buffer = 2 meaning, second button or switch is on ONLY.	
		case 5:
			return '2';
			break;
			
		case 3:
			// the button (3), the number 3 on the keypad.
			return '3';
			break;
		
	}
	
//-------------------------------------------SECOND ROW-------------------------------------------------

// Second Row.
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_1, DIO_LOW);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);

// Hold data of all switches, each switch will take a separate bit.
// 1st switch 3rd switch 4th switch -> buffer = 0b00001101
// DIO_func gives use 1 or 0, remember that.
buffer = 0;
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_4));
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_5) << 1);
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_6) << 2);

// See which switch is pushed.
switch(buffer){
	
	// buffer = 1 meaning, first button or switch is on ONLY.
	case 6:
	return '4';
	break;
	
	// buffer = 2 meaning, second button or switch is on ONLY.
	case 5:
	return '5';
	break;
	
	case 3:
	// the button (3), the number 3 on the keypad.
	return '6';
	break;
	
}
//----------------------------------------THIRD ROW---------------------------------------------------

// Third Row.
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_2, DIO_LOW);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);

// Hold data of all switches, each switch will take a separate bit.
// 1st switch 3rd switch 4th switch -> buffer = 0b00001101
// DIO_func gives use 1 or 0, remember that.
buffer = 0;
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_4));
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_5) << 1);
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_6) << 2);


// See which switch is pushed.
switch(buffer){
	
	// buffer = 1 meaning, first button or switch is on ONLY.
	case 6:
	return '7';
	break;
	
	// buffer = 2 meaning, second button or switch is on ONLY.
	case 5:
	return '8';
	break;
	
	case 3:
	// the button (3), the number 3 on the keypad.
	return '9';
	break;
	
}

//--------------------------------------------FOURTH ROW---------------------------------------------------

// Fourth Row.
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
DIO_void_SetPinValue(DIO_PORTC, DIO_PIN_3, DIO_LOW);

// Hold data of all switches, each switch will take a separate bit.
// 1st switch 3rd switch 4th switch -> buffer = 0b00001101
// DIO_func gives use 1 or 0, remember that.
buffer = 0;
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_4));
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_5) << 1);
buffer |= (DIO_uint8_GetPinValue(DIO_PORTC, DIO_PIN_6) << 2);

// See which switch is pushed.
switch(buffer){
	
	// buffer = 1 meaning, first button or switch is on ONLY.
	case 6:
	return '*';
	break;
	
	// buffer = 2 meaning, second button or switch is on ONLY.
	case 5:
	return '0';
	break;
	
	case 3:
	// th button (3), the number 3 on the keypad.
	return '#';
	break;
	
}
	// No button is pushed.
	return 0xff;
}