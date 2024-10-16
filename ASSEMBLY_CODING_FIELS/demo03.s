.global _start

_start:
    # r1 = 21
    li  t1, 21
    # r2 = 23
    li  t2, 23

    # Compare/difference r1 and r2 and Branch if greater than or equal
    bge t1, t2, greater_than

    # r3 = r2 if r1 <= r2
    mv  t3, t2
    j   end

greater_than:
    # r3 = r1 if r1 > r2
    mv  t3, t1

end:
	addi a7, zero, 93
	add a0, zero, t3
	ecall
