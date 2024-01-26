/*
 * STM32F103x6.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Aly Enaya
 */
#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------
//#include "stdio.h"

#include "Platform_Types.h"
#include "RCC.h"
#include "NVIC.h"




//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*Base addresses for Memories-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define FLASH_Memory_BASE 						0x08000000UL
#define SYSTEM_Memory_BASE 						0x1FFFF000UL
#define SRAM_Memory_BASE 						0x20000000UL
#define Peripherals_BASE 						0x40000000UL
#define CortexM3_Internal_Peripherals  			0xE0000000UL
//NVIC addresses
#define NVIC_BASE_Address						0xE000E100UL
#define NVIC_ISER0								(*( vuint32_t *)(NVIC_BASE_Address + 0x000))
#define NVIC_ISER1								(*( vuint32_t *)(NVIC_BASE_Address + 0x004))
#define NVIC_ISER2								(*( vuint32_t *)(NVIC_BASE_Address + 0x008))
#define NVIC_ICER0								(*( vuint32_t *)(NVIC_BASE_Address + 0x080))
#define NVIC_ICER1								(*( vuint32_t *)(NVIC_BASE_Address + 0x084))
#define NVIC_ICER2								(*( vuint32_t *)(NVIC_BASE_Address + 0x088))

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*Base addresses for BUS Peripheral-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define AHB_BASE_Address 						0x40018000UL
#define APB1_BASE_Address 						0x40000000UL
#define APB2_BASE_Address 						0x40010000UL
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*Base addresses for APB2 Bus-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//GPIO
//A,B fully included in LQFP48 Package
#define GPIOA_BASE    				(Peripherals_BASE + 0x00010800UL)
#define GPIOB_BASE    				(Peripherals_BASE + 0x00010C00UL)
//C,D Partial included in LQFP48 Package
#define GPIOC_BASE    				(Peripherals_BASE + 0x00011000UL)
#define GPIOD_BASE    				(Peripherals_BASE + 0x00011400UL)
//E,F,G not included in LQFP48 Package
#define GPIOE_BASE    				(Peripherals_BASE + 0x00011800UL)
#define GPIOF_BASE    				(Peripherals_BASE + 0x00011C00UL)
#define GPIOG_BASE    				(Peripherals_BASE + 0x00012000UL)
//EXTI
#define EXTI_BASE    				(Peripherals_BASE + 0x00010400UL)
//AFIO
#define AFIO_BASE    				(Peripherals_BASE + 0x00010000UL)
//TIM1
#define TIM1_BASE    				( 0x40012C00UL )

//-------------------------------------------------------------------------
//Base addresses for APB1 Bus
//-------------------------------------------------------------------------
#define TIM2_BASE    				( 0x40000000UL )
#define TIM3_BASE    				( 0x40000400UL )
#define TIM4_BASE    				( 0x40000800UL )
//-------------------------------------------------------------------------
//Base addresses for AHB Bus
//-------------------------------------------------------------------------
#define RCC_BASE    							(Peripherals_BASE + 0x00021000UL)

//-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*- Peripheral Register-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//RCC
typedef struct
{
	vuint32_t CR;
	vuint32_t CFGR;
	vuint32_t CIR;
	vuint32_t APB2RSTR;
	vuint32_t APB1RSTR;
	vuint32_t AHBENR;
	vuint32_t APB2ENR;
	vuint32_t APB1ENR;
	vuint32_t BDCR;
	vuint32_t CSR;
}RCC_t;

//GPIO
typedef struct
{
	vuint32_t CRL;
	vuint32_t CRH;
	vuint32_t IDR;
	vuint32_t ODR;
	vuint32_t BSRR;
	vuint32_t BRR;
	vuint32_t LCKR;
}GPIO_t;

//AFIO
typedef struct
{
	vuint32_t EVCR;
	vuint32_t MAPR;
	vuint32_t EXTICR[4];
	vuint32_t Reserved;
	vuint32_t MAPR2;
}AFIO_t;

//EXTI
typedef struct
{
	vuint32_t IMR;
	vuint32_t EMR;
	vuint32_t RTSR;
	vuint32_t FTSR;
	vuint32_t SWIER;
	vuint32_t PR;
}EXTI_t;

// Timers
typedef struct
{
	vuint32_t CR1;
	vuint32_t CR2;
	vuint32_t SMCR;
	vuint32_t DIER;
	vuint32_t SR;
	vuint32_t EGR;
	vuint32_t CCMR1;
	vuint32_t CCMR2;
	vuint32_t CCER;
	vuint32_t CNT;
	vuint32_t PSC;
	vuint32_t ARR;
	vuint32_t RCR;
	vuint32_t CCR1;
	vuint32_t CCR2;
	vuint32_t CCR3;
	vuint32_t CCR4;
	vuint32_t BDTR;
	vuint32_t DCR;
	vuint32_t DMAR;
}TIM_t;


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*Peripheral Instants-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

//GPIO
#define GPIOA 	((GPIO_t*)GPIOA_BASE)
#define GPIOB 	((GPIO_t*)GPIOB_BASE)
#define GPIOC 	((GPIO_t*)GPIOC_BASE)
#define GPIOD 	((GPIO_t*)GPIOD_BASE)
#define GPIOE 	((GPIO_t*)GPIOE_BASE)
#define GPIOF 	((GPIO_t*)GPIOF_BASE)
#define GPIOG 	((GPIO_t*)GPIOG_BASE)

//RCC
#define RCC 	( (RCC_t*)RCC_BASE )

//AFIO
#define AFIO 	((AFIO_t*)AFIO_BASE)

//EXTI
#define EXTI 	((EXTI_t*)EXTI_BASE)

//Timers
#define TIM1 	((TIM_t*)TIM1_BASE)
#define TIM2 	((TIM_t*)TIM2_BASE)
#define TIM3 	((TIM_t*)TIM3_BASE)
#define TIM4 	((TIM_t*)TIM4_BASE)
#endif /* INC_STM32F103X6_H_ */
