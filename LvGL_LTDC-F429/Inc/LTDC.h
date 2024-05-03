/*
 * LTDC.h
 *
 *  Created on: Nov 17, 2023
 *      Author: hussamaldean
 */

#ifndef LTDC_H_
#define LTDC_H_
#include "stdint.h"

#include "lvgl/lvgl.h"

#define LCD_WIDTH  					240
#define LCD_HEIGHT 					320




#define  LCD_ACTIVE_WIDTH 			LCD_WIDTH
#define  LCD_ACTIVE_HEIGHT  		LCD_HEIGHT

/*Set layer width and height */
#define LTDC_LAYER_WIDTH			LCD_WIDTH
#define LTDC_LAYER_HEIGHT			LCD_HEIGHT
#define LTDC_LAYER_H_START			0
#define LTDC_LAYER_H_STOP			LCD_ACTIVE_WIDTH
#define LTDC_LAYER_V_START			0
#define LTDC_LAYER_V_STOP			LCD_ACTIVE_HEIGHT


/*Select pixel format */

#define LCD_PIXEL_FMT 				2


#define LCD_HSW 					10
#define LCD_HBP						20
#define LCD_HFP						10
#define LCD_VSW						2
#define LCD_VBP						2
#define LCD_VFP						4

#define FB_WIDTH					LTDC_LAYER_WIDTH
#define FB_HEIGHT					LTDC_LAYER_HEIGHT

/*Functions*/

void LTDC_Pins_Init();
void LTDC_Init();
void Layer_Init(LTDC_Layer_TypeDef *Layer);
void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t RGB_Code);
//void LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint8_t red, uint8_t green, uint8_t blue);
uint32_t lcd_get_fb_address(void);

#endif /* LTDC_H_ */
