/*
 * Stm32f103c6_GPIO_driver.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Metro
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------

#include "STM32F103x6.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct {
	uint16_t GPIO_PinNumber;  		//specifies the GPIO pins to be configured.
	//This parameter can be a value of @ref GPIO_PIN_define

	uint8_t GPIO_MODE;		  		//specifies the mode of GPIO pin mode to be configured.
	//This parameter can be a value of @ref GPIO_PIN_MODE

	uint8_t GPIO_OUTPUT_SPEED;		//specifies the Speed of GPIO OUTPUT pins to be configured.
	//This parameter can be a value of @ref GPIO_PIN_OUTPUT_Speed

}GPIO_config_t;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Macros Configuration References
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//@ref GPIO_PIN_define
#define GPIO_PIN_0  			((uint16_t)0x0001)
#define GPIO_PIN_1  			((uint16_t)0x0002)
#define GPIO_PIN_2  			((uint16_t)0x0004)
#define GPIO_PIN_3  			((uint16_t)0x0008)
#define GPIO_PIN_4  			((uint16_t)0x0010)
#define GPIO_PIN_5  			((uint16_t)0x0020)
#define GPIO_PIN_6  			((uint16_t)0x0040)
#define GPIO_PIN_7  			((uint16_t)0x0080)
#define GPIO_PIN_8  			((uint16_t)0x0100)
#define GPIO_PIN_9  			((uint16_t)0x0200)
#define GPIO_PIN_10  			((uint16_t)0x0400)
#define GPIO_PIN_11  			((uint16_t)0x0800)
#define GPIO_PIN_12 			((uint16_t)0x1000)
#define GPIO_PIN_13  			((uint16_t)0x2000)
#define GPIO_PIN_14  			((uint16_t)0x4000)
#define GPIO_PIN_15  			((uint16_t)0x8000)

#define GPIO_PIN_ALL  			((uint16_t)0xFFFF)

#define GPIO_PIN_MASK  			0x0000FFFFu

//@ref GPIO_PIN_MODE
/*
00: Analog mode
01: Floating input (reset state)
10: Input with pull-up
11: Input with PULL-DOWN

00: General purpose output push-pull     	-4
01: General purpose output Open-drain       -4
10: Alternate function output Push-pull		-4
11: Alternate function output Open-drain	-4
11: Alternate function INPUT				-4
 */
#define GPIO_MODE_ANALOG  				((uint8_t)0x0000)  //Analog mode
#define GPIO_MODE_INPUT_FLO 			((uint8_t)0x0001)  //Floating input (reset state)
#define GPIO_MODE_INPUT_PU 				((uint8_t)0x0002)  //Input with pull-up
#define GPIO_MODE_INPUT_PD				((uint8_t)0x0003)  //Input with PULL-DOWN
#define GPIO_MODE_OUTPUT_PP  			((uint8_t)0x0004)  //output push-pull
#define GPIO_MODE_OUTPUT_OD  			((uint8_t)0x0005)  //output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP 			((uint8_t)0x0006)  //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD 			((uint8_t)0x0007)  //Alternate function output Open-drain
#define GPIO_MODE_INPUT_AF 				((uint8_t)0x0001)  //AAlternate function INPUT  <<<<<< as GPIO_MODE_INPUT_FLO >>>>>>

//@ref GPIO_PIN_OUTPUT_Speed

/*
00: Input mode (reset state)
01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz.
 */
#define GPIO_INPUT 						((uint8_t)0x0) 		//GENERAL.
#define GPIO_SPEED_10M  				((uint8_t)0x0001) 	//max speed 10 MHz.
#define GPIO_SPEED_2M  					((uint8_t)0x0002) 	//max speed 2 MHz.
#define GPIO_SPEED_50M  				((uint8_t)0x0003)	//max speed 50 MHz.

//@ref GPIO_PIN_state
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET 		0


//@ref GPIO_lock_state
#define GPIO_RETURN_LOCK_Enabled		1
#define GPIO_RETURN_LOCK_ERROR 			0



/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
//initialization APIs
void MCAL_GPIO_Init (GPIO_t* GPIOx , GPIO_config_t* PinConfig );
void MCAL_GPIO_DeInit (GPIO_t* GPIOx);

//READ APIs
uint8_t MCAL_GPIO_ReadPin (GPIO_t* GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort (GPIO_t* GPIOx);

//WRITE APIs
void MCAL_GPIO_WritePin (GPIO_t* GPIOx , uint16_t PinNumber , uint8_t value);
void MCAL_GPIO_WritePort (GPIO_t* GPIOx , uint16_t value );

void MCAL_GPIO_TogglePin (GPIO_t* GPIOx , uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin (GPIO_t* GPIOx , uint16_t PinNumber);

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
