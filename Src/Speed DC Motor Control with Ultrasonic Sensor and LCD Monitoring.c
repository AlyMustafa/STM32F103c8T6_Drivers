/**
 ******************************************************************************
 * @file           : main.c
 * @author         : ALy Mustafa
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include "STM32F103x6.h"
#include "GPIO.h"
#include "EXTI.h"
#include "TIM.h"
#include "PWM.h"
#include "Servo.h"
#include "UltraSonic.h"
#include "dcmotor.h"



uint32_t mydistance = 0;

void Dc_Motor_STOP(){
	
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,0);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,0);
	
};

void Dc_Motor_Forward(){
	
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,1);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,0);
	
};

void Dc_Motor_Reverse(){
	
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,0);
	MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,1);
	
};

int main(){
	RCC_GPIOB_CLK_EN();
	RCC_GPIOA_CLK_EN();

	GPIO_config_t IN1 =  {GPIO_PIN_8 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t IN2 =  {GPIO_PIN_9 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };

	MCAL_GPIO_Init(GPIOB, &IN1);
	MCAL_GPIO_Init(GPIOB, &IN2);
	UltraSonic_init();
	LCD_init();
	
	while(1)
	{

		mydistance = Ultra_get_distance();
			if (mydistance < 10){
	Dc_Motor_STOP();
				
			LCD_send_string("So Close !!!");
			TDelay_Millis(500);
			LCD_Clear_Screen();
			TDelay_Millis(500);
			}
			else if (mydistance > 20){
				Dc_Motor_Forward();
				Dc_Motor_PWM(GPIOA , GPIO_PIN_11 ,100 );
				LCD_set_cursor(0,0);
				LCD_Clear_Screen();
				LCD_send_string("FULL SPEED");
				TDelay_Millis(500);

			}
			
			else  
				{
				Dc_Motor_Forward();
					uint16_t duty= (mydistance*80)/20;
				Dc_Motor_PWM(GPIOA , GPIO_PIN_11 ,duty);
				TDelay_Millis(10);
				LCD_set_cursor(0,0);
				LCD_send_string("distance = ");
				LCD_set_cursor(0,11);
					LCD_send_Num(mydistance);
					LCD_set_cursor(1,0);
					LCD_send_string("Duty cycle ");
					LCD_set_cursor(1,12);
					LCD_send_Num(duty);
					LCD_set_cursor(1,15);
					LCD_send_string("%");
					//LCD_Clear_Screen();
					
				}

	}
}

