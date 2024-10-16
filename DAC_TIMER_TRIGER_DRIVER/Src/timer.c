/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Nilesh
 */
#include "timer.h"
#include "dac.h"

void TimerInit(uint32_t ms) {
	// enable timer clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// set prescalar
	TIM6->PSC = TIM_PR-1;
	// set number of clocks to count
	uint16_t cnt = (TCLK / 1000) * ms / TIM_PR;
	TIM6->ARR = cnt - 1;
	// start count from 0
	TIM6->CNT = 0;
	// enable UI interrupt in timer
	TIM6->DIER |= TIM_DIER_UIE;
	// enable interrupt in NVIC
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	// use update event as trigger
	TIM6->CR2 |= TIM_CR2_MMS_1;
	// start timer counter
	TIM6->CR1 |= TIM_CR1_CEN;
}

// implement timer ISR
void TIM6_DAC_IRQHandler(void)
{
	static uint16_t val = 0, step = 16;
	// check if interrupt occurred
	if(TIM6->SR & TIM_SR_UIF) {
		// then clear (ack) the interrupt
		TIM6->SR &= ~TIM_SR_UIF;
		// set DAC value
		DAC_SetValue(val);
		val = val + step;
		if(val <= 0 || val >= 4096)
			step = -step;
	}
}




