/*
 * dac.h
 *
 *  Created on: Apr 6, 2024
 *      Author: Nilesh
 */

#ifndef DAC_H_
#define DAC_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

void DAC_Init(void);
void DAC_SetValue(uint16_t val);

#endif /* DAC_H_ */
