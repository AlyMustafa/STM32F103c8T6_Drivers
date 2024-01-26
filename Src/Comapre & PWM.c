
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO.h"
#include "TIM.h"
#include "PWM.h"
int main(void)
{
Timer_PWM_milli(GPIOB, GPIO_PIN_0, 1000, 250);
Timer_PWM_milli(GPIOA, GPIO_PIN_11, 1000, 100);
Timer_PWM_milli(GPIOA, GPIO_PIN_8, 1000, 750);
	/*
	  while(1)
	{

	}
	 */
		return 0;
}
