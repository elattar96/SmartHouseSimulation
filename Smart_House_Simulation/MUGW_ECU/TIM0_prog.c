#include "STD_types.h"
#include "bitwise.h"
#include "TIM0_reg.h"
#include "TIM0_priv.h"
#include "TIM0_config.h"
#include "TIM0_int.h"


static void(*TIM0_CallBack)(void);
static void(*TIM0_CallBack_CTC)(void);

/* Description:  */
void TIM0_voidInitialize(void)
{
	uint8 MODE=0;
	//han5aly el prescaler a5er 7aga 3shan ana mograd makatbt el prescaller haybtdy 3ad
	
	/*Disable interrupt */  //3ashan el setcallback delwa2ty feha gabrage fna h3melo enable lama y7ot el call back
	CLR_BIT(TIMSK,0);
	/* Clear Flag */
	SET_BIT(TIFR,0);
	/* Set Mode and Prescaller */
	#if TIM0_u16_MODE == TIM0_NORMAL_MODE
	MODE = TIM0_NORMAL_MODE;
	#elif TIM0_u16_MODE ==TIM0_CTC_MODE
	MODE = TIM0_CTC_MODE;
	#elif TIM0_u16_MODE ==TIM0_FAST_PWM_MODE
	MODE = TIM0_FAST_PWM_MODE;
	#elif TIM0_u16_MODE ==TIM0_PHASE_PWM_MODE
	MODE = TIM0_PHASE_PWM_MODE;
	#endif

	#if TIM0_u16_PRESCALLER ==TIM0_u16_DIV_1
	TCCR0 = MODE | 0b00000001;
	#elif TIM0_u16_PRESCALLER ==TIM0_u16_DIV_8
	TCCR0 = MODE | 0b00000010;
	#elif TIM0_u16_PRESCALLER ==TIM0_u16_DIV_64
	TCCR0 = MODE | 0b00000011;
	#elif TIM0_u16_PRESCALLER ==TIM0_u16_DIV_256
	TCCR0 = MODE | 0b00000100;
	#elif TIM0_u16_PRESCALLER ==TIM0_u16_DIV_1024
	TCCR0 = MODE | 0b00000101;
	#endif
	
}

/* Description:  */
void TIM0_voidEnableInt(void)
{
	SET_BIT(TIMSK,0);
}


void TIM0_voidDisableInt(void)
{
	CLR_BIT(TIMSK,0);
}

void TIM0_voidSetRegister(uint8 Copy_u8Value)
{
	TCNT0 = Copy_u8Value;
}

void TIM0_voidSet_OCR0(uint8 Copy_u8Value)
{
	OCR0 = Copy_u8Value;
}


void TIM0_voidSetCallBack(void (*Copy_ptr) (void))
{
	TIM0_CallBack = Copy_ptr;
}

void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	TIM0_CallBack();
}

void TIM0_voidSetCallBack_CTC(void (*Copy_ptr) (void))
{
	TIM0_CallBack_CTC = Copy_ptr;
}

void __vector_10(void) __attribute__((signal,used));
void __vector_10(void)
{
	TIM0_CallBack_CTC();
}

