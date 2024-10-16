/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Nilesh
 */

#include "timer.h"

void TimerInit(void) {
	// enable timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// set prescalar
	TIM6->PSC = TIM_PR-1;
}

void TimerDelayMs(uint32_t ms) {
	// set number of clocks to count
	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM6->ARR = cnt - 1;
	// start count from 0
	TIM6->CNT = 0;
	// start timer counter
	TIM6->CR1 |= TIM_CR1_CEN;
	// wait for update interrupt flag
	while(! (TIM6->SR & TIM_SR_UIF))
		;
	// clear the update interrupt flag
	TIM6->SR &= ~TIM_SR_UIF;
	// stop timer counter
	TIM6->CR1 &= ~TIM_CR1_CEN;
}




