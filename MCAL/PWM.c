/*
 * PWM.c
 *
 *  Created on: 4/12/2023
 *      Author: Aly Mustafa
 */

#include "PWM.h"
TIM_t* get_timer_mapping(GPIO_t* GPIOx ,uint16_t pin)
{
	if (GPIOx == GPIOA)
	{
		if (  (pin >= GPIO_PIN_0) && ( pin < GPIO_PIN_4) )
		{
			RCC_TIM2_CLK_EN();
			return TIM2;
		}
		if ( (pin > GPIO_PIN_5) && ( pin < GPIO_PIN_8) )
		{
			RCC_TIM3_CLK_EN();
			return TIM3;
		}
		if ( (pin >= GPIO_PIN_8) && ( pin < GPIO_PIN_12) )
		{
			RCC_TIM1_CLK_EN();
			return TIM1;
		}
		return 0 ;
	}
	else if (GPIOx == GPIOB)
	{
		if ( pin == GPIO_PIN_0)
		{
			RCC_TIM3_CLK_EN();
			return TIM3;
		}
		return 0;
	}
}

uint8_t get_timer_channel(GPIO_t* GPIOx ,uint16_t pin ,uint8_t mode)

{
	RCC_AFIO_CLK_EN();

	if (mode == compare) {
		GPIO_config_t PIN =  {pin , GPIO_MODE_OUTPUT_AF_PP ,GPIO_SPEED_50M };
		MCAL_GPIO_Init(GPIOx, &PIN);
	}
	else if (mode == capture) {
		GPIO_config_t PIN =  {pin , GPIO_MODE_INPUT_AF ,GPIO_SPEED_50M };
		MCAL_GPIO_Init(GPIOx, &PIN);
	}

	if (GPIOx == GPIOA)
	{
		RCC_GPIOA_CLK_EN();
		if ( (pin == GPIO_PIN_0) || (pin == GPIO_PIN_6)  || (pin == GPIO_PIN_8)){
			return (uint8_t)1;
		}
		if ( (pin == GPIO_PIN_1) || (pin == GPIO_PIN_7)  || (pin == GPIO_PIN_9)){
			return (uint8_t)2;
		}
		if ( (pin == GPIO_PIN_2) || (pin == GPIO_PIN_10)){
			return (uint8_t)3;
		}
		if ( (pin == GPIO_PIN_3) || (pin == GPIO_PIN_11)){
			return (uint8_t)4;
		}
		return (uint8_t)0;
	}
	else if (GPIOx == GPIOB)
	{
		RCC_GPIOB_CLK_EN();
		if ( pin == GPIO_PIN_0){
			return (uint8_t)3;
		}
		if ( pin == GPIO_PIN_1 ){
			return (uint8_t)4;
		}
		return (uint8_t)0;
	}
}
/*
 *================================================================
 * @Fn				- Timer_compare_micro
 * @brief 			- Output compare in micro
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- compare_val
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
void Timer_compare_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , compare );
	tim->PSC  = (72-1);
	tim->ARR  = (arr_val-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 = 0x30;  				//011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
		tim->CCER |= (1<<0); 				//Capture/Compare 1 output enable
		tim->CCR1 = compare_val;			//Set compare Value

		break;
	}
	case 2 :
	{
		tim->CCMR1 = 0x3000; 				//011: Toggle - OC2REF toggles when TIMx_CNT=TIMx_CCR2.
		tim->CCER |= (1<<4);				//Capture/Compare 1 output enable
		tim->CCR2 = compare_val;			//Set compare Value
		break;
	}
	case 3 :
	{
		tim->CCMR2 = 0x30;					//011: Toggle - OC3REF toggles when TIMx_CNT=TIMx_CCR3.
		tim->CCER |= (1<<8);				//Capture/Compare 1 output enable
		tim->CCR3 = compare_val;			//Set compare Value
		break;
	}
	case 4 :
	{
		tim->CCMR2 = 0x3000;				//011: Toggle - OC4REF toggles when TIMx_CNT=TIMx_CCR4.
		tim->CCER |= (1<<12);    			//Capture/Compare 4 output enable
		tim->CCR4 = compare_val; 			//Set compare Value
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}

/*
 *================================================================
 * @Fn				- Timer_compare_milli
 * @brief 			- Output compare in milli
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- compare_val
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
void Timer_compare_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , compare);
	tim->PSC  = (36000-1);
	tim->ARR  = (arr_val*2-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	compare_val *= 2;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x30;  				//011: Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1.
		tim->CCER |= (1<<0); 				//Capture/Compare 1 output enable
		tim->CCR1 = compare_val;			//Set compare Value

		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x3000; 				//011: Toggle - OC2REF toggles when TIMx_CNT=TIMx_CCR2.
		tim->CCER |= (1<<4);				//Capture/Compare 1 output enable
		tim->CCR2 = compare_val;			//Set compare Value
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x30;					//011: Toggle - OC3REF toggles when TIMx_CNT=TIMx_CCR3.
		tim->CCER |= (1<<8);				//Capture/Compare 1 output enable
		tim->CCR3 = compare_val;			//Set compare Value
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x3000;				//011: Toggle - OC4REF toggles when TIMx_CNT=TIMx_CCR4.
		tim->CCER |= (1<<12);    			//Capture/Compare 4 output enable
		tim->CCR4 = compare_val; 			//Set compare Value
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}


/*
 *================================================================
 * @Fn				- Timer_PWM_micro
 * @brief 			- Output PWM in micro
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- compare_val
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
void Timer_PWM_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , compare);
	tim->PSC = (72-1);
	tim->ARR = (arr_val-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x60;  				//110: PWM mode
		tim->CCER |= (1<<0); 				//Capture/Compare 1 output enable
		tim->CCR1 = compare_val;			//Set compare Value

		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x6000; 				//110: PWM mode
		tim->CCER |= (1<<4);				//Capture/Compare 1 output enable
		tim->CCR2 = compare_val;			//Set compare Value
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x60;					//110: PWM mode
		tim->CCER |= (1<<8);				//Capture/Compare 1 output enable
		tim->CCR3 = compare_val;			//Set compare Value
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x6000;				//110: PWM mode .
		tim->CCER |= (1<<12);    			//Capture/Compare 4 output enable
		tim->CCR4 = compare_val; 			//Set compare Value
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}

/*
 *================================================================
 * @Fn				- Timer_PWM_milli
 * @brief 			- Output PWM in milli
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- compare_val
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
void Timer_PWM_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint16_t compare_val )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , compare);
	tim->PSC = (36000-1);
	tim ->CNT = 0;
	tim->ARR = (arr_val*2-1);
	tim->BDTR |=0x8000;

	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x60;  				//110: PWM mode
		tim->CCER |= (1<<0); 				//Capture/Compare 1 output enable
		tim->CCR1 = compare_val*2;			//Set compare Value

		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x6000; 				//110: PWM mode
		tim->CCER |= (1<<4);				//Capture/Compare 1 output enable
		tim->CCR2 = compare_val*2;			//Set compare Value
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x60;					//110: PWM mode
		tim->CCER |= (1<<8);				//Capture/Compare 1 output enable
		tim->CCR3 = compare_val*2;			//Set compare Value
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x6000;				//110: PWM mode
		tim->CCER |= (1<<12);    			//Capture/Compare 4 output enable
		tim->CCR4 = compare_val*2; 			//Set compare Value
		break;
	}
	}

	tim->CR1 |= (1<<0); //Kick Timer
}

/*
 *================================================================
 * @Fn				- Timer_Capture_micro
 * @brief 			- Capture configuration
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- edge
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
/*
void Timer_Capture_micro(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint8_t edge )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , capture);
	tim->PSC  = (72-1);
	tim->ARR  = (arr_val-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x1;  					//01: CC1 channel is configured as input
		tim->CCER |= (1<<0);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<1); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<1);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x100; 					//01: CC2 channel is configured as input
		tim->CCER |= (1<<4);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<5); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<5);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x1;						//01: CC3 channel is configured as input
		tim->CCER |= (1<<8);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<9); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<9);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x100;					//01: CC4 channel is configured as input
		tim->CCER |= (1<<12);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<13); 		//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<13);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}
*/
/*
 *================================================================
 * @Fn				- Timer_Capture_milli
 * @brief 			- Capture configuration
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- arr_val
 * @param [in]		- edge
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
/*void Timer_Capture_milli(GPIO_t* GPIOx , uint16_t pin , uint16_t arr_val , uint8_t edge )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , capture);
	tim->PSC  = (36000-1);
	tim->ARR  = (arr_val*2-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x1;  					//01: CC1 channel is configured as input
		tim->CCER |= (1<<0);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<1); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<1);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x100; 					//01: CC2 channel is configured as input
		tim->CCER |= (1<<4);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<5); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<5);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x1;						//01: CC3 channel is configured as input
		tim->CCER |= (1<<8);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<9); 			//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<9);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x100;					//01: CC4 channel is configured as input
		tim->CCER |= (1<<12);					//capture/compare enable register
		if (edge) tim->CCER |= (1<<13); 		//faling    1: inverted: capture is done on a falling edge
		else tim->CCER &= ~(1<<13);				// RISING   0: non-inverted: capture is done on a rising edge of IC1
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}
*/
/*
 *================================================================
 * @Fn				- Timer_get_Capture_micro
 * @brief 			- get time in micro
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
/*uint16_t Timer_get_Capture_micro (GPIO_t* GPIOx , uint16_t pin )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , capture);
	uint16_t my_PSC = 0;
	my_PSC = tim->PSC;
	uint16_t my_capture = 0;
	switch (channel)
	{
	case 1 : my_capture = (uint16_t)tim->CCR1 ;  break;
	case 2 : my_capture = (uint16_t)tim->CCR2 ;  break;
	case 3 : my_capture = (uint16_t)tim->CCR3 ;  break;
	case 4 : my_capture = (uint16_t)tim->CCR4 ;  break;
	}
	my_capture = my_capture * my_PSC/(72-1);  //convert into time
	return my_capture;
}*/
/*
 *================================================================
 * @Fn				- Timer_get_Capture_micro
 * @brief 			- get time in milli
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
/*uint16_t Timer_get_Capture_milli (GPIO_t* GPIOx , uint16_t pin )
{
	uint16_t my_capture = 0;
	my_capture = Timer_get_Capture_micro(GPIOx , pin) /1000;
	return my_capture;
}*/
