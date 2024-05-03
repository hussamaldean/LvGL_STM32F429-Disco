/*
 * STMPE811.h
 *
 *  Created on: Nov 4, 2023
 *      Author: hussamaldean
 */

#ifndef STMPE811_H_
#define STMPE811_H_

#include "stdint.h"

#define deviceAddress 0x41


typedef enum TouchDetect
{
	touched =1,
	no_touch=0

}TouchDetect_t;



#define STMPE811_REG_SYS_CTRL2 			0x04 /*Clock control*/
#define STMPE811_REG_SYS_CTRL1 			0x03 /*Reset control*/
#define STMPE811_REG_IO_AF              0x17 /*Alternate function register*/
#define STMPE811_REG_ADC_CTRL1          0x20 /*ADC control*/
#define STMPE811_REG_ADC_CTRL2          0x21 /*ADC control*/
#define STMPE811_REG_TSC_CFG            0x41 /*Touch Configuration*/
#define STMPE811_REG_FIFO_TH            0x4A /*FIFO threshold*/
#define STMPE811_REG_FIFO_STA           0x4B /*FIFO status*/
#define STMPE811_REG_TSC_FRACT_XYZ      0x56 /*Touchscreen controller FRACTION_Z*/
#define STMPE811_REG_TSC_I_DRIVE        0x58 /*Touchscreen controller drive*/
#define STMPE811_REG_TSC_CTRL           0x40 /*touchscreen controller control register*/
#define STMPE811_REG_INT_CTRL			0x09 /*Interrupt control register*/
#define STMPE811_REG_INT_EN				0x0A /*Interrupt enable register*/
#define STMPE811_REG_INT_STA            0x0B /*Interrupt status register*/
#define STMPE811_REG_TSC_DATA_INC       0x57 /*Touchscreen controller DATA Incremental*/
#define STMPE811_REG_TSC_DATA_NON_INC   0xD7 /*Touchscreen controller DATA Non-Incremental*/
#define STMPE811_REG_FIFO_SIZE          0x4C /*FIFO size*/

/*IO expander facilities*/
#define STMPE811_ADC_FCT                0x01
#define STMPE811_TS_FCT                 0x02
#define STMPE811_IO_FCT                 0x04
#define STMPE811_TEMPSENS_FCT           0x08



/* Touch Screen Pins definition */
#define STMPE811_TOUCH_YD               STMPE811_PIN_7
#define STMPE811_TOUCH_XD               STMPE811_PIN_6
#define STMPE811_TOUCH_YU               STMPE811_PIN_5
#define STMPE811_TOUCH_XU               STMPE811_PIN_4
#define STMPE811_TOUCH_IO_ALL           0x00

/* IO Pins definition */
#define STMPE811_PIN_0                  0x01
#define STMPE811_PIN_1                  0x02
#define STMPE811_PIN_2                  0x04
#define STMPE811_PIN_3                  0x08
#define STMPE811_PIN_4                  0x10
#define STMPE811_PIN_5                  0x20
#define STMPE811_PIN_6                  0x40
#define STMPE811_PIN_7                  0x80
#define STMPE811_PIN_ALL                0xFF

#define STMPE811_TS_CTRL_ENABLE         0x01
#define STMPE811_TS_CTRL_STATUS         0x80


#define Touch_XMIN 						390
#define Touch_YMIN 						359
#define Touch_XMAX 						3830
#define Touch_YMAX 						3895
#define Touch_WIDTH 					(Touch_XMAX - Touch_XMIN)
#define Touch_HEIGHT 					(Touch_YMAX - Touch_YMIN)



void STMPE811_Touch_Enable(void);
TouchDetect_t isToched(void);
void getTouchValue(uint16_t *X, uint16_t *Y);
uint16_t getID(void);





#endif /* STMPE811_H_ */
