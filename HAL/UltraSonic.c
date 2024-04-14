
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "UltraSonic.h"



/*
 *================================================================
 * @Fn				- UltraSonic_init
 * @brief 			- Mapping the sensor to specific PORT
 * @param [in]		- none
 * @param [in]		- none
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */
 
void UltraSonic_init()
{
	GPIO_config_t Trig =  {GPIO_PIN_0 , GPIO_MODE_OUTPUT_PP ,GPIO_SPEED_10M };
	GPIO_config_t echo =  {GPIO_PIN_1 , GPIO_MODE_INPUT_FLO ,GPIO_INPUT };

	MCAL_GPIO_Init(GPIOA, &Trig);
	MCAL_GPIO_Init(GPIOA, &echo);
}
/*
 *================================================================
 * @Fn				- Ultra_get_distance
 * @brief 			- get the distance
 * @param [in]		- none
 * @param [in]		- none
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */

uint32_t Ultra_get_distance()
{
	int my_distance=0;
	  while(1)
	{
		MCAL_GPIO_WritePin(GPIOA ,GPIO_PIN_0 ,1); //Trig
		TDelay_Micros(10);
		MCAL_GPIO_WritePin(GPIOA ,GPIO_PIN_0 ,0);

		while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == 0) //wait echo
		{}
			T_Start_micros(T4,65000);
			while(MCAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)) //wait
		{}
			my_distance = Tget_time_micros(T4)/58;
			TDelay_Millis(70);
			
			return my_distance;
	}		
}