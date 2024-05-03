/*
 * LTDC.c
 *
 *  Created on: Nov 17, 2023
 *      Author: hussamaldean
 uint8_t LTDC_Buffer[1280*800*3] __attribute__ ((section (".SDRAM_data")));

 uint32_t buffer_add (void)
 {

 return (uint32_t)&LTDC_Buffer;
 }

 static lv_color_t buf_1[MY_DISP_HOR_RES*MY_DISP_VER_RES]__attribute__ ((section (".SDRAM_data")));
 static lv_color_t buf_2[MY_DISP_HOR_RES*MY_DISP_VER_RES]__attribute__ ((section (".SDRAM_data")));

SDRAM	 (xrw)   : ORIGIN = 0XD0000000, LENGTH = 8M

.SDRAM_data :
{
    KEEP(*(.SDRAM_data))
} >SDRAM




 */


#include "stm32f4xx.h"
#include "LTDC.h"
#include "lvgl/lvgl.h"


#define FB_SIZE (320 * 240)

#define BYTES_PER_PIXEL 2

//#define SDRAM_BANK_ADDR ((uint32_t)0xD0000000)


__IO uint16_t  Frame_buffer[FB_SIZE]__attribute__ ((section(".SDRAM_data"),used));


uint32_t lcd_get_fb_address(void)
{
	return (uint32_t)&Frame_buffer;
}


void LTDC_Pins_Init()
{

	#define LTDC_AF 14U
	/*Refer to bsp_lcd.h for the pins required by the LCD*/
	//enable the peripheral clock for GPIO ports involved in LTDC interface
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;

	/*
	 * Configure GPIOA pins related to LTDC
	 * PA4, PA3, PA6, PA11, PA12 */
	/*Set the GPIOs to Alternate function*/
	GPIOA->MODER|=GPIO_MODER_MODE3_1|GPIO_MODER_MODE4_1|GPIO_MODER_MODE6_1|
			GPIO_MODER_MODE11_1|GPIO_MODER_MODE12_1;

	GPIOA->MODER&=~(GPIO_MODER_MODE3_0|GPIO_MODER_MODE4_0|GPIO_MODER_MODE6_0|
				GPIO_MODER_MODE11_0|GPIO_MODER_MODE12_0);

	/*Set the output speed to max*/
	GPIOA->OSPEEDR|=GPIO_OSPEEDR_OSPEED3|GPIO_OSPEEDR_OSPEED4|GPIO_OSPEEDR_OSPEED6|
			GPIO_OSPEEDR_OSPEED11|GPIO_OSPEEDR_OSPEED12;

	/*Select which alternate function to use */
	GPIOA->AFR[0]|=(LTDC_AF<<GPIO_AFRL_AFSEL3_Pos)|(LTDC_AF<<GPIO_AFRL_AFSEL4_Pos)|
			(LTDC_AF<<GPIO_AFRL_AFSEL6_Pos);

	GPIOA->AFR[1]|=(LTDC_AF<<GPIO_AFRH_AFSEL11_Pos)|(LTDC_AF<<GPIO_AFRH_AFSEL12_Pos);

	/*
		 * Configure GPIOB pins related to LTDC
		 * PB8, PB9, PB10, PB11, PB0, PB1*/

	GPIOB->MODER|=GPIO_MODER_MODE0_1|GPIO_MODER_MODE1_1|GPIO_MODER_MODE8_1|GPIO_MODER_MODE9_1|
			GPIO_MODER_MODE10_1|GPIO_MODER_MODE11_1;

	GPIOB->MODER&=~(GPIO_MODER_MODE0_0|GPIO_MODER_MODE1_0|GPIO_MODER_MODE8_0|GPIO_MODER_MODE9_0|
				GPIO_MODER_MODE10_0|GPIO_MODER_MODE11_0);

	GPIOB->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR0|GPIO_OSPEEDER_OSPEEDR1|GPIO_OSPEEDER_OSPEEDR8|
			GPIO_OSPEEDER_OSPEEDR9|GPIO_OSPEEDER_OSPEEDR10|GPIO_OSPEEDER_OSPEEDR11;

	GPIOB->AFR[0]|=(LTDC_AF<<GPIO_AFRL_AFSEL0_Pos)|(LTDC_AF<<GPIO_AFRL_AFSEL1_Pos);
	GPIOB->AFR[1]|=(LTDC_AF<<GPIO_AFRH_AFSEL8_Pos)|(LTDC_AF<<GPIO_AFRH_AFSEL9_Pos)|
			(LTDC_AF<<GPIO_AFRH_AFSEL10_Pos)|(LTDC_AF<<GPIO_AFRH_AFSEL11_Pos);


	/*
		 * Configure GPIOC pins related to LTDC
		 * PC6, PC7, PC10*/

	GPIOC->MODER|=GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1|GPIO_MODER_MODE10_1;
	GPIOC->MODER&=~(GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0|GPIO_MODER_MODE10_0);

	GPIOC->OSPEEDR|=GPIO_OSPEEDR_OSPEED6|GPIO_OSPEEDR_OSPEED7|GPIO_OSPEEDR_OSPEED10;

	GPIOC->AFR[0]|=(LTDC_AF<<GPIO_AFRL_AFSEL6_Pos)|(LTDC_AF<<GPIO_AFRL_AFSEL7_Pos);
	GPIOC->AFR[1]|=(LTDC_AF<<GPIO_AFRH_AFSEL10_Pos);

		/*
		 * Configure GPIOD pins related to LTDC
		 * PD6, PD3*/

	GPIOD->MODER|=GPIO_MODER_MODE6_1|GPIO_MODER_MODE3_1;
	GPIOD->MODER&=~(GPIO_MODER_MODE6_0|GPIO_MODER_MODE3_0);

	GPIOD->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR3|GPIO_OSPEEDER_OSPEEDR6;

	GPIOD->AFR[0]|=(LTDC_AF<<GPIO_AFRL_AFSEL6_Pos)|(LTDC_AF<<GPIO_AFRL_AFSEL3_Pos);


	/*
	 * Configure GPIOG pins related to LTDC
	 * PG7, PG11, PG12, PG10, PG6*/

	GPIOG->MODER|=GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1|GPIO_MODER_MODE10_1|
			GPIO_MODER_MODE11_1|GPIO_MODER_MODE12_1;

	GPIOG->MODER&=~(GPIO_MODER_MODE6_0|GPIO_MODER_MODE7_0|GPIO_MODER_MODE10_0|
			GPIO_MODER_MODE11_0|GPIO_MODER_MODE12_0);

	GPIOG->OSPEEDR|=GPIO_OSPEEDER_OSPEEDR6|GPIO_OSPEEDER_OSPEEDR7|GPIO_OSPEEDER_OSPEEDR10|
			GPIO_OSPEEDER_OSPEEDR11|GPIO_OSPEEDER_OSPEEDR12;

	GPIOG->AFR[0]|=(LTDC_AF<<GPIO_AFRL_AFSEL6_Pos)|(LTDC_AF<<GPIO_AFRL_AFSEL7_Pos);
	GPIOG->AFR[1]|=(LTDC_AF<<GPIO_AFRH_AFSEL11_Pos)|(LTDC_AF<<GPIO_AFRH_AFSEL12_Pos)|
			(LTDC_AF<<GPIO_AFRH_AFSEL10_Pos);

	/*
	 * Configure GPIOF pin related to LTDC
	 * PF10*/

	GPIOF->MODER|=GPIO_MODER_MODE10_1;
	GPIOF->MODER&=~GPIO_MODER_MODE10_0;
	GPIOF->OSPEEDR|=GPIO_OSPEEDR_OSPEED10;

	GPIOF->AFR[1]|=(LTDC_AF<<GPIO_AFRH_AFSEL10_Pos);

}


void LTDC_Init()
{
	RCC->APB2ENR|=RCC_APB2ENR_LTDCEN;


	/*Configure HSYNC*/

	LTDC->SSCR|=((LCD_HSW-1)<<LTDC_SSCR_HSW_Pos);

	LTDC->BPCR|=((LCD_HSW+LCD_HBP-1)<<LTDC_BPCR_AHBP_Pos);

	LTDC->AWCR|=((LCD_HSW+LCD_HBP+LCD_ACTIVE_WIDTH-1)<<LTDC_AWCR_AAW_Pos);

	uint32_t total_width = LCD_HSW+LCD_HBP+LCD_ACTIVE_WIDTH+LCD_HFP-1;

	LTDC->TWCR|=(total_width<<LTDC_TWCR_TOTALW_Pos);


	/*Configure VSYNC*/

	LTDC->SSCR|=((LCD_VSW-1)<<LTDC_SSCR_VSH_Pos);

	LTDC->BPCR|=((LCD_VSW+LCD_VBP-1)<<LTDC_BPCR_AVBP_Pos);

	LTDC->AWCR|=((LCD_VSW+LCD_VBP+LCD_ACTIVE_HEIGHT-1)<<LTDC_AWCR_AAH_Pos);

	uint32_t total_height = LCD_VSW+LCD_VBP+LCD_ACTIVE_HEIGHT+LCD_VFP-1;

	LTDC->TWCR|=(total_height<<LTDC_TWCR_TOTALH_Pos);

	/*Configure the shadow register*/
	/*Enable vertical banking reload*/

	/*Configure LTDC Background to be white*/
	LTDC->BCCR=(0x00<<LTDC_BCCR_BCBLUE_Pos)|(0x00<<LTDC_BCCR_BCGREEN_Pos)|(0x00<<LTDC_BCCR_BCRED_Pos);

	/*Enable pixel Dither*/
	//LTDC->GCR=LTDC_GCR_DEN;

	/*Enable LTDC*/

	LTDC->GCR|=LTDC_GCR_LTDCEN;



}


void Layer_Init(LTDC_Layer_TypeDef *Layer)
{

	Layer->CR&=~LTDC_LxCR_LEN;

	uint32_t tmp;

	Layer->PFCR |=(0x02<<LTDC_LxPFCR_PF_Pos);


	//2. configure the constant alpha and blending factors
	Layer->CACR&=~(0xFFU<<LTDC_LxCACR_CONSTA_Pos);
	Layer->CACR=(255U<<LTDC_LxCACR_CONSTA_Pos);


	tmp = 0;
	tmp|=(0x6U<<LTDC_LxBFCR_BF1_Pos)|(0x07U<<LTDC_LxBFCR_BF2_Pos);

	Layer->BFCR=tmp;


	//3. Configure layer position (Windowing)
	uint32_t AHBP=(LTDC->BPCR >>LTDC_BPCR_AHBP_Pos)&0xFFFU;

	uint32_t WHSTART = AHBP+LTDC_LAYER_H_START +1;
	tmp=0;
	tmp|=WHSTART<<LTDC_LxWHPCR_WHSTPOS_Pos;

	uint32_t WHSTOP = AHBP+LTDC_LAYER_H_START+LTDC_LAYER_WIDTH+1;
	uint32_t AAW =   (LTDC->AWCR>>LTDC_AWCR_AAW_Pos)&0xFFFU;
	WHSTOP = (WHSTOP > AAW)?AAW:WHSTOP;
	tmp&=~(0xFFFU<<LTDC_LxWHPCR_WHSPPOS_Pos);
	tmp|=WHSTOP<<LTDC_LxWHPCR_WHSPPOS_Pos;

	Layer->WHPCR=tmp;

	tmp = 0;
	uint32_t AVBP = (LTDC->BPCR>>LTDC_BPCR_AVBP_Pos)&0x7FFU;
	uint32_t WVSTART = AVBP+LTDC_LAYER_V_START+1;
	tmp|=WVSTART<<LTDC_LxWVPCR_WVSTPOS_Pos;

	uint32_t AAH = (LTDC->AWCR>>LTDC_AWCR_AAH_Pos)&0x7FFU;
	uint32_t WVSTOP = AVBP+LTDC_LAYER_V_START+LTDC_LAYER_HEIGHT+1;
	WVSTOP = (WVSTOP > AAH)?AAH:WVSTOP;
	tmp&=~(0x7FFU<<LTDC_LxWVPCR_WVSPPOS_Pos);
	tmp|=WVSTOP<<LTDC_LxWVPCR_WVSPPOS_Pos;

	Layer->WVPCR=tmp;

	//4. Configure Frame buffer address
	Layer->CFBAR=lcd_get_fb_address();



	//6 . Configure pitch, line length and total lines of the frame buffer
	tmp = 0;

	uint32_t pitch =  LTDC_LAYER_WIDTH*2 ;

	uint32_t line_len = pitch+3;

	tmp|=pitch<<LTDC_LxCFBLR_CFBP_Pos;

	tmp&=~(0x1FFFU<<LTDC_LxCFBLR_CFBLL_Pos);

	tmp|=line_len<<LTDC_LxCFBLR_CFBLL_Pos;

	Layer->CFBLR|=tmp;

	Layer->CFBLNR&=~(LTDC_LxCFBLNR_CFBLNBR_Msk<<LTDC_LxCFBLNR_CFBLNBR_Pos);

	Layer->CFBLNR|=LTDC_LAYER_HEIGHT<<LTDC_LxCFBLNR_CFBLNBR_Pos;


	//8. Enable the layer
	Layer->CR|=LTDC_LxCR_LEN;

	LTDC->SRCR|=LTDC_SRCR_IMR;

}




//void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint8_t red, uint8_t green, uint8_t blue)
void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code)
{

	*(__IO uint16_t*) ( lcd_get_fb_address()+ 2*((Ypos*LTDC_LAYER_WIDTH + Xpos))) = (uint16_t)RGB_Code;

}