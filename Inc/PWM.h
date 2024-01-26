/*
 * PWM.h
 *
 *  Created on: 4/12/2023
 *      Author: Aly Mustafa
 */

#ifndef PWM_H_
#define PWM_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "GPIO.h"
//########################################     ENUMS     ###########################################
enum Mode_Type {
	none,compare,capture
};

enum Edge_Type {
	RISING,FALING
};
//########################################     pin_ref    ###########################################
/*
PA0 -> TIM2_CH1
PA1 -> TIM2_CH2
PA2 -> TIM2_CH3
PA3 -> TIM2_CH4

PA6 -> TIM3_CH1
PA7 -> TIM3_CH2
PB0 -> TIM3_CH3
PB1 -> TIM3_CH4

PA8 -> TIM1_CH1
PA9 -> TIM1_CH2
PA10 -> TIM1_CH3
PA11 -> TIM1_CH4
*/
//########################################     APIs    ###########################################

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-         Compare        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void Timer_compare_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val );
void Timer_compare_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val );
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-           PWM          *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void Timer_PWM_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val );
void Timer_PWM_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val );
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-           capture          *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void Timer_Capture_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint8_t edge );
void Timer_Capture_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint8_t edge );
uint16_t Timer_get_Capture_micro (GPIO_t* GPIOx , uint16_t pin );
uint16_t Timer_get_Capture_mili (GPIO_t* GPIOx , uint16_t pin );
#endif /* PWM_H_ */
