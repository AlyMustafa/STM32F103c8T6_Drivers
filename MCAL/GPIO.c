/*
 * Stm32f103c6_GPIO_driver.c
 *
 *  Created on: Sep 15, 2023
 *      Author: Aly Enaya
 */
#include "GPIO.h"
uint16_t GetPinPostion(uint16_t Pin_Number)
{
	switch (Pin_Number)
	{
	case GPIO_PIN_0:
		return 0 ;
		break;

	case GPIO_PIN_1:
		return 4 ;
		break;

	case GPIO_PIN_2:
		return 8 ;
		break;

	case GPIO_PIN_3:
		return 12 ;
		break;

	case GPIO_PIN_4:
		return 16 ;
		break;

	case GPIO_PIN_5:
		return 20 ;
		break;

	case GPIO_PIN_6:
		return 24 ;
		break;

	case GPIO_PIN_7:
		return 28 ;
		break;

	case GPIO_PIN_8:
		return 0 ;

	case GPIO_PIN_9:
		return 4 ;
		break;

	case GPIO_PIN_10:
		return 8 ;
		break;

	case GPIO_PIN_11:
		return 12 ;
		break;

	case GPIO_PIN_12:
		return 16 ;
		break;

	case GPIO_PIN_13:
		return 20 ;
		break;

	case GPIO_PIN_14:
		return 24 ;
		break;

	case GPIO_PIN_15:
		return 28 ;
		break;
	}
	return 0;
}
/*
 *================================================================
 * @Fn				-MCAL_GPIO_Init
 * @brief 			- Initialization GPIOx Port (A -> G)
 * @param [in]		- Pointer GPIOx (A -> G)
 * @param [in]		- Pointer PinConfig
 * @retval 		    - none
 * Note			    - Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *=================================================================
 */
void MCAL_GPIO_Init (GPIO_t* GPIOx , GPIO_config_t* PinConfig)	{
	//Port configuration register low (GPIOx_CRL) from 0>>>7
	//Port configuration register low (GPIOx_CRH) from 8>>>15
	volatile uint32_t* configregister = NULL;
	uint8_t pin_config = 0;

	configregister = ( (PinConfig->GPIO_PinNumber) < GPIO_PIN_8 )? (&GPIOx->CRL): (&GPIOx->CRH);
	//clear CNF & MODE
	(*configregister) &= ~(0xF << ( GetPinPostion (PinConfig->GPIO_PinNumber) ) );

	//if Pin is OUTPUT
	if ( ((PinConfig -> GPIO_MODE) == GPIO_MODE_OUTPUT_PP ) || ((PinConfig -> GPIO_MODE) == GPIO_MODE_OUTPUT_OD ) || ((PinConfig -> GPIO_MODE) == GPIO_MODE_OUTPUT_AF_OD ) || ((PinConfig -> GPIO_MODE) == GPIO_MODE_OUTPUT_AF_PP )   )
	{
		//set CNF & MODE
		pin_config = (( ((PinConfig -> GPIO_MODE - 4) << 2) |  PinConfig -> GPIO_OUTPUT_SPEED ) & 0xF);
		(*configregister) |= ( (pin_config) << ( GetPinPostion (PinConfig->GPIO_PinNumber) ) );
	}

	//if Pin is INPUT
	else
	{
		if ( (PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_PD) || (PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_PU) || (PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_AF) || (PinConfig -> GPIO_MODE == GPIO_MODE_ANALOG) )
		{
			//INPUT PULL_UP & PULL_DOWN
			if ( PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_PU ) //PULL_UP
			{
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
			}
			else if ( PinConfig -> GPIO_MODE == GPIO_MODE_INPUT_PD ) //PULL_DOWN
			{
				GPIOx->ODR &= PinConfig->GPIO_PinNumber;
			}
			pin_config = ( (((PinConfig -> GPIO_MODE ) << 2) | GPIO_INPUT ) & 0xF);
			(*configregister) |= ( (pin_config) << ( GetPinPostion (PinConfig->GPIO_PinNumber) ) );
		}
	}
}
/*
 *================================================================
 * @Fn				- MCAL_GPIO_DeInit
 * @brief 			- RESET GPIOx Port (A -> G)
 * @param [in]		- Pointer GPIOx (A -> G)
 * @retval 		    - none
 * Note			    - Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *=================================================================
 */

