/*
 * sys_init.c
 *
 *  Created on: Oct 14, 2022
 *      Author: hussamaldean
 */

#include "stm32f4xx.h"

void SystemInit (void)
{

	#define PLL_M      4
	#define PLL_N      180
	#define PLL_P      2
	#define PLL_Q      9

	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;


	  RCC->CR |= ((uint32_t)RCC_CR_HSEON);


	  do
	  {
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	  } while((HSEStatus == 0) && (StartUpCounter != 3000));

	  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	  {
		HSEStatus = (uint32_t)0x01;
	  }
	  else
	  {
		HSEStatus = (uint32_t)0x00;
	  }

	  if (HSEStatus == (uint32_t)0x01)
	  {

		RCC->APB1ENR |= RCC_APB1ENR_PWREN;
		PWR->CR &= (uint32_t)~(PWR_CR_VOS);


		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;


		RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;


		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;


		RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
					   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);


		RCC->CR |= RCC_CR_PLLON;


		while((RCC->CR & RCC_CR_PLLRDY) == 0)
		{
		}

		/* Configure Flash prefetch, Instruction cache, Data cache and wait state */
		FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;


		/* Select the main PLL as system clock source */
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= RCC_CFGR_SW_PLL;

		/* Wait till the main PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL)
		{;}
	  }
	  else
	  { /* If HSE fails to start-up, the application will have wrong clock
			 configuration. User can add here some code to deal with this error */
	  }

	  /*Enable FPU*/
	  SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	  /*Enable cell compensation*/
	  RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN ;
	  SYSCFG->CMPCR|=(1<<0);
	  while(!((SYSCFG->CMPCR)&(1<<8))){;}

	  /*Enable over drive*/

	  PWR->CR|=PWR_CR_ODEN;

	  while((PWR->CSR & PWR_CSR_ODRDY) ==PWR_CSR_ODRDY);

	  PWR->CR|=PWR_CR_ODSWEN;

	  while((PWR->CSR & PWR_CSR_ODSWRDY) ==PWR_CSR_ODSWRDY);



	  /*Enable clock access to SAI1*/
	  RCC->APB2ENR|=RCC_APB2ENR_SAI1EN;


	  /*SAI clock configuration */
	  RCC->PLLSAICFGR|=(0x02U<<RCC_PLLSAICFGR_PLLSAIR_Pos);

	  RCC->PLLSAICFGR|=(100U<<RCC_PLLSAICFGR_PLLSAIN_Pos);

	  RCC->DCKCFGR|=(0x03U<<RCC_DCKCFGR_PLLSAIDIVR_Pos);

	  RCC->CR|=RCC_CR_PLLSAION;
	  while(!(RCC->CR & RCC_CR_PLLSAION));

}

