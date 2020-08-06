/*
 * UART.h
 *
 * Created: 27-Jul-20 4:46:18 PM
 *  Author: Mohamed Elattar
 */ 


#ifndef UART_H_
#define UART_H_


void UART_voidInit();
void UART_voidSendChar(uint8 byte);
uint8 UART_uint8RecChar();
void UART_SendString(char *str);


#endif /* UART_H_ */