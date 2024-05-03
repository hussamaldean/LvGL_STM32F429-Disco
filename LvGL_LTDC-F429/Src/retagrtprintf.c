/*
 * retagrtprintf.c
 *
 *  Created on: Nov 4, 2023
 *      Author: hussamaldean
 */


#include "stm32f4xx.h"

#include "stdio.h"


int __io_putchar(int ch)
{
	 ITM_SendChar(ch);
	return ch;
}

