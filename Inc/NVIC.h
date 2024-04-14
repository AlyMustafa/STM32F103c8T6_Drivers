/*
 * stm32f103c6_NVIC.h
 * Created on: Oct 3, 2023
 * Author: Aly Mustafa
 */

#ifndef NVIC_H_
#define NVIC_H_

//EXTI							//Interrupt Request to NVIC
#define  EXTI0_IRQ				6
#define  EXTI1_IRQ				7
#define  EXTI2_IRQ 				8
#define  EXTI3_IRQ 				9
#define  EXTI4_IRQ 				10
#define  EXTI5_IRQ 				23
#define  EXTI6_IRQ 				23
#define  EXTI7_IRQ 				23
#define  EXTI8_IRQ 				23
#define  EXTI9_IRQ 				23
#define  EXTI10_IRQ 			40
#define  EXTI11_IRQ 			40
#define  EXTI12_IRQ 			40
#define  EXTI13_IRQ 			40
#define  EXTI14_IRQ 			40
#define  EXTI15_IRQ 			40

//--------------------------------------------
//-----------------EXTI Interrupt-------------								Edit for M4
//--------------------------------------------
//-----------------------ENABLE---------------------
#define NVIC_IRQ6_EXTI0_Enable   			NVIC_ISER0 |= (1<<6 )
#define NVIC_IRQ7_EXTI1_Enable    			NVIC_ISER0 |= (1<<7 )
#define NVIC_IRQ8_EXTI2_Enable   			NVIC_ISER0 |= (1<<8 )
#define NVIC_IRQ9_EXTI3_Enable    			NVIC_ISER0 |= (1<<9 )
#define NVIC_IRQ10_EXTI4_Enable    			NVIC_ISER0 |= (1<<10)
#define NVIC_IRQ23_EXTI5_9_Enable    		NVIC_ISER0 |= (1<<23)
#define NVIC_IRQ40_EXTI10_15_Enable   		NVIC_ISER1 |= (1<<8 ) //40-32=8
//-----------------------DISABLE----------------------
#define NVIC_IRQ6_EXTI0_Disable   			NVIC_ICER0 |= (1<<6 )
#define NVIC_IRQ7_EXTI1_Disable    			NVIC_ICER0 |= (1<<7 )
#define NVIC_IRQ8_EXTI2_Disable   			NVIC_ICER0 |= (1<<8 )
#define NVIC_IRQ9_EXTI3_Disable    			NVIC_ICER0 |= (1<<9 )
#define NVIC_IRQ10_EXTI4_Disable    		NVIC_ICER0 |= (1<<10)
#define NVIC_IRQ23_EXTI5_9_Disable   		NVIC_ICER0 |= (1<<23)
#define NVIC_IRQ40_EXTI10_15_Disable   		NVIC_ICER1 |= (1<<8 ) //40-32=8

//------------------------------------
//-----------------Timers-------------										Edit for M4
//------------------------------------
//-----------------------ENABLE---------------------
//TIMER 1,2,3,4
#define NVIC_IRQ25_TIM1_Enable   			NVIC_ISER0 |= (1<<25 )
#define NVIC_IRQ28_TIM2_Enable    			NVIC_ISER0 |= (1<<28 )
#define NVIC_IRQ29_TIM3_Enable   			NVIC_ISER0 |= (1<<29 )
#define NVIC_IRQ30_TIM4_Enable    			NVIC_ISER0 |= (1<<30 )
//-----------------------DISABLE----------------------
#define NVIC_IRQ25_TIM1_Disable  			NVIC_ICER0 |= (1<<25 )
#define NVIC_IRQ28_TIM2_Disable   			NVIC_ICER0 |= (1<<28 )
#define NVIC_IRQ29_TIM3_Disable   			NVIC_ICER0 |= (1<<29 )
#define NVIC_IRQ30_TIM4_Disable   			NVIC_ICER0 |= (1<<30 )
#endif /* NVIC_H_ */
