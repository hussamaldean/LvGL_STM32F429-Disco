/*
 * i2c3.h
 *
 *  Created on: Nov 1, 2023
 *      Author: hussamaldean
 */

#ifndef I2C3_H_
#define I2C3_H_

#include "stdint.h"

void i2c3_init(void);
void I2C3_WriteByte(uint8_t saddr,uint8_t maddr, uint8_t data);
void I2C3_ReadMultiByte(uint8_t saddr,uint8_t maddr, uint8_t* data, uint16_t n);
void i2c3_WriteMulti(uint8_t saddr,uint8_t maddr,uint8_t *buffer, uint8_t length);
void i2c3_readByte(uint8_t saddr,uint8_t maddr, uint8_t *data);
void i2c3_bus_scan(void);

#endif /* I2C3_H_ */
