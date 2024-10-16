.global _start

_start:
    # Bitwise not operation -- 1's complement, 2's complement
    li  t1, 23             # r1 = 23
    not t2, t1            # r2 = ~r1   = -24 
    addi t2, t2, 1         # r2 = r2 + 1 = ~r1 + 1 = -23
    neg t3, t1             # t3 = -t1 (2's complement)  = -23

    # AND operation
    li  t1, 9              # r1 = 00000000 00000000 00000000 00001001
    li  t2, 5              # r2 = 00000000 00000000 00000000 00000101
    and t3, t1, t2         # r3 = 00000000 00000000 00000000 00000001 = 1

    # OR operation
    li  t1, 9              # r1 = 00000000 00000000 00000000 00001001
    li  t2, 5              # r2 = 00000000 00000000 00000000 00000101
    or t3, t1, t2          # r3 = 00000000 00000000 00000000 00001101 = 13

    # XOR operation
    li  t1, 9              # r1 = 00000000 00000000 00000000 00001001
    li  t2, 5              # r2 = 00000000 00000000 00000000 00000101
    xor t3, t1, t2         # r3 = 00000000 00000000 00000000 00001100 = 12

    # Bit clear operation
    li  t1, 0x0000FFFF     # r1 = 00000000 00000000 11111111 11111111
    li  t2, 0x00000080     # r2 = 00000000 00000000 00000000 10000000
    not t2, t2            # r2 = ~r2
    and t3, t1, t2         # r3 = r1 & ~r2 = 00000000 00000000 11111111 01111111 = 0x0000FF7F

    # Test a bit
    li  t5, 19
    andi t6, t5, 1         # if t5 is even, t6=0 (Z=1), if t5 is odd, t6=1 (Z=0).

	addi a7, zero, 93
	addi a0, zero, 0
	ecall
