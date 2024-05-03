/*
 * i2c3.c
 *
 *  Created on: Nov 1, 2023
 *      Author: hussamaldean
 */


#include "STM32F4xx.h"

#include "i2c3.h"
#include "stdio.h"

#define AF04 0x04

void i2c3_init(void)
{
	/*GPIO Configuration*/

	/*Enable Clock access to GPIOA and GPIOC*/
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN;

	/*GPIOA configuration*/
	GPIOA->MODER|=GPIO_MODER_MODE8_1;
	GPIOA->MODER&=~GPIO_MODER_MODE8_0;

	GPIOA->OTYPER|=GPIO_OTYPER_OT8;

	GPIOA->AFR[1]|=(AF04<<GPIO_AFRH_AFSEL8_Pos);

	/*GPIOC configuration*/
	GPIOC->MODER|=GPIO_MODER_MODE9_1;
	GPIOC->MODER&=~GPIO_MODER_MODE9_0;

	GPIOC->OTYPER|=GPIO_OTYPER_OT9;

	GPIOC->AFR[1]|=(AF04<<GPIO_AFRH_AFSEL9_Pos);


	/*I2C3 Init*/

	RCC->APB1ENR|=RCC_APB1ENR_I2C3EN;

	I2C3->CR1=I2C_CR1_SWRST;//reset i2c
	I2C3->CR1&=~I2C_CR1_SWRST;// release reset i2c
	I2C3->CR2|=0x2d;//set clock source to 42MHz
	I2C3->CCR=0xe1 ;  //based on calculation
	I2C3->TRISE=0x2e; //output max rise
	I2C3->CR1|=I2C_CR1_PE; //enable I2C

}

void I2C3_WriteByte(uint8_t saddr,uint8_t maddr, uint8_t data)
{
	while(I2C3->SR2&I2C_SR2_BUSY){;}          /*wait until bus not busy*/
	I2C3->CR1|=I2C_CR1_START;                 /*generate start*/
	while(!(I2C3->SR1&I2C_SR1_SB)){;}         /*wait until start bit is set*/
	I2C3->DR = saddr<< 1;                 	 /* Send slave address*/
	while(!(I2C3->SR1&I2C_SR1_ADDR)){;}      /*wait until address flag is set*/
	(void)I2C3->SR2; 							/*clear SR2 by reading it */
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}       /*Wait until Data register empty*/
	I2C3->DR = maddr;                        /* send memory address*/
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}       /*wait until data register empty*/
	I2C3->DR = data;
	while (!(I2C3->SR1 & I2C_SR1_BTF));      /*wait until transfer finished*/
	I2C3->CR1 |=I2C_CR1_STOP;
}

void I2C3_ReadMultiByte(uint8_t saddr,uint8_t maddr, uint8_t* data, uint16_t n)
{
	while (I2C3->SR2 & I2C_SR2_BUSY){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1 & I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1;
	while(!(I2C3->SR1 & I2C_SR1_ADDR)){;}
	(void)I2C3->SR2;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->DR = maddr;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1 & I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1|1;
	while(!(I2C3->SR1 & I2C_SR1_ADDR)){;}
	(void)I2C3->SR2;
	I2C3->CR1|=I2C_CR1_ACK;
	while(n>0U)
	{
		if(n==1U)
		{
			I2C3->CR1&=~I2C_CR1_ACK;
			I2C3->CR1|=I2C_CR1_STOP;
			while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
			*data++=I2C3->DR;
			break;
		}
		else
		{
			while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
			(*data++)=I2C3->DR;
			n--;

		}
	}
}


void i2c3_WriteMulti(uint8_t saddr,uint8_t maddr,uint8_t *buffer, uint8_t length)
{
	while (I2C3->SR2 & I2C_SR2_BUSY);           //wait until bus not busy
	I2C3->CR1 |= I2C_CR1_START;                 //generate start
	while (!(I2C3->SR1 & I2C_SR1_SB)){;}		//wait until start is generated

	I2C3->DR = saddr<< 1;                 	 	// Send slave address
	while (!(I2C3->SR1 & I2C_SR1_ADDR)){;}      //wait until address flag is set
	(void)I2C3->SR2; 						    //Clear SR2
	while (!(I2C3->SR1 & I2C_SR1_TXE));         //Wait until Data register empty
	I2C3->DR = maddr;                      		// send memory address
	while (!(I2C3->SR1 & I2C_SR1_TXE));         //wait until data register empty
	//sending the data
	for (uint8_t i=0;i<length;i++)
	 {
		I2C3->DR=buffer[i]; 					//filling buffer with command or data
		while (!(I2C3->SR1 & I2C_SR1_BTF));
	 }

	I2C3->CR1 |= I2C_CR1_STOP;					//wait until transfer finished

}


void i2c3_readByte(uint8_t saddr,uint8_t maddr, uint8_t *data)
{

	while(I2C3->SR2&I2C_SR2_BUSY){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1&I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1;
	while(!(I2C3->SR1&I2C_SR1_ADDR)){;}
	(void)I2C3->SR2;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->DR=maddr;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1&I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1|1;
	while(!(I2C3->SR1&I2C_SR1_ADDR)){;}
	I2C3->CR1&=~I2C_CR1_ACK;
	(void)I2C3->SR2;
	I2C3->CR1|=I2C_CR1_STOP;
	while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
	*data=I2C3->DR;

}


void i2c3_bus_scan(void)
{
	int a=0; //address variable
	for (uint8_t i=0;i<128;i++) //go through all 127 address
	{
		I2C3->CR1 |= I2C_CR1_START; //generate start
		while(!(I2C3->SR1 & I2C_SR1_SB)); // wait to start to be generated
		I2C3->DR=(i<<1|0); // transmit the address
		while(!(I2C3->SR1)|!(I2C3->SR2)){}; //clear status register
		I2C3->CR1 |= I2C_CR1_STOP; //generate stop condition
		for (int k=0;k<10000;k++);//minium wait time is 40 uS, but for sure, leave it 100 uS
		a=(I2C3->SR1&I2C_SR1_ADDR); //read the status register address set
		if (a==2)//if the address is valid
		{
			printf("Found I2C device at address 0x%X (hexadecimal), or %d (decimal)\r\n",i,i);

		}
	}
}
