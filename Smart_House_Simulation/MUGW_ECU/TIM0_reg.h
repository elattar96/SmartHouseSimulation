#ifndef _TIM0_REG_H
#define _TIM0_REG_H

#define TIMSK	*((volatile uint8*)0x59)
#define TIFR	*((volatile uint8*)0x58)
#define TCCR0	*((volatile	uint8*)0x53)
#define TCNT0	*((volatile uint8*)0x52)
#define OCR0	*((volatile uint8*)0x5C)

#endif
