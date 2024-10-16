/*
 * systick.c
 *
 *  Created on: Apr 6, 2024
 *      Author: Nilesh
 */

#include "systick.h"

static volatile uint32_t jiffies = 0;

// Will be executed after every 1 ms
void SysTick_Handler(void) {
	jiffies++;
}

// Generate delay for given milliseconds
void SysTick_Delay(uint32_t delayMs) {
	uint32_t now = jiffies;
	uint32_t waitUntil = now + delayMs;
	while(jiffies < waitUntil)
		;
}


