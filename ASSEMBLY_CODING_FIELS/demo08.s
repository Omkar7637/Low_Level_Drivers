
.section .data

# Timer registers
TIMER_CTRL_ADDR:    .word   0x10008000   # Address for the timer control register
TIMER_VALUE_ADDR:   .word   0x10008008   # Address for the timer value register
MTIMECMP_ADDR:      .word   0x10008018   # Address for the memory-mapped compare register
MIE_ADDR:           .word   0x300

# Constants
.equ TIMER_INTERVAL, 5000     # Set the timer interval for 5000 cycles

.section .text

.globl _start
.globl _timer_isr

_start:
    # Set up timer
    la t0, TIMER_CTRL_ADDR
    li t1, 0x80         # Enable the timer interrupt
    sw t1, 0(t0)

    la t0, TIMER_VALUE_ADDR
    li t1, TIMER_INTERVAL
    sw t1, 0(t0)

    # Set up timer interrupt handler
    la t0, _timer_isr
    la t1, MTIMECMP_ADDR
    sw t0, 0(t1)

    # Enable machine interrupts
    li t0, 0x8
    la t1, MIE_ADDR
    csrrs t0, mstatus, t0
    sw t0, 0(t1)

    # Wait for interrupts
    wfi

_timer_isr:
    # Your timer interrupt handling code goes here

    # Acknowledge the interrupt by writing a new compare value
    la t0, MTIMECMP_ADDR
    la t1, TIMER_INTERVAL
    add t2, t1, a0
    sw t2, 0(t0)

    # Return from interrupt
    mret
