#ifndef _TIM0_INT_H
#define _TIM0_INT_H
#include "std_types.h"

/* Description:  */
void TIM0_voidInitialize(void);

/* Description:  */
void TIM0_voidEnableInt(void);


void TIM0_voidDisableInt(void);


void TIM0_voidSetRegister(uint8 Copy_u8Value);
void TIM0_voidSet_OCR0(uint8 Copy_u8Value);

void TIM0_voidSetCallBack(void (*Copy_ptr) (void));
void TIM0_voidSetCallBack_CTC(void (*Copy_ptr) (void));

void SET_Date_and_Time(void);
void RUN_Date_and_Time (void);

#endif
