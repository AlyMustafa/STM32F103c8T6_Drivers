/*
 * Stm32f103c6_GPIO_driver.c
 *
 *   Created on: Oct 7, 2023
 *      Author:Aly Mustafa
 */
#include "EXTI.h"
#include"STM32F103x6.h"
#include "GPIO.h"

#define AFIO_GPIO_EXTI_Mapping(x)     	( 		(x==GPIOA)?0 :\
												(x==GPIOB)?1 :\
												(x==GPIOC)?2 :\
												(x==GPIOD)?3 : 0 )
void Enable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;

	case 1 :
		NVIC_IRQ7_EXTI1_Enable ;
		break;

	case 2 :
		NVIC_IRQ8_EXTI2_Enable;
		break;

	case 3 :
		NVIC_IRQ9_EXTI3_Enable ;
		break;

	case 4 :
		NVIC_IRQ10_EXTI4_Enable;
		break;

	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_Enable;
		break;

	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_Enable ;
		break;
	}
}

void Disable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;

	case 1 :
		NVIC_IRQ7_EXTI1_Disable ;
		break;

	case 2 :
		NVIC_IRQ8_EXTI2_Disable;
		break;

	case 3 :
		NVIC_IRQ9_EXTI3_Disable ;
		break;

	case 4 :
		NVIC_IRQ10_EXTI4_Disable;
		break;

	case 5 :
	case 6 :
	case 7 :
	case 8 :
	case 9 :
		NVIC_IRQ23_EXTI5_9_Disable;
		break;

	case 10 :
	case 11 :
	case 12 :
	case 13 :
	case 14 :
	case 15 :
		NVIC_IRQ40_EXTI10_15_Disable ;
		break;
	}
}

void (*GP_CallBack_Fn[16])(void);

