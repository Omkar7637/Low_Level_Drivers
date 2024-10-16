/*
 * iwdg.h
 *
 *  Created on: Apr 5, 2024
 *      Author: Nilesh
 */

#ifndef IWDG_H_
#define IWDG_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define IWDG_CLK	32000
void IWDGInit(uint32_t ms);
void IWDGRefresh(void);
int IsIWDGReset(void);

#endif /* IWDG_H_ */
