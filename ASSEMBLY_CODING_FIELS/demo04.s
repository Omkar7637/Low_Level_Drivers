.global _start

_start:
	# r2 = 5
	li t2, 5
	# r1 = 1
	li t1, 1
	# r7 = 1
	li t3, 1

loop:
	# while (r7 <= r2)
	bgt t3, t2, loop_end

	# r1 = r1 * r7
	mul t1, t1, t3

	# r7++
	addi t3, t3, 1

	# branch to loop
	j loop

loop_end:
	# exit(t1); // 120
	addi a7, zero, 93
	add a0, zero, t1
	ecall
