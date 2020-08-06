/*
 * I2C_Slave.h
 *
 * Created: 29-Jul-20 12:03:56 AM
 *  Author: Mohamed Elattar
 */ 



#ifndef I2C_SLAVE_H_FILE_H_
#define I2C_SLAVE_H_FILE_H_

#include <avr/io.h>								

void I2C_Slave_Init(uint8_t slave_address);		
int8_t I2C_Slave_Listen();						
int8_t I2C_Slave_Transmit(char data);			
char I2C_Slave_Receive();						

#endif 