/*
 * PWM.h
 *
 *  Created on: Dec 4, 2023
 *      Author: hussamaldean
 */

#ifndef PWM_H_
#define PWM_H_

#include "stdint.h"

void PB3_PWM_Init(void);
void PB3_PWM_SetDutyCycle(uint8_t duty);

#endif /* PWM_H_ */
