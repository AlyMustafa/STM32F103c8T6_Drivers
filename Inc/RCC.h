/*
 * RCC.h
 * Created on: Oct 3, 2023
 * Author: Ali Mustafa
 */

#ifndef RCC_H_
#define RCC_H_


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*Clock Enabling / Disabling Macros*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//------------------------------------
//-----------------GPIO---------------
//------------------------------------
//-----------------------ENABLE---------------------
#define RCC_GPIOA_CLK_EN()   (RCC->APB2ENR |= (1 << 2))
#define RCC_GPIOB_CLK_EN()	 (RCC->APB2ENR |= (1 << 3))
#define RCC_GPIOC_CLK_EN()	 (RCC->APB2ENR |= (1 << 4))
#define RCC_GPIOD_CLK_EN()	 (RCC->APB2ENR |= (1 << 5))
#define RCC_GPIOE_CLK_EN()	 (RCC->APB2ENR |= (1 << 6))
//-----------------------DISABLE----------------------
#define RCC_GPIOA_CLK_DIS()  (RCC->APB2ENR &= ~(1 << 2))
#define RCC_GPIOB_CLK_DIS()	 (RCC->APB2ENR &= ~(1 << 3))
#define RCC_GPIOC_CLK_DIS()	 (RCC->APB2ENR &= ~(1 << 4))
#define RCC_GPIOD_CLK_DIS()	 (RCC->APB2ENR &= ~(1 << 5))
#define RCC_GPIOE_CLK_DIS()	 (RCC->APB2ENR &= ~(1 << 6))
//-----------------------RESET------------------------
#define RCC_GPIOA_CLK_RESET()   (RCC->APB2RSTR |= (1 << 2)); (RCC->APB2RSTR &= ~(1 << 2));
#define RCC_GPIOB_CLK_RESET()	(RCC->APB2RSTR |= (1 << 3)); (RCC->APB2RSTR &= ~(1 << 3));
#define RCC_GPIOC_CLK_RESET()	(RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4));
#define RCC_GPIOD_CLK_RESET()	(RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5));
#define RCC_GPIOE_CLK_RESET()	(RCC->APB2RSTR |= (1 << 6)); (RCC->APB2RSTR &= ~(1 << 6));

//------------------------------------
//-----------------Timers-------------								Edit for M4
//------------------------------------
//-----------------------ENABLE---------------------
#define RCC_TIM1_CLK_EN()   	(RCC->APB2ENR |= (1 << 11))
#define RCC_TIM2_CLK_EN()   	(RCC->APB1ENR |= (1 << 0))
#define RCC_TIM3_CLK_EN()   	(RCC->APB1ENR |= (1 << 1))
#define RCC_TIM4_CLK_EN()   	(RCC->APB1ENR |= (1 << 2))
//-----------------------DISABLE----------------------
#define RCC_TIM1_CLK_DIS()   	(RCC->APB2ENR &= ~(1 << 11))
#define RCC_TIM2_CLK_DIS()   	(RCC->APB1ENR &= ~(1 << 0))
#define RCC_TIM3_CLK_DIS()   	(RCC->APB1ENR &= ~(1 << 1))
#define RCC_TIM4_CLK_DIS()   	(RCC->APB1ENR &= ~(1 << 2))
//-----------------------RESET------------------------
#define RCC_TIM1_CLK_RESET()   (RCC->APB2RSTR |= (1 << 11)); (RCC->APB2RSTR &= ~(1 << 11));
#define RCC_TIM2_CLK_RESET()   (RCC->APB1RSTR |= (1 << 0)); (RCC->APB1RSTR &= ~(1 << 0));
#define RCC_TIM3_CLK_RESET()   (RCC->APB1RSTR |= (1 << 1)); (RCC->APB1RSTR &= ~(1 << 1));
#define RCC_TIM4_CLK_RESET()   (RCC->APB1RSTR |= (1 << 2)); (RCC->APB1RSTR &= ~(1 << 2));

//---------------------------------
//---------------AFIO--------------								Edit for M4
//---------------------------------
//-----------------------ENABLE---------------------
#define RCC_AFIO_CLK_EN()	 (RCC->APB2ENR |= (1 << 0))
//-----------------------DISABLE----------------------
#define RCC_AFIO_CLK_DIS()	 (RCC->APB2ENR &= ~(1 << 0))


#endif /* RCC_H_ */
