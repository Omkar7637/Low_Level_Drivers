/*
 * timer.c
 *
 *  Created on: Apr 4, 2024
 *      Author: Nilesh
 */
#include "led.h"
#include "timer.h"

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
	// start timer counter
	TIM6->CR1 |= TIM_CR1_CEN;
}

// implement timer ISR
void TIM6_DAC_IRQHandler(void)
{
	static int flag = 0;
	// check if interrupt occurred
	if(TIM6->SR & TIM_SR_UIF) {
		// then clear (ack) the interrupt
		TIM6->SR &= ~TIM_SR_UIF;
		// toggle LED
		if(flag == 0) {
			LedOn(LED_BLUE);
			flag = 1;
		} else {
			LedOff(LED_BLUE);
			flag = 0;
		}
	}
}




