/*
 * Servo.h
 * Created on: 4/12/2023
 * Author: Aly Mustafa
 */

#ifndef SERVO_H_
#define SERVO_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "GPIO.h"
#include "PWM.h"

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

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-         Driver_concept         *-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

/*
 To achieve a 50Hz signal with a 72MHz clock:

 1. Calculate the period value (ARR - Auto Reload Register):
    - Divide the clock frequency by the desired frequency: ARR = 72,000,000 / 50 = 1,440,000.
    - Set ARR to 1,439,999 (subtracting 1).

 2. Choose a suitable Prescaler (PSC) value:
    - Since ARR is less than or equal to 65,535, set PSC to 144.

 3. Calculate CCRx values for each angle:
    - For 0.5ms (0 degrees):
      - Calculate CCRx = (0.5 * 10,000) / 20 = 250.
    - For 1.5ms (90 degrees):
      - Calculate CCRx = (1.5 * 10,000) / 20 = 750.
    - For 2.5ms (180 degrees):
      - Calculate CCRx = (2.5 * 10,000) / 20 = 1,250.

 These CCRx values correspond to 0, 90, and 180 degrees respectively. 
 Adjust these values as needed for your servo motor control.
*/

//########################################     APIs    ###########################################
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-           PWM          *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
void Servo_Write(GPIO_t* GPIOx , uint16_t pin , uint16_t Angle );
void Servo_Stop(GPIO_t* GPIOx , uint16_t pin);

#endif /* SERVO_H_ */
