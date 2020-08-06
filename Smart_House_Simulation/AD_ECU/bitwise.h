/*
 * bitwise.h
 *
 * Created: 23-Jul-20 1:42:02 PM
 *  Author: Mohamed Elattar
 */ 

#ifndef BITWISE_H_
#define BITWISE_H_
#define SET_BIT(reg, pin) reg|=(1<<pin)
#define CLR_BIT(reg, pin) reg&=(~(1<<pin))
#define TOGGLE_BIT(reg, pin) reg^=(1<<pin)


#define GET_BIT(reg, pin) ((reg>>pin)&1)
#endif /* BITWISE_H_ */

