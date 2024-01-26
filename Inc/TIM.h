/*
 * Stm32f103c6_GPIO_driver.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Ali Mustafa
 */

#ifndef INC_STM32F103C6_TIM_DRIVER_H_
#define INC_STM32F103C6_TIM_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
//-----------------------------
//User type definitions (structures & enums)
//-----------------------------
enum timerType {
	T,T1,T2,T3,T4
};
//########################################     APIs    ###########################################
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-         Timer          *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
TIM_t* get_timer (uint8_t timerType);
TIM_t* T_Start_micros (uint8_t timerType , uint16_t micros );
TIM_t* T_Start_millis (uint8_t timerType, uint16_t millis);
void T_Stop_Timer (uint8_t timerType);
uint16_t Tget_time_micros (uint8_t timerType);
uint16_t Tget_time_millis (uint8_t timerType);
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-         DELAY          *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void TDelay_Micro(uint8_t timerType , uint16_t micros);
void TDelay_Milli(uint8_t timerType , uint16_t millis);
void TDelay_Micros(uint16_t micros);
void TDelay_Millis(uint16_t millis);
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-         IRQ        *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void T_irq_micro_start(uint8_t timerType, uint16_t micros , void (* P_T_IRQ_CallBack)(void));
void T_irq_millis_start(uint8_t timerType, uint16_t millis , void (* P_T_IRQ_CallBack)(void));
void TClear_irq_Flag(uint8_t timerType);
void T_irq_stop(uint8_t timerType);

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
