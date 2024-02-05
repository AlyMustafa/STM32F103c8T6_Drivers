
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO.h"
#include "TIM.h"
#include "PWM.h"

int main(void)
{
	
uint16_t mycapture = 0;
Timer_PWM_milli(GPIOA, GPIO_PIN_10, 1000, 300);
Timer_Capture_milli(GPIOA, GPIO_PIN_11, 1000, RISING);

	  while(1)
	{
		mycapture = Timer_get_Capture_milli(GPIOA, GPIO_PIN_11);
	}

return 0;
}
