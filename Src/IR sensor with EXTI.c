
/**
 ******************************************************************************
 * file           : main.c
 * Board		  :STM32f103c6_Cortex-M3
 * author         : Aly_Mustafa_Enaya
 * brief          : Main program body
 * Date			  : 6/11/2023
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103x6.h"
#include "GPIO.h"
#include "EXTI.h"

void EXT0_CallBack() //Call Back Fn
{
	Led_on();
}

void wait_ms(int x){

	int i,j;
	for(i=0 ; i<j ; i++){
		for(j=0 ; j<255 ; j++);
	}
}

void Led_on()
{
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);

}
void Led_off()
{
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);

}

int main(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	GPIO_config_t PA1 =  {GPIO_PIN_1 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t PA2 =  {GPIO_PIN_2 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t PA3 =  {GPIO_PIN_3 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };

	EXTI_Config_t EXT_cnfg = { EXTI0PB0, EXTI_IRQ_Enable , EXTI_Trigger_FALLING , EXT0_CallBack };

	MCAL_EXTI_GPIO_Init (&EXT_cnfg);

	MCAL_GPIO_Init(GPIOA, &PA1);
	MCAL_GPIO_Init(GPIOA, &PA2);
	MCAL_GPIO_Init(GPIOA, &PA3);

	Led_off();
	while(1)
	{
		if ( (MCAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 1) )
		{
			Led_off();
		}


	}
}