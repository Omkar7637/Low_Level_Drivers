.global _start

.section .data
# uint32_t arr[5] = { 11, 22, 33, 44, 55 }
arr:	.word	11
		.word	22
		.word	33
		.word	44
		.word	55

.section .bss

.section .text
_start:
	# r4 = arr
	la t4, arr
	# r1 = 0
	li t1, 0
	# r7 = 0
	li t3, 0

    # Load the address of the array into a register
    la t0, arr

	# Load array size into a register
	li t5, 5

    # Loop to iterate through the array
    li t1, 0          # Initialize loop counter

	# Sum array elements
	li t6, 0			# t6 = 0

loop_start:
    # Access the array element at the current index (t1)
    lw t2, 0(t0)      # Load the element into t2

	# Add element into accumulated sum
	add t6, t6, t2		# t6 = t6 + t2

    # Increment the loop counter
    addi t1, t1, 1

    # Check if the end of the array is reached
    bge t1, t5, loop_end

    # Calculate the next address in the array (4 bytes per element)
    add t0, t0, 4

    # Repeat the loop
    j loop_start

loop_end:
	addi a7, zero, 93
	add a0, zero, t6
	ecall
