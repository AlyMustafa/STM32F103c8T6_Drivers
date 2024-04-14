/*
 * Ultrasonic_driver.h
 *
 *  Created on: Feb 12, 2024
 *      Author: Ali Mustafa
 */

#ifndef ULTRASONIC_DRIVER_H_
#define ULTRASONIC_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "GPIO.h"
#include "TIM.h"
//-----------------------------

//Echo -----> PA.1
//Trig -----> PA.0

void UltraSonic_init();
uint32_t Ultra_get_distance();


#endif