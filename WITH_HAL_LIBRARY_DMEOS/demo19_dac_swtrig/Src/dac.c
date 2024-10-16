/*
 * dac.c
 *
 *  Created on: Apr 6, 2024
 *      Author: Nilesh
 */

#include "dac.h"

void DAC_Init(void) {
	//1. Enable GPIOA peripheral. (DAC1_OUT=PA4, DAC2_OUT=PA5)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//2. Set GPIO mode to Analog. (PA4 MODER = 0b11).
	GPIOA->MODER |= 3 << GPIO_MODER_MODE4_Pos;
	//3. Enable DAC peripheral (APB1).
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	//4. Enable DAC channel, Output buffer, Enable trigger, and select Trigger (Software=0b111) (CR).
	DAC1->CR |= DAC_CR_EN1 | DAC_CR_TEN1 | DAC_CR_TSEL1_2 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_0;
	//5. Set DAC register to initial value. (DHRxR)
	DAC1->DHR12R1 = 0x000;
}

void DAC_SetValue(uint16_t val) {
	//1. Set value in DAC register. (DHRxR)
	DAC1->DHR12R1 = val;
	//2. Trigger conversion (in SWTRIGR).
	DAC1->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;
}

