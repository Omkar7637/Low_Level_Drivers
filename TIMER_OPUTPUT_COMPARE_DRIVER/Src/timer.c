/*
 * timer.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Nilesh
 */
#include "timer.h"

void TimerInit(void) {
	// GPIO PD.12, PD.13 config
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= (2 << (12 * 2)) | (2 << (13 * 2)); // mode=10 (alt fn)
	GPIOD->MODER |= (2 << (14 * 2)) | (2 << (15 * 2)); // mode=10 (alt fn)
	GPIOD->AFR[1] |= (2 << GPIO_AFRH_AFSEL12_Pos) | (2 << GPIO_AFRH_AFSEL13_Pos); // tim4 chx = alt fn2
	GPIOD->AFR[1] |= (2 << GPIO_AFRH_AFSEL14_Pos) | (2 << GPIO_AFRH_AFSEL15_Pos); // tim4 chx = alt fn2

	// Timer4 config
	// enable timer peri
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // enable TIM in APB
	// set timer clock, prescalar, arr, ccrx
	TIM4->PSC = TIM_PSC-1; // set prescalar
	/*
	TIM4->ARR = 10000-1; // set arr (10000 => 10 sec delay)
	TIM4->CCR1 = 3000-1; // set ccr1 (3000 => 3 sec init delay)
	TIM4->CCR2 = 6000-1; // set ccr2 (6000 => 6 sec init delay)
	*/
	TIM4->ARR = 500-1; // set arr 500 ms
	TIM4->CCR1 = 100-1; // set ccr1 100 ms
	TIM4->CCR2 = 200-1; // set ccr2 200 ms
	TIM4->CCR3 = 300-1; // set ccr3 300 ms
	TIM4->CCR4 = 400-1; // set ccr2 400 ms
	// select output mode
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0; // toggle CH1 on match
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0; // toggle CH2 on match
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0; // toggle CH3 on match
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_0; // toggle CH4 on match
	TIM4->CCER |= TIM_CCER_CC1E; // channel1 en-able
	TIM4->CCER |= TIM_CCER_CC2E; // channel2 enable
	TIM4->CCER |= TIM_CCER_CC3E; // channel3 en-able
	TIM4->CCER |= TIM_CCER_CC4E; // channel4 enable
	// start the timer
	TIM4->CR1 |= TIM_CR1_CEN; // enable timer clock
}

