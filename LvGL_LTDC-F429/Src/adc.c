/*
 * adc.c
 *
 *  Created on: Dec 4, 2023
 *      Author: hussamaldean
 */
#include "stm32f4xx.h"
#include "adc.h"

#define CH5	0x05


void PA5_ADC_Init(void)
{

	RCC->APB2ENR|=RCC_APB2ENR_ADC1EN;

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;

	GPIOA->MODER|=GPIO_MODER_MODE5;

	ADC1->SQR3|=(CH5<<ADC_SQR3_SQ1_Pos);

	ADC1->CR2=ADC_CR2_CONT;

	ADC1->CR2|=ADC_CR2_ADON;

	ADC1->CR2|=ADC_CR2_SWSTART;

}

uint16_t PA5_ADC_Value(void)
{
	/*Wait for conversion to be complete*/
	while(!(ADC1->SR & ADC_SR_EOC)){}

	/*Read converted result*/
	return (ADC1->DR);
}
