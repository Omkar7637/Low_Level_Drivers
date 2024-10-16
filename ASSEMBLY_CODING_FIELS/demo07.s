
.text

.globl _add_numbers
_add_numbers:
    # Function prologue
    addi sp, sp, -4
    sw ra, 0(sp)

    # Arguments: a in a0, b in a1
    add a0, a0, a1  # a0 = a0 + a1 (result of addition)

    # Function epilogue
    lw ra, 0(sp)
    addi sp, sp, 4
    ret

.global _start
_start:
    # Example usage of the add_numbers function

    # Load the arguments (numbers to be added)
    li a0, 5         # Set the first number (e.g., 5)
    li a1, 7         # Set the second number (e.g., 7)

    # Call the add_numbers function
    call _add_numbers
    mv t0, a0        # Collect return value in t0

	addi a7, zero, 93
	add a0, zero, t0
	ecall
