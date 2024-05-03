/*
 * PWM.c
 *
 *  Created on: Dec 4, 2023
 *      Author: hussamaldean
 */

#include "stm32f4xx.h"
#include "PWM.h"

#define TIM2AF 0x01

void PB3_PWM_Init(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;

	GPIOB->MODER|=GPIO_MODER_MODE3_1;
	GPIOB->MODER&=~GPIO_MODER_MODE3_0;

	GPIOB->AFR[0]|=(TIM2AF<<GPIO_AFRL_AFSEL3_Pos);

	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;

	TIM2->PSC=100;
	TIM2->ARR=100;

	TIM2->CCMR1|=TIM_CCMR1_OC2M_2|TIM_CCMR1_OC2M_1;

	TIM2->CCER|=TIM_CCER_CC2E;

	TIM2->CR1|=TIM_CR1_CEN;

}

void PB3_PWM_SetDutyCycle(uint8_t duty)
{

	TIM2->CCR2=duty;

}
