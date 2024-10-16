/* *************************************************************************
**  Target      : Cortex-M3
**  Environment : GNU Tools
*************************************************************************
*/

/* Misc Instructions */

.syntax unified

.global pfnVectors
.global Default_Handler
.global _start
.equ Top_Of_Stack, 0x20002000    /* end of 8K RAM */

.global sdata
.global edata
.global etext
.global sbss
.global ebss

.section .vectors
vectors:
	.word Top_Of_Stack          @ msp = 0x20002000
	.word _start                @ Starting Program address
	.word Default_Handler	    @ NMI_Handler
	.word Default_Handler	    @ HardFault_Handler
	.word Default_Handler	    @ MemManage_Handler
	.word Default_Handler	    @ BusFault_Handler
	.word Default_Handler	    @ UsageFault_Handler
	.word 0                     @ 7
	.word 0                     @ To
	.word 0                     @ 10 
	.word 0                     @ Reserved
	.word Default_Handler	    	@ SVC_Handler
	.word Default_Handler	    @ DebugMon_Handler
	.word 0                     @ Reserved
	.word Default_Handler	    @ PendSV_Handler
	.word Default_Handler	    @ SysTick_Handler
	.word Default_Handler	    @ IRQ_Handler
	.word Default_Handler	    @ IRQ_Handler

.section .rodata


.section .data


.section .bss


.section .text

.thumb
/**
 * This is the code that gets called when the processor first
 * starts execution following a reset. 
*/
.type _start, %function
_start:                              @ _start label is required by the linker

	//init .data section
	ldr r7, =etext
	ldr r6, =sdata
	ldr r5, =edata
	mov r4, #0
data_init:
	cmp r6, r5
	beq data_init_end
	ldrb r4, [r7], #1
	strb r4, [r6], #1
	b data_init
data_init_end:

	//clear .bss section
	ldr r6, =sbss
	ldr r7, =ebss
	mov r4, #0
bss_init:
	cmp r6, r7
	beq bss_init_end
	strb r4, [r6], #1
	b bss_init
bss_init_end:

	bl main
	stop:   b stop

/***************************************************************/
.global main
.type main, %function
main:                              
	@ Saturated Math
	mov r0, #10
	usat r1, #5, r0, lsl #1		@ 10 * 2 < 32
	usat r2, #5, r0, lsl #2		@ 10 * 4 >= 32 -- Saturation -- result=31 and Q=1

	@ simd instructions are not supported by CM3 (netduino2), but supported by CM4 (netduinoplus2)
	ldr r1, =0xAA4499BB
	ldr r2, =0x55778822
	adds r3, r1, r2		@ r1[31:0] + r2[31:0] --> r3[31:0] -- NZCV flags
						@ r3 = 0xFFBC21DD
	@uadd8 r4, r1, r2	@ SMID instruction	
						@ r1[7:0] + r2[7:0] --> r3[7:0] -- GE[0]
						@ r1[15:8] + r2[15:8] --> r3[15:8] -- GE[1]
						@ r1[23:16] + r2[23:16] --> r3[23:16] -- GE[2]
						@ r1[31:24] + r2[31:24] --> r3[31:24] -- GE[3]
						@ r4 = 0xFFBB21DD		-- GE[3:0] -- 0010

	@ uadd16 r5, r1, r2
	@ sadd8 r6, r1, r2
	@ sadd16 r7, r1, r2		
	
	@ Rev instruction (Change Endianness)
	ldr r0, =0x11223344
	rev r1, r0					@ r1 will be 0x44332211

	@ Sign Extends
	ldr r0, =0x55AA8765	@ 01010101 10101010 10000111 01100101
	sxtb r1, r0			@ copy one byte and retain sign
						@ 00000000 00000000 00000000 01100101 --> r1
	sxth r2, r0			@ copy half-word (2 bytes) and retain sign
						@ 11111111 11111111 10000111 01100101 --> r2
	uxth r3, r0			@ copy half-word (2 bytes) and result keep positive
						@ 00000000 00000000 10000111 01100101
	
	@ Bit Field instructions -- Extract
	ldr r6, =0x11223344		@ 00010001 00100010 00110011 01000100
	ubfx r0, r6, #4, #12	@ r6[15:4] --> r0[11:0] (copy 12 bits from bit 4 of r6)
							@ r0 will be 0x00000334
	
	@ Bit Field instructions -- Clear
	ldr r6, =0x11223344
	bfc r6, #8, #16			@ clear 16 bits from bit 8 of r6
							@ r6 = 0x11000044
	
	@ Bit Field instructions -- Insert
	@ r6 = 0x11000044
	mov r2, #0x12
	bfi r6, r2, #8, #8		@ r6 = 0x11001244

	mov r7, #0x1234			@ 00000000 00000000 00010010 00110100
	clz r0, r7				@ 19 leading 0 bits, so r0 will be 19
	
	mov pc, lr

/***************************************************************/

.type Default_Handler, %function
Default_Handler:
	halt: b halt

.end

