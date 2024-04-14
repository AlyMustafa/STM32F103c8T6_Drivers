
#include "PWM.h"
#include "dcmotor.h"

/*
 *================================================================
 * @Fn				- Servo_Write
 * @brief 			- get the servo in specific angle by PWM
 * @param [in]		- Pointer (GPIO_t* GPIOx)
 * @param [in]		- pin
 * @param [in]		- Angle
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */
void Dc_Motor_PWM(GPIO_t* GPIOx , uint16_t pin , uint16_t duty )
{
	TIM_t* tim = get_timer_mapping(GPIOx , pin);
	uint8_t channel = get_timer_channel(GPIOx , pin , compare);
	tim->PSC = 36-1;  
	tim->ARR = (100-1);
	tim ->CNT = 0;
	tim->BDTR |=0x8000;
	switch (channel)
	{
	case 1 :
	{
		tim->CCMR1 |= 0x60;  				//110: PWM mode
		tim->CCER |= (1<<0); 				//Capture/Compare 1 output enable
		tim->CCR1 =  duty;//minPWM+(Angle/maxAngle)*(maxPWM-minPWM)

		break;
	}
	case 2 :
	{
		tim->CCMR1 |= 0x6000; 				//110: PWM mode
		tim->CCER |= (1<<4);				//Capture/Compare 1 output enable
		tim->CCR2 =  duty;//minPWM+(Angle/maxAngle)*(maxPWM-minPWM)
		break;
	}
	case 3 :
	{
		tim->CCMR2 |= 0x60;					//110: PWM mode
		tim->CCER |= (1<<8);				//Capture/Compare 1 output enable
		tim->CCR3 = duty;//minPWM+(Angle/maxAngle)*(maxPWM-minPWM)
		break;
	}
	case 4 :
	{
		tim->CCMR2 |= 0x6000;				//110: PWM mode .
		tim->CCER |= (1<<12);    			//Capture/Compare 4 output enable
		tim->CCR4 =  duty;//minPWM+(Angle/maxAngle)*(maxPWM-minPWM)
		break;
	}
	}
	tim->CR1 |= (1<<0); //Kick Timer
}