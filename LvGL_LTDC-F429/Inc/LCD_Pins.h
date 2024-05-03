/*
 * LCD_Pins.h
 *
 *  Created on: Oct 24, 2023
 *      Author: hussamaldean
 */

#ifndef LCD_PINS_H_
#define LCD_PINS_H_

#include "delay.h"
#include "stm32f4xx.h"

#define LCD_RES_HIGH(void)			GPIOA->BSRR=GPIO_BSRR_BS7
#define LCD_RES_LOW(void)			GPIOA->BSRR=GPIO_BSRR_BR7

#define LCD_CS_HIGH(void)			GPIOC->BSRR=GPIO_BSRR_BS2
#define LCD_CS_LOW(void)			GPIOC->BSRR=GPIO_BSRR_BR2

#define LCD_DC_HIGH(void)			GPIOD->BSRR=GPIO_BSRR_BS13
#define LCD_DC_LOW(void)			GPIOD->BSRR=GPIO_BSRR_BR13


/*SPI */
void LCD_Pin_Init(void);
void LCD_SPI_Init(void);

/*LCD*/
void LCD_RST(void);
void LCD_Write_Cmd(uint8_t cmd);
void LCD_Write_Data (uint8_t data);


#endif /* LCD_PINS_H_ */
