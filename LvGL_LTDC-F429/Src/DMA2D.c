/*
 * DMA2D.c
 *
 *  Created on: Nov 19, 2023
 *      Author: hussamaldean
 */


#include "DMA2D.h"
#include "stm32f4xx.h"

void DMA2_Init(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_DMA2DEN;

	NVIC_EnableIRQ(DMA2D_IRQn);
}
