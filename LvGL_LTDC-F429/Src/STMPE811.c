/*
 * STMPE811.c
 *
 *  Created on: Nov 4, 2023
 *      Author: hussamaldean
 */


#include "i2c3.h"
#include "STMPE811.h"
#include "delay.h"
#include "STM32F4xx.h"


void STMPE811_Touch_Enable(void)
{

	uint8_t mode;

	/* Power Down the stmpe811 */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_SYS_CTRL1, 2);

	/* Wait for a delay to ensure registers erasing */
	delay(10);

	/* Power On the Codec after the power off => all registers are reinitialized */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_SYS_CTRL1, 0);

	/* Wait for a delay to ensure registers erasing */
	delay(2);

	/*Disable clock access to GPIO*/

	i2c3_readByte(deviceAddress, STMPE811_REG_SYS_CTRL2, &mode);

	mode &= ~(STMPE811_IO_FCT);

	/* Write the new register value */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_SYS_CTRL2, mode);


	/*Select TSC pins in TSC alternate mode */

	I2C3_WriteByte(deviceAddress, STMPE811_REG_IO_AF, STMPE811_TOUCH_IO_ALL);


	mode&= ~(STMPE811_TS_FCT | STMPE811_ADC_FCT);

	/* Write the new register value */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_SYS_CTRL2, mode);



	/* Select Sample Time, bit number and ADC Reference */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_ADC_CTRL1, 0x49);

	/* Wait for 2 ms */
	delay(2);

	/* Select the ADC clock speed: 3.25 MHz */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_ADC_CTRL2, 0x01);



	/* Select 2 nF filter capacitor */
	/* Configuration:
	- Touch average control    : 8 samples
	- Touch delay time         : 500 uS
	- Panel driver setting time: 500 uS
	*/
	I2C3_WriteByte(deviceAddress, STMPE811_REG_TSC_CFG, 0xDA);

	/* Configure the Touch FIFO threshold: single point reading */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_TH, 0x01);

	/* Clear the FIFO memory content. */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, 0x01);

	/* Put the FIFO back into operation mode  */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, 0x00);

	/* Set the range and accuracy pf the pressure measurement (Z) :
	- Fractional part :7a
	- Whole part      :1
	*/
	I2C3_WriteByte(deviceAddress, STMPE811_REG_TSC_FRACT_XYZ, 0x07);

	/* Set the driving capability (limit) of the device for TSC pins: 50mA */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_TSC_I_DRIVE, 0x01);

	/* Touch screen control configuration (enable TSC):
	- No window tracking index
	- XYZ acquisition mode
	*/
	I2C3_WriteByte(deviceAddress, STMPE811_REG_TSC_CTRL, 0x01);

	/*  Clear all the status pending bits if any */
	I2C3_WriteByte(deviceAddress, STMPE811_REG_INT_STA, 0xFF);


	/*Delay for 5ms*/

	delay(5);

//	/*Enable Interrupt for touch*/
//
//	I2C3_WriteByte(deviceAddress, STMPE811_REG_INT_EN, 0x01);
//
//
//	/*Enable Interrupt
//	* Global interrupt.
//	* Rising edge.
//	* Edge detection.
//	* */
//
//	I2C3_WriteByte(deviceAddress, STMPE811_REG_INT_CTRL, 0x07);




}



TouchDetect_t isToched(void)
{

	uint8_t state=0;
	uint8_t value=0;

	i2c3_readByte(deviceAddress, STMPE811_REG_TSC_CTRL, &value);

	value&=STMPE811_TS_CTRL_STATUS;

	state=(value&STMPE811_TS_CTRL_STATUS)==0x80;

	if(value==STMPE811_TS_CTRL_STATUS)
	{
		i2c3_readByte(deviceAddress,STMPE811_REG_FIFO_SIZE, &value);
		if(value>0)
		{
			return touched;
		}
	}

	else
	{
		/* Clear the FIFO memory content. */
		I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, 0x01);

		/* Put the FIFO back into operation mode  */
		I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, 0x00);
	}



	return no_touch;
}




void getTouchValue(uint16_t *X, uint16_t *Y)
{
	uint32_t uldataXYZ;
	uint8_t  dataXYZ[4];
	uint8_t mode;
	uint16_t localx=0,localy =0;


		I2C3_ReadMultiByte(deviceAddress, STMPE811_REG_TSC_DATA_NON_INC, dataXYZ, 4) ;

		/* Calculate positions values */
		uldataXYZ = (dataXYZ[0] << 24)|(dataXYZ[1] << 16)|(dataXYZ[2] << 8)|(dataXYZ[3] << 0);
		*X=(uldataXYZ >> 20) & 0x00000FFF;
		*Y= (uldataXYZ >>  8) & 0x00000FFF;

		/* Reset FIFO */
		mode=0x01;
		I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, mode);

		/* Enable the FIFO again */
		mode=0x00;
		I2C3_WriteByte(deviceAddress, STMPE811_REG_FIFO_STA, mode);


}



uint16_t getID(void)
{
	uint8_t data[2];
	I2C3_ReadMultiByte(deviceAddress, 0x00, data, 2);
	uint16_t data_re=data[0]<<8|data[1];
	return (data_re);

}

//void EXTI15_10_IRQHandler(void)
//{
//	if((EXTI->PR & EXTI_PR_PR15)==EXTI_PR_PR15)
//	{
//		GPIOG->ODR^=GPIO_ODR_OD13;
//		Touched=1;
//		EXTI->PR|=EXTI_PR_PR15;
//	}
//
//}
