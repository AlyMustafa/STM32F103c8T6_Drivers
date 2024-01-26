
/**
 ******************************************************************************
 * file           : main.c
 * Board		  :STM32f103c6_Cortex-M3
 * author         : Aly_Mustafa_Enaya
 * brief          : Main program body
 * Date			  : 25/8/2023
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "STM32F103x6.h"
#include "GPIO.h"


void wait_ms(int x){

	int i,j;
	for(i=0 ; i<j ; i++){
		for(j=0 ; j<255 ; j++);
	}
}

int main(void)
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	GPIO_config_t PB2 =  {GPIO_PIN_1 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t PB12 =  {GPIO_PIN_12 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	MCAL_GPIO_Init(GPIOB, &PB2 );
	MCAL_GPIO_Init(GPIOB, &PB12 );


	while(1)
	{
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
		wait_ms(1);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);

		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
		wait_ms(1);
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);

	}
}
