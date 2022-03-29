.section .text

systick_timer_handler:
    /* Jump to threadx timer handler */
    j _tx_timer_interrupt_handler

default_exc_handler:
    jal x0, default_exc_handler

reset_handler:
    /* Set all registers to zero */
    mv  x1, x0
    mv  x2, x1
    mv  x3, x1
    mv  x4, x1
    mv  x5, x1
    mv  x6, x1
    mv  x7, x1
    mv  x8, x1
    mv  x9, x1
    mv x10, x1
    mv x11, x1
    mv x12, x1
    mv x13, x1
    mv x14, x1
    mv x15, x1
    mv x16, x1
    mv x17, x1
    mv x18, x1
    mv x19, x1
    mv x20, x1
    mv x21, x1
    mv x22, x1
    mv x23, x1
    mv x24, x1
    mv x25, x1
    mv x26, x1
    mv x27, x1
    mv x28, x1
    mv x29, x1
    mv x30, x1
    mv x31, x1

    /* Clear CSRs */
    csrwi mepc,    0
    csrwi mstatus, 0
    csrwi mie,     0

    /* Stack initilization */
    la   x2, _stack_start

_start:
.global _start
    /* Clear BSS */
    la x26, _bss_start
    la x27, _bss_end

    bge x26, x27, zero_loop_end

zero_loop:
    sw x0, 0(x26)
    addi x26, x26, 4
    ble x26, x27, zero_loop
    zero_loop_end:

main_entry:
    /* Jump to main program entry point (argc = argv = 0) */
    addi x10, x0, 0
    addi x11, x0, 0
    jal x1, main

sleep_loop:
    j sleep_loop

/* =============== Exceptions =============== */

.section .vectors, "ax"
.option norvc;

.org 0x00
.rept 7
jal x0, default_exc_handler
.endr

/* Systick handler */
jal x0, systick_timer_handler

.rept 23
jal x0, default_exc_handler
.endr

/* Reset vector */
.org 0x80
jal x0, reset_handler

/* Illegal instruction exception */
.org 0x84
jal x0, default_exc_handler

/* Ecall handler */
.org 0x88
jal x0, default_exc_handler

