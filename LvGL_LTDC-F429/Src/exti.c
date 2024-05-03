/*
 * exti.c
 *
 *  Created on: Nov 1, 2023
 *      Author: hussamaldean
 */


#include "exti.h"

#include "stm32f4xx.h"

void PA15_EXTI_Init(void)
{

	__disable_irq();

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER&=~GPIO_MODER_MODE15;

	RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[3]|=SYSCFG_EXTICR4_EXTI15_PA;

	EXTI->IMR |=EXTI_IMR_IM15;

	EXTI->RTSR |=EXTI_RTSR_TR15;

	NVIC_EnableIRQ(EXTI15_10_IRQn);

	__enable_irq();

}
