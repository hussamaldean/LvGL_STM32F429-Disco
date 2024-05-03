/*
 * LED.c
 *
 *  Created on: Dec 4, 2023
 *      Author: hussamaldean
 */


#include "LED.h"

#include "stm32f4xx.h"

void LEDS_Init(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;

	GPIOG->MODER|=GPIO_MODER_MODE13_0|GPIO_MODER_MODE14_0;
	GPIOG->MODER&=~(GPIO_MODER_MODE13_1|GPIO_MODER_MODE14_1);

}

void LEDSet(LEDsTypedef LED, uint8_t state)
{

	switch (LED)
	{
		case LED3: if(state==1) GPIOG->BSRR=GPIO_BSRR_BS13;
		else GPIOG->BSRR=GPIO_BSRR_BR13;
		break;

		case LED4: if(state==1) GPIOG->BSRR=GPIO_BSRR_BS14;
		else GPIOG->BSRR=GPIO_BSRR_BR14;
		break;

		default : break;

	}

}
