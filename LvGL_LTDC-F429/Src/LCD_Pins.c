/*
* LCD_Pins.c
*
*  Created on: Oct 24, 2023
*      Author: hussamaldean
*/

#include "stm32f4xx.h"
#include "LCD_Pins.h"

#define AF05						0x05






void LCD_Pin_Init(void)
{
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN|RCC_AHB1ENR_GPIODEN|RCC_AHB1ENR_GPIOFEN;

	/*PA7*/
	GPIOA->MODER|=GPIO_MODER_MODE7_0;
	GPIOA->MODER&=~GPIO_MODER_MODE7_1;
	GPIOA->OSPEEDR|=GPIO_OSPEEDR_OSPEED7;
	GPIOA->ODR|=GPIO_ODR_OD7;

	/*PC2*/
	GPIOC->MODER|=GPIO_MODER_MODE2_0;
	GPIOC->MODER&=~GPIO_MODER_MODE2_1;
	GPIOC->OSPEEDR|=GPIO_OSPEEDR_OSPEED2;
	GPIOC->ODR|=GPIO_ODR_OD2;



	/*PD13*/
	GPIOD->MODER|=GPIO_MODER_MODE13_0;
	GPIOD->MODER&=~GPIO_MODER_MODE13_1;
	GPIOD->OSPEEDR|=GPIO_OSPEEDR_OSPEED13;
	GPIOD->ODR|=GPIO_ODR_OD13;

	/*PF7 and PF9 for SPI5*/

	GPIOF->MODER|=GPIO_MODER_MODE7_1|GPIO_MODER_MODE9_1;
	GPIOF->MODER&=~(GPIO_MODER_MODE7_0|GPIO_MODER_MODE9_0);

	GPIOF->OSPEEDR|=GPIO_OSPEEDR_OSPEED7|GPIO_OSPEEDR_OSPEED9;

	GPIOF->AFR[0]|=(AF05<<GPIO_AFRL_AFSEL7_Pos);
	GPIOF->AFR[1]|=(AF05<<GPIO_AFRH_AFSEL9_Pos);


}


void LCD_SPI_Init(void)
{
	RCC->APB2ENR|=RCC_APB2ENR_SPI5EN;
	SPI5->CR1|=SPI_CR1_MSTR|SPI_CR1_SSM|SPI_CR1_SSI|SPI_CR1_BR_2|SPI_CR1_BR_1|SPI_CR1_BR_0;

	SPI5->CR1|=SPI_CR1_SPE;

}


static void spi5_transmit(uint8_t data)
{

	/*Wait until TXE is set*/
	while(!(SPI5->SR & (SPI_SR_TXE))){}

	/*Write the data to the data register*/
	SPI5->DR = data;


	/*Wait until TXE is set*/
	while(!(SPI5->SR & (SPI_SR_TXE))){}

	/*Wait for BUSY flag to reset*/
	while((SPI5->SR & (SPI_SR_BSY))){}

	/*Clear OVR flag*/
	(void) SPI5->DR;
	(void) SPI5->SR;
}


void LCD_RST(void)
{
	LCD_RES_LOW();
	delay(50);
	LCD_RES_HIGH();
	delay(20);

}





void LCD_Write_Cmd(uint8_t cmd)
{
	LCD_CS_LOW();
	LCD_DC_LOW();
	spi5_transmit(cmd);
	LCD_CS_HIGH();
}


void LCD_Write_Data (uint8_t data)
{
	LCD_CS_LOW();
	LCD_DC_HIGH();
	spi5_transmit (data);
	LCD_CS_HIGH();
}
