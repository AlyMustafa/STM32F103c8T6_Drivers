
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO.h"
#include "TIM.h"

void TIM1_CallBack(void);
int main(void)
{
	RCC_GPIOB_CLK_EN();

	GPIO_config_t x1 =  {GPIO_PIN_1 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t x3 =  {GPIO_PIN_5 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	MCAL_GPIO_Init(GPIOB, &x1);
	MCAL_GPIO_Init(GPIOB, &x3);
	T_irq_millis_start(T1,500 ,TIM1_CallBack);
	
	while(1)
	{
		TDelay_Millis(500);
		MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
	}
	
}

void TIM1_CallBack()
{
	TClear_irq_Flag(T1);
	MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
}