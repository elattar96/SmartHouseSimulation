#ifndef _TIM0_CONFIG_H
#define _TIM0_CONFIG_H

/*	Range:  TIM0_u16_DIV_1 		*/
/*			TIM0_u16_DIV_8 		*/
/*		 	TIM0_u16_DIV_64		*/
/*			TIM0_u16_DIV_256	*/
/*			TIM0_u16_DIV_1024	*/

#define TIM0_u16_PRESCALLER	TIM0_u16_DIV_256


/* MODE:  TIM0_NORMAL_MODE
          TIM0_CTC_MODE
          TIM0_FAST_PWM_MODE
          TIM0_PHASE_PWM_MODE   */

#define TIM0_u16_MODE TIM0_NORMAL_MODE


#endif
