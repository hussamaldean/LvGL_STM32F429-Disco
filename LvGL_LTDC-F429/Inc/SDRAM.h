/*
 * SDRAM.h
 *
 *  Created on: Nov 20, 2023
 *      Author: hussamaldean
 */


/*
 * SDRAM Pins
 *
 * STM32 SDRAM1
 * ---------
 * PORTB
 * PB5 ->SDKE1
 * PB6 ->SDNE1
 * ---------
 * PORTC
 * PC0 ->SDNWE
 * ---------
 * PORTD
 *
 * PD0 ->D2
 * PD1 ->D3
 * PD8 ->D13
 * PD9 ->D14
 * PD10->D15
 * PD14->D0
 * PD15->D1
 *
 * --------
 * PORTE
 *
 * PE0-> NBL0
 * PE1-> NBL1
 * PE7-> D4
 * PE8-> D5
 * PE9-> D6
 * PE10->D6
 * PE11->D8
 * PE12->D9
 * PE13->D10
 * PE14->D11
 * PE15->D12
 * --------
 * PORTF
 *
 * PF0 ->A0
 * PF1 ->A1
 * PF2 ->A2
 * PF3 ->A3
 * PF4 ->A4
 * PF5 ->A5
 * PF11->SDNRAS
 * PF12->A6
 * PF13->A7
 * PF14->A8
 * PF15->A9
 *
 * -------
 * PORTG
 * PG0 ->A10
 * PG1 ->A11
 * PG4 ->BA0
 * PG5 ->BA1
 * PG8->SDCLK
 * PG15->SDNCAS
 *
 *
 * */




#ifndef SDRAM_H_
#define SDRAM_H_
#include "stdint.h"

void FMC_Clock_Enable(void);
void SDRAM_Init(void);
void SDRAM_Pins_Init(void);


#endif /* SDRAM_H_ */
