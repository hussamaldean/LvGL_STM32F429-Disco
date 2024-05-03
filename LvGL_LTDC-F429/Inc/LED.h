/*
 * LED.h
 *
 *  Created on: Dec 4, 2023
 *      Author: hussamaldean
 */

#ifndef LED_H_
#define LED_H_

#include "stdint.h"


typedef enum LEDs
{
	LED3=0,
	LED4=1

}LEDsTypedef;

void LEDS_Init(void);

void LEDSet(LEDsTypedef LED, uint8_t state);


#endif /* LED_H_ */
