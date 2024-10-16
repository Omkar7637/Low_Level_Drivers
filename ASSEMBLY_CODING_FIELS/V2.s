/* *************************************************************************
**  Target      : Cortex-M3
**  Environment : GNU Tools
*************************************************************************
*/
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
// uint32_t arr1[] = { 11, 22, 33, 44, 55 };
arr1:	.word 11
		.word 22
		.word 33
		.word 44
		.word 55

.section .bss
// uint32_t arr2[5];
arr2:	.skip (5*4)

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
/*
	mov r0, #0				// r0 = 0;
	mov r3, #0				// r3 = 0; (loop counter)
	ldr r7, =arr1			// r7 = &arr1;
loop:
	cmp r3, #5				// if r3 >= 5, 
	bge loop_end				//		goto loop_end
	ldr r1, [r7]				//		r1 = *r7;
	add r7, #4					//		r7 = r7 + 4;
	add r0, r1					//		r0 = r0 + r1;
	add r3, #1					//		r3 = r3 + 1;
	b loop				// repeat loop
loop_end:
*/

/*
	// access values using post-indexing
	mov r0, #0				// r0 = 0;
	mov r3, #0				// r3 = 0; (loop counter)
	ldr r7, =arr1			// r7 = &arr1;
loop:
	cmp r3, #5				// if r3 >= 5, 
	bge loop_end				//		goto loop_end
	ldr r1, [r7], #4			//		r1 = *r7 and then r7 = r7 + 4;
	add r0, r1					//		r0 = r0 + r1;
	add r3, #1					//		r3 = r3 + 1;
	b loop				// repeat loop
loop_end:
*/

/*
	// access values using pre-indexing
	mov r0, #0				// r0 = 0;
	mov r3, #0				// r3 = 0; (loop counter)
	ldr r7, =arr1			// r7 = &arr1;
loop:
	cmp r3, #5				// if r3 >= 5, 
	bge loop_end				//		goto loop_end
	//mul r4, r3, #4			//		r4 = r3 * 4;
	lsl r4, r3, #2				//		r4 = r3 * 4;
	ldr r1, [r7, r4]			//		r1 = *(r7 + r4)
	add r0, r1					//		r0 = r0 + r1;
	add r3, #1					//		r3 = r3 + 1;
	b loop				// repeat loop
loop_end:
*/

/*
	// access values using pre-indexing
	mov r0, #0				// r0 = 0;
	mov r3, #0				// r3 = 0; (loop counter)
	ldr r7, =arr1			// r7 = &arr1;
loop:
	cmp r3, #5				// if r3 >= 5, 
	bge loop_end				//		goto loop_end
	ldr r1, [r7, r3, lsl #2]	//		r1 = *(r7 + (r3 * 4))
	add r0, r1					//		r0 = r0 + r1;
	add r3, #1					//		r3 = r3 + 1;
	b loop				// repeat loop
loop_end:
*/

	// access values using pre-indexing with update (addr update)
	mov r0, #0				// r0 = 0;
	mov r3, #0				// r3 = 0; (loop counter)
	ldr r7, =arr1			// r7 = &arr1;
	sub r7, #4				// r7 = r7 - 4; so that first preindexing will access first ele i.e. 11
loop:
	cmp r3, #5				// if r3 >= 5, 
	bge loop_end				//		goto loop_end
	ldr r1, [r7, #4]!			//		r7 = r7 + 4; and then r1 = *r7;
	add r0, r1					//		r0 = r0 + r1;
	add r3, #1					//		r3 = r3 + 1;
	b loop				// repeat loop
loop_end:

	mov pc, lr

/***************************************************************/

.type Default_Handler, %function
Default_Handler:
	halt: b halt

.end