void Uptade_EXTI(EXTI_Config_t* EXTI_config)
{
	//mapping GPIO to act as AFIO
	GPIO_config_t Pin_Cfg;

	//to make a GPIO pin act as AF INPUT -> Floating INPUT
	Pin_Cfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	Pin_Cfg.GPIO_PinNumber = EXTI_config->EXTI_Pin.GPIO_Pin_Number;
	MCAL_GPIO_Init(EXTI_config->EXTI_Pin.GPIOx, &Pin_Cfg);

	//Routing AFIO to EXTI device
	uint8_t AFIO_EXTICR_Index = (EXTI_config->EXTI_Pin.EXTI_Input_line_Number) / 4 ;
	uint8_t AFIO_EXTICR_Position =  ((EXTI_config->EXTI_Pin.EXTI_Input_line_Number) % 4) * 4;

	//clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |=  ((AFIO_GPIO_EXTI_Mapping(EXTI_config->EXTI_Pin.GPIOx) & 0xF) << AFIO_EXTICR_Position );

	//Trigger configuration
	//Clear Trigger
	EXTI->RTSR &=~ (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	EXTI->FTSR &=~ (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	//Update Trigger
	if (EXTI_config -> Trigger_Case == EXTI_Trigger_RISING){
		EXTI->RTSR |= (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	}
	else if (EXTI_config -> Trigger_Case == EXTI_Trigger_FALLING){
		EXTI->FTSR |= (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	}
	else if (EXTI_config -> Trigger_Case == EXTI_Trigger_FALLINGAndRISING){
		EXTI->RTSR |= (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
		EXTI->FTSR |= (1<< EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	}
	//EXTI & NVIC Enable
	if (EXTI_config -> IRQ_EN == EXTI_IRQ_Enable){
		EXTI->IMR |= (1 <<EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
		Enable_NVIC(EXTI_config->EXTI_Pin.EXTI_Input_line_Number);

	}

	else if (EXTI_config -> IRQ_EN == EXTI_IRQ_Disable){
		EXTI->IMR &= ~(1 <<EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
		Disable_NVIC(EXTI_config->EXTI_Pin.EXTI_Input_line_Number);
	}

	//IRQ_Handling_CallBack_Fn
	GP_CallBack_Fn[EXTI_config->EXTI_Pin.EXTI_Input_line_Number] = EXTI_config->P_IRQ_CallBack;
}
/*
 *================================================================
 * @Fn				-MCAL_EXTI_GPIO_DeInit
 * @brief 			-Reset EXTI
 * @retval 			-none
 * Note				-none
 *=================================================================
 */
void MCAL_EXTI_GPIO_DeInit (){
	//EXTI_Reset_values
	EXTI->IMR   =  0x00000000;
	EXTI->EMR   =  0x00000000;
	EXTI->RTSR  =  0x00000000;
	EXTI->FTSR  =  0x00000000;
	EXTI->SWIER =  0x00000000;
	//rc_w
	EXTI->PR    =  0xffffffff;
	//Disable IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable 	 ;
	NVIC_IRQ7_EXTI1_Disable  	 ;
	NVIC_IRQ8_EXTI2_Disable		 ;
	NVIC_IRQ9_EXTI3_Disable 	 ;
	NVIC_IRQ10_EXTI4_Disable  	 ;
	NVIC_IRQ23_EXTI5_9_Disable 	 ;
	NVIC_IRQ40_EXTI10_15_Disable ;
}
/*
 *================================================================
 * @Fn				- MCAL_EXTI_GPIO_Init
 * @brief 			- This is used to inialize EXTI from specific GPIO PIN and Specify the Mask/Trigger Condition and IRQ CallBack
 * @param [in]		- EXTI_config set by @ref EXTI_define & EXTI_IRQ_define and EXTI_Trigger_define
 * @retval 			- none
 * Note				- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *=================================================================
 */

void MCAL_EXTI_GPIO_Init (EXTI_Config_t* EXTI_config)
{

	Uptade_EXTI(EXTI_config);
}

/*
 *================================================================
 * @Fn				- MCAL_EXTI_GPIO_Update
 * @brief 			- This is used to inialize EXTI from specific GPIO PIN and Specify the Mask/Trigger Condition and IRQ CallBack
 * @param [in]		- EXTI_config set by @ref EXTI_define & EXTI_IRQ_define and EXTI_Trigger_define
 * @retval 			- none
 * Note				- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *=================================================================
 */

void MCAL_EXTI_GPIO_Update (EXTI_Config_t* EXTI_config)
{
	Uptade_EXTI( EXTI_config);

}

/*
 ===========================================================
 ===========================I S R===========================
 ===========================================================
 */

void EXTI0_IRQHandler(){
	EXTI->PR |= (1 << 0);
	GP_CallBack_Fn[0]();
}
void EXTI1_IRQHandler (){
	EXTI->PR |= (1 << 1);
	GP_CallBack_Fn[1]();

}
void EXTI2_IRQHandler (){
	EXTI->PR |= (1 << 2);
	GP_CallBack_Fn[2]();
}
void EXTI3_IRQHandler (){
	EXTI->PR |= (1 << 3);
	GP_CallBack_Fn[3]();
}
void EXTI4_IRQHandler  (){
	EXTI->PR |= (1 << 4);
	GP_CallBack_Fn[4]();
}
void EXTI9_5_IRQHandler(){

	if(EXTI->PR & 1<<5) {EXTI->PR |= (1 << 5);    GP_CallBack_Fn[5](); }
	if(EXTI->PR & 1<<6) {EXTI->PR |= (1 << 6);    GP_CallBack_Fn[6](); }
	if(EXTI->PR & 1<<7) {EXTI->PR |= (1 << 7);    GP_CallBack_Fn[7](); }
	if(EXTI->PR & 1<<8) {EXTI->PR |= (1 << 8);    GP_CallBack_Fn[8](); }
	if(EXTI->PR & 1<<9) {EXTI->PR |= (1 << 9);    GP_CallBack_Fn[9](); }

}
void EXTI15_10_IRQHandler(){
	if(EXTI->PR & 1<<10) {EXTI->PR |= (1 << 10);    GP_CallBack_Fn[10](); }
	if(EXTI->PR & 1<<11) {EXTI->PR |= (1 << 11);    GP_CallBack_Fn[11](); }
	if(EXTI->PR & 1<<12) {EXTI->PR |= (1 << 12);    GP_CallBack_Fn[12](); }
	if(EXTI->PR & 1<<13) {EXTI->PR |= (1 << 13);    GP_CallBack_Fn[13](); }
	if(EXTI->PR & 1<<14) {EXTI->PR |= (1 << 14);    GP_CallBack_Fn[14](); }
	if(EXTI->PR & 1<<15) {EXTI->PR |= (1 << 15);    GP_CallBack_Fn[15](); }
}

