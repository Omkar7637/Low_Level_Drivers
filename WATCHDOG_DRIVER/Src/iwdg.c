/*
 * iwdg.c
 *
 *  Created on: Apr 5, 2024
 *      Author: Nilesh
 */

#include "iwdg.h"

void IWDGInit(uint32_t ms) {
	// Enable LSI
	RCC->CSR |= RCC_CSR_LSION;				//enable LSI (stm32 manual 7.3.21)
	while(!(RCC->CSR & RCC_CSR_LSIRDY));	//wait for LSI ready flag

	// Enable IWDG
	IWDG->KR = 0xCCCC;

	// Enable IWDG register access
	IWDG->KR = 0x5555;

	// set PreScalar
	IWDG->PR = IWDG_PR_PR_0 | IWDG_PR_PR_1 | IWDG_PR_PR_2; // PR=256

	// set reload value
	uint32_t cnt = (IWDG_CLK / 1000) * ms / 256;
	IWDG->RLR = cnt;

	// wait for registers (PR and RLR) update (bit1==0, bit0==0)
	while(IWDG->SR)
		;

	// Refresh WDG
	IWDGRefresh();
}

void IWDGRefresh(void) {
	// Enable IWDG refresh
	IWDG->KR = 0xAAAA;
}

int IsIWDGReset(void) {
	// check bit29 from RCC CSR register for IWDG reset
	return (RCC->CSR & RCC_CSR_IWDGRSTF) ? 1 : 0;
}

