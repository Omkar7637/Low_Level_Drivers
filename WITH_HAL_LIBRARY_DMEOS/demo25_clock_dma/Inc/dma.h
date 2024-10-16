/*
 * dma.h
 *
 *  Created on: Apr 11, 2024
 *      Author: Nilesh
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f4xx.h"
#include "stm32f407xx.h"

void Dma_Init_M2M(uint8_t *dest, uint8_t *src, uint16_t size);
extern volatile int dma2_flag;

#endif /* DMA_H_ */
