/*
 * dma.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Nilesh
 */

#include "dma.h"

void Dma_Init_M2M(uint8_t *dest, uint8_t *src, uint16_t size) {
    // enable DMA2 clock, bit 22 on AHB1ENR
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // clear DMA Stream configuration register
    // single transfer, M0 is target, single buffer mode, circular buffer disabled
    DMA2_Stream0->CR = 0x00;
    // wait until dma is disabled
    while(DMA2_Stream0->CR & DMA_SxCR_EN);

    // set channel CHSEL: bits27:25 to channel0
    DMA2_Stream0->CR |= 0 << DMA_SxCR_CHSEL_Pos;

    // set data transfer direction DIR: bits7:6 memory-to-memory (0b10)
    DMA2_Stream0->CR |= 2 << DMA_SxCR_DIR_Pos;

    // set channel priority PL bits17:16 to medium
    DMA2_Stream0->CR |= 1 << DMA_SxCR_PL_Pos;

    // increment memory MINC : bit10
    DMA2_Stream0->CR |= DMA_SxCR_MINC;
    // memory data size MSIZE : bits14:13 to byte (0b00)
    DMA2_Stream0->CR |= 0 << DMA_SxCR_MSIZE_Pos;

    // increment peripheral PINC : bit9
    DMA2_Stream0->CR |= DMA_SxCR_PINC;
    // peripheral data size PSIZE : bits12:11 to byte (0b00)
    DMA2_Stream0->CR |= 0 << DMA_SxCR_PSIZE_Pos;

    // source memory address
    DMA2_Stream0->PAR = (uint32_t)src;
    // destination memory address
    DMA2_Stream0->M0AR = (uint32_t)dest;
    // number of items to be transferred
    DMA2_Stream0->NDTR = size;

    // enable transfer complete interrupt bit4
    DMA2_Stream0->CR |= DMA_SxCR_TCIE;
    NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    // enable dma bit0
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}

volatile int dma2_flag = 0;
void DMA2_Stream0_IRQHandler(void)
{
    if (DMA2->LISR & DMA_LISR_TCIF0) {
        // clear stream 0 transfer complete interrupt
        DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
        // flag the interrupt
        dma2_flag = 1;
    }
}
