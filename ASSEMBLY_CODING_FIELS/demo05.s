.global _start

.section .data
num1:	.word	11		# uint32 num1 = 11;
num2:	.word	22		# uint32 num2 = 22;

.section .bss
num3:	.skip	4

.section .text
_start:
	# r5 = &num1;
	la t5, num1
	# r1 = *r5;
	lw t1, 0(t5)

	# r6 = &num2;
	la t6, num2
	# r2 = *r6;
	lw t2, 0(t6)

	# r3 = r1 + r2;
	add t3, t1, t2

	# r7 = &num3;
	la t4, num3
	# *r7 = r3;
	sw t3, 0(t4)

	addi a7, zero, 93
	add a0, zero, t3
	ecall
