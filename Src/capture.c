
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
Timer_PWM_micro(GPIOA, GPIO_PIN_10, 	50000, 20000);
Timer_Capture_micro(GPIOA, GPIO_PIN_11, 50000, RISING);

	  while(1)
	{
		mycapture = Timer_get_Capture_micro(GPIOA, GPIO_PIN_10);
	}

return 0;
}