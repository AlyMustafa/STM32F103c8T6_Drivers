/*
 * Stm32f103c6_GPIO_driver.c
 * Created on: Sep 15, 2023
 * Author: Ali Mustafa
 */

#include "TIM.h"
/*=========>  Enable/Disable NVIC  <=========*/
void Enable_NVIC_TIM(uint8_t timerType)
{
	TIM_t* tim;
	switch(timerType)
	{
	case 1: tim = TIM1; NVIC_IRQ25_TIM1_Enable; break;
	case 2: tim = TIM2; NVIC_IRQ28_TIM2_Enable; break;
	case 3: tim = TIM3; NVIC_IRQ29_TIM3_Enable; break;
	case 4: tim = TIM4; NVIC_IRQ30_TIM4_Enable; break;

	}
}
void Disable_NVIC_TIM(uint8_t timerType)
{

	TIM_t* tim;
	switch(timerType)
	{
	case 1: tim = TIM1; NVIC_IRQ25_TIM1_Disable; break;
	case 2: tim = TIM2; NVIC_IRQ28_TIM2_Disable; break;
	case 3: tim = TIM3; NVIC_IRQ29_TIM3_Disable; break;
	case 4: tim = TIM4; NVIC_IRQ30_TIM4_Disable; break;
	}
}


void (*GP_CallBack_TIM[4])(void);  //Global pointer to callBack_fn which will be written in application layer

/*=========>  IRQ Handler  <=========*/

void TIM1_UP_IRQHandler(){          			/* TIM1 Update interrupt                            */
GP_CallBack_TIM[0]();
}

void TIM2_IRQHandler(){          				/* TIM2 Update interrupt                            */
	GP_CallBack_TIM[1]();
}
void TIM3_IRQHandler(){          				/* TIM3 Update interrupt                            */
	GP_CallBack_TIM[2]();
}
void TIM4_IRQHandler(){          				/* TIM4 Update interrupt                            */
	GP_CallBack_TIM[3]();
}

TIM_t* get_timer (uint8_t timerType)
{
	TIM_t* tim;
	switch (timerType)
	{
	case 1 : tim = TIM1; RCC_TIM1_CLK_EN();  break;
	case 2 : tim = TIM2; RCC_TIM2_CLK_EN();  break;
	case 3 : tim = TIM3; RCC_TIM3_CLK_EN();  break;
	case 4 : tim = TIM4; RCC_TIM4_CLK_EN();  break;
	default :tim = TIM4; RCC_TIM4_CLK_EN();  break;
	}
	return tim ;
}


/*
 *================================================================
 * @Fn				-T_Start_micros
 * @brief 			- Start the Timer with micro time
 * @param [in]		- timerType
 * @param [in]		- micros
 * @retval 		    - none
 * Note			    - Stm32F103c6 MCU has TIM 1,2,3,4
 * 					it is preferred to use tim->ARR =( micros-3) because of
 * 					the time will be taken for initialization some registers
 * 					and be more accurate

 *=================================================================
 */
TIM_t* T_Start_micros (uint8_t timerType , uint16_t micros )
{

	TIM_t* tim = get_timer(timerType);
	uint32_t Prescaler = (72-1) ;
	//set Counter register 0
	tim->CNT = 0;
	//set up the prescaler (72-1) to make one pulse equal 1 micro sec
	tim->PSC = Prescaler;
	//initialize the Auto reload register "the value where the timer will be stopped"
	tim->ARR =( micros-3);
	//kick the counter to start
	tim->CR1 = 0x1;
	return tim;
}
/*
 *================================================================
 * @Fn				-T_Start_millis
 * @brief 			- Start the Timer with millie time
 * @param [in]		- timerType
 * @param [in]		- millis
 * @retval 		    - none
 * Note			    - Stm32F103c6 MCU has TIM 1,2,3,4
 * 					it is preferred to use tim->ARR =( micros-3) because of
 * 					the time will be taken for initialization some registers
 * 					and be more accurate

 *=================================================================
 */
TIM_t* T_Start_millis (uint8_t timerType, uint16_t millis)
{
	TIM_t* tim = get_timer(timerType);
	uint32_t Prescaler = (36000-1) ;
	//set Counter register 0
	tim->CNT = 0;
	//set up the prescaler (72-1) to make one pulse equal 1 micro sec
	tim->PSC = Prescaler;
	//initialize the Auto reload register "the value where the timer will be stopped"
	tim->ARR =( millis*2);
	//kick the counter to start
	tim->CR1 = 0x1;
	return tim;
}

/*
 *================================================================
 * @Fn				- Tget_time_micros
 * @brief 			- get the time in micro
 * @param [in]		- timerType
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */

uint16_t Tget_time_micros (uint8_t timerType)
{
	TIM_t* tim = get_timer(timerType);
	uint16_t myTime = ( (tim->PSC) * (tim->CNT) )/(72-1) ;
	return myTime;
}

/*
 *================================================================
 * @Fn				- Tget_time_millis
 * @brief 			- get the time in millie
 * @param [in]		- timerType
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */

uint16_t Tget_time_millis (uint8_t timerType)
{
	uint16_t myTime =   Tget_time_micros (timerType) / 1000 ;
	return myTime;
}

/*
 *================================================================
 * @Fn				- TDelay_Micro
 * @brief 			- delay using timer withe micro time
 * @param [in]		- timerType
 * @param [in]		- micros
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */
void TDelay_Micro(uint8_t timerType , uint16_t micros)
{
	TIM_t* tim = T_Start_micros(timerType , micros );
	//kick the counter to start and make it OPM mode
	tim->CR1 = 0x9;
	//wait state
	while(tim->CR1 & 1)
	{}
}

/*
 *================================================================
 * @Fn				- TDelay_Milli
 * @brief 			- delay using timer withe millie time
 * @param [in]		- timerType
 * @param [in]		- Millis
 * @retval 		    - none
 * Note			    - none

 *=================================================================
 */
void TDelay_Milli(uint8_t timerType , uint16_t Millis)
{
	int i =0;
	for (i ; i<Millis ; i++)
	{
		TDelay_Micro(timerType, 1000);
	}
}
/*
 *================================================================
 * @Fn				- TDelay_Micros
 * @brief 			- delay using timer withe micro time
 * @param [in]		- micros
 * @retval 		    - none
 * Note			    - it is preferred to use delay function directly with TIM4
 *  				because it connected with pins where other pins do not connected

 *=================================================================
 */

void TDelay_Micros(uint16_t micros)
{
	TDelay_Micro(T4 , micros);
}
/*
 *================================================================
 * @Fn				- TDelay_Millis
 * @brief 			- delay using timer withe millie time
 * @param [in]		- Millis
 * @retval 		    - none
 * Note			    - it is preferred to use delay function directly with TIM4
 *  				because it connected with pins where other pins do not connected

 *=================================================================
 */
void TDelay_Millis(uint16_t Millis)
{
	TDelay_Milli(T4 , Millis);
}

/*
 *================================================================
 * @Fn				- T_irq_micro_start
 * @brief 			- start normal timer in micro time with Interrupt when CNT reaches ARR
 * @param [in]		- timerType
 * @param [in]		- micros
 * @param [in]		- (Pointer to Call back fn ) --->  void (* P_T_IRQ_CallBack)(void)
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */

void T_irq_micro_start(uint8_t timerType, uint16_t micros , void (* P_T_IRQ_CallBack)(void))
{
	TIM_t* tim = T_Start_micros(timerType ,micros );
	tim->DIER |= 1<<0;
	Enable_NVIC_TIM(timerType);
	GP_CallBack_TIM[timerType-1] = P_T_IRQ_CallBack;
}

/*
 *================================================================
 * @Fn				- T_irq_millis_start
 * @brief 			- start normal timer in millie time with Interrupt when CNT reaches ARR
 * @param [in]		- timerType
 * @param [in]		- Millis
 * @param [in]		- (Pointer to Call back fn ) --->  void (* P_T_IRQ_CallBack)(void)
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */

void T_irq_millis_start(uint8_t timerType, uint16_t millis , void (* P_T_IRQ_CallBack)(void))
{
	TIM_t* tim = T_Start_millis(timerType ,millis );
	tim->DIER |= 1<<0;
	Enable_NVIC_TIM(timerType);
	GP_CallBack_TIM[timerType-1] = P_T_IRQ_CallBack;
}

/*
 *================================================================
 * @Fn				- TClear_irq_Flag
 * @brief 			- clear the SR register to clear Interrupt request Pending
 * @param [in]		- timerType
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */

void TClear_irq_Flag(uint8_t timerType)
{
	TIM_t* tim = get_timer(timerType);
	tim->SR &= ~(1<<0);
}

/*
 *================================================================
 * @Fn				- T_irq_stop
 * @brief 			- Disabling the Interrupt feature in timer by clear the DIER register
 * @param [in]		- timerType
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */

void T_irq_stop(uint8_t timerType)
{
	TIM_t* tim = get_timer(timerType);
	tim->DIER &= ~(1<<0);
	Disable_NVIC_TIM(timerType);
}

/*
 *================================================================
 * @Fn				- T_Stop_Timer
 * @brief 			- Disabling the timer and its clock
 * @param [in]		- timerType
 * @retval 		    - none
 * Note			    - none
 *=================================================================
 */

void T_Stop_Timer (uint8_t timerType)
{
	TIM_t* tim = get_timer(timerType);
	tim->CR1 = 0;
	T_irq_stop(timerType);
	//Disable the CLK
	switch (timerType)
	{
	case 1 : tim = TIM1; RCC_TIM1_CLK_DIS();  break;
	case 2 : tim = TIM2; RCC_TIM2_CLK_DIS();  break;
	case 3 : tim = TIM3; RCC_TIM3_CLK_DIS();  break;
	case 4 : tim = TIM4; RCC_TIM4_CLK_DIS();  break;
	default :tim = TIM4; RCC_TIM4_CLK_DIS();  break;
	}
}
