#include <stdint.h>
#include "uart.h"
#include "stm32f446xx.h"

#define GPIOAEN			(1U<<0) // Enabling the GPIO PORT A
#define UART2EN			(1U<<17)// ENABLING THE UART PAGE 118 DM
#define SYS_FREQ		16000000 // DEFULT FREQUENCY 16MHZ
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	115200 // SETTING DEFULT BAUD RATE TO 115200 FOR UART
#define CR1_TE			(1U<<3)
#define CR1_UE			(1U<<13)
#define SR_TXE			(1U<<7)

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate);
static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);


int __io_putchar(int ch)
{
	uart_write(ch);
	return ch;
}

void uart_tx_init(void)
{

	 RCC->AHB1ENR  |= GPIOAEN;//Enable clock access to GPIOA


	 GPIOA->MODER &=~(1U<<4); // PA2 AF PIN 4 ,Set PA2 mode to alternate function mode PAGE NO 157
	 GPIOA->MODER |=(1U<<5); //PA2 AF PIN 5


	 GPIOA->AFR[0] |=(1U<<8);// PIN 8 Set alternate function type to AF7 (UART2_TX) PAGE NO 161
	 GPIOA->AFR[0] |=(1U<<9);//PIN 9
	 GPIOA->AFR[0] |=(1U<<10);//PIN 10
	 GPIOA->AFR[0] &= ~(1U<<11);//PIN 11


	 RCC->APB1ENR |= UART2EN; // Enable clock access to UART PAGE NO 118

	// Configure baudrate
	 uart_set_baudrate(APB1_CLK,UART_BAUDRATE);

	/*Configure transfer direction*/
	 USART2->CR1 = CR1_TE;

	/*Enable UART module*/
	 USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch)
{
	/*Make sure the transmit data register is empty*/
	 while(!(USART2->SR & SR_TXE)){}

	/*Write to transmit data register*/
	 USART2->DR =  (ch & 0XFF);
}

static void uart_set_baudrate(uint32_t periph_clk, uint32_t baudrate) // ARG PERIFRERAL CLOCK AND DESIRED BAURD RATE WILL BE TAKE
{
	USART2->BRR = compute_uart_bd(periph_clk,baudrate);
}

static uint16_t compute_uart_bd(uint32_t periph_clk, uint32_t baudrate)
{
	return ((periph_clk + (baudrate/2U))/baudrate);
}
