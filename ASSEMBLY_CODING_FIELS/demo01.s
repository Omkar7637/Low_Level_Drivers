.global _start

_start:
    # r1 = 23
    li  t1, 23
    # r2 = 27
    li  t2, 27
    # r0 = r1 + r2
    add t0, t1, t2

    # r1 = 23
    li  t1, 23
    # r2 = 27
    li  t2, 27
    # r0 = r1 - r2
    sub t0, t1, t2

    # r1 = 12
    li  t1, 12
    # r2 = 5
    li  t2, 5
    # r0 = r1 * r2
    mul t0, t1, t2
    # Output: r0 = 60

    # r1 = 27
    li  t1, 27
    # r2 = 4
    li  t2, 4
    # r0 = r1 / r2
    divu t0, t1, t2
    # Output: r0 = 6

	addi a7, zero, 93
	addi a0, zero, 0
	ecall