void MCAL_GPIO_DeInit (GPIO_t* GPIOx)
{
	if(GPIOx == GPIOA )
	{
		RCC_GPIOA_CLK_RESET();
	}
	else if(GPIOx == GPIOB )
	{
		RCC_GPIOB_CLK_RESET();
	}
	else if(GPIOx == GPIOC )
	{
		RCC_GPIOC_CLK_RESET();
	}
	else if(GPIOx == GPIOD )
	{
		RCC_GPIOD_CLK_RESET();
	}
	else if(GPIOx == GPIOE )
	{
		RCC_GPIOE_CLK_RESET();
	}
	/*
	else if(GPIOx == GPIOF )
	{
		RCC -> APB2RSTR |= (1<<7);
		RCC -> APB2RSTR &= ~(1<<7);
	}
*/
}
/*
 *================================================================
 * @Fn				- MCAL_GPIO_ReadPin
 * @brief 			- Read the value from specific PIN in specific PORT
 * @param [in]		- Pointer GPIOx (A -> G)
 * @param [in]		- PinNumber
 * @retval 		    - none
 * Note			    - Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
 *=================================================================
 */uint8_t MCAL_GPIO_ReadPin (GPIO_t* GPIOx , uint16_t PinNumber)
 {
	 uint8_t pin_val=0;

	 if ( (GPIOx->IDR & PinNumber) != (uint32_t)GPIO_PIN_RESET )
	 {
		 pin_val = 1;
	 }
	 else
	 {
		 pin_val = 0;
	 }
	 return pin_val;

 }
 /*
  *================================================================
  * @Fn				- MCAL_GPIO_ReadPort
  * @brief 			- Read the value in PORTx
  * @param [in]		- Pointer GPIOx (A -> G)
  * @retval 		- none
  * Note			- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
  *=================================================================
  */
 uint16_t MCAL_GPIO_ReadPort (GPIO_t* GPIOx)
 {
	 uint16_t port_val;
	 port_val = (uint16_t)GPIOx ->IDR;
	 return port_val;
 }

 //WRITE APIs

 /*
   *================================================================
   * @Fn			- MCAL_GPIO_WritePin
   * @brief 		- Write the value in specific PIN
   * @param [in]	- Pointer GPIOx (A -> G)
   * @param [in]	- PinNumber
   * @param [in]	- value
   * @retval 		- none
   * Note			- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
   					  But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
   				 	  Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
   *=================================================================
   */
 void MCAL_GPIO_WritePin (GPIO_t* GPIOx , uint16_t PinNumber , uint8_t value)
 {

	 if (value != GPIO_PIN_RESET)
	 {
		 /*
		 Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Set the corresponding ODRx bit*/
		 GPIOx -> ODR |= (uint16_t)PinNumber;
		 //BSRR this register his job is that ---> to set & reset any PIN in any Port without to write on ODR register
		 }
	 else
	 {
		 /*Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		These bits are write-only and can be accessed in Word mode only.
		0: No action on the corresponding ODRx bit
		1: Reset the corresponding ODRx bit*/
		 GPIOx -> ODR &= ~ (uint16_t)PinNumber;
	 }

 }

 /*
  *================================================================
  * @Fn				- MCAL_GPIO_WritePort
  * @brief 			- Write specific value on specific PORTx
  * @param [in]		- Pointer GPIOx (A -> G)
  * @param [in]		- value
  * @retval 		- none
  * Note			- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					 But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	 Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
  *=================================================================
  */
 void MCAL_GPIO_WritePort (GPIO_t* GPIOx , uint16_t value )
 {
	 GPIOx -> ODR = (uint32_t)value;
 }

 /*
  *================================================================
  * @Fn				- MCAL_GPIO_TogglePin
  * @brief 			- toggle specific PIN 0 / 1
  * @param [in]		- Pointer GPIOx (A -> G)
  * @param [in]		- PinNumber
  * @retval 		- none
  * Note			- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					 But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	 Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
  *=================================================================
  */
 void MCAL_GPIO_TogglePin (GPIO_t* GPIOx , uint16_t PinNumber)
 {
	 GPIOx -> ODR ^= PinNumber;
 }
 /*
  *================================================================
  * @Fn				- MCAL_GPIO_LockPin
  * @brief 			- Lock specific PIN do prevent any value to be written on this PIN
  * @param [in]		- Pointer GPIOx (A -> G)
  * @param [in]		- PinNumber
  * @retval 		- none
  * Note			- Stm32F103c6 MCU has GPIO A,B,C,D,E Modules
  					 But LQFP48 has only GPIO A,B and Part of C/D exported as external pins from MCU,
  				 	 Also mandatory to Enable RCC clock for AFIO and the corresponding GPIO
  *=================================================================
  */

 uint8_t MCAL_GPIO_LockPin (GPIO_t* GPIOx , uint16_t PinNumber)
 {
	 /*
	 Bit 16 LCKK[16]: Lock key
This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
0: Port configuration lock key not active
1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
LOCK key writing sequence:
Write 1
Write 0
Write 1
Read 0
Read 1 (this read is optional but confirms that the lock is active)
Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
Any error in the lock sequence will abort the lock.
Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
These bits are read write but can only be written when the LCKK bit is 0.
0: Port configuration not locked
1: Port configuration locked.

	  */
	 //set  LCKK[16]
	 volatile uint32_t temp = 1<<16;
	 temp |= PinNumber;
	 //Write 1
	 GPIOx -> LCKR = temp;
	 //Write 0
	 GPIOx -> LCKR = PinNumber;
	 //Write 1
	 GPIOx -> LCKR = temp;

	 temp = GPIOx -> LCKR;
	 //read
	 if ( (uint32_t)( GPIOx -> LCKR & 1<<16 ))
	 {
		 return GPIO_RETURN_LOCK_Enabled;
	 }
	 else
		 return GPIO_RETURN_LOCK_ERROR;
 }
