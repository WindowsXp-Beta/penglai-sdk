#include "soc.h"

.macro PUSH_CALLER_REG
    addi  sp, sp, -(INT_SIZE_ON_STACK)
    SREG  t6, 16 * REGBYTES(sp)
    SREG  t5, 17 * REGBYTES(sp)
    SREG  t4, 18 * REGBYTES(sp)
    SREG  t3, 19 * REGBYTES(sp)
    SREG  a7, 20 * REGBYTES(sp)
    SREG  a6, 21 * REGBYTES(sp)
    SREG  a5, 22 * REGBYTES(sp)
    SREG  a4, 23 * REGBYTES(sp)
    SREG  a3, 24 * REGBYTES(sp)
    SREG  a2, 25 * REGBYTES(sp)
    SREG  a1, 26 * REGBYTES(sp)
    SREG  a0, 27 * REGBYTES(sp)
    SREG  t2, 28 * REGBYTES(sp)
    SREG  t1, 29 * REGBYTES(sp)
    SREG  t0, 30 * REGBYTES(sp)
    SREG  ra, 31 * REGBYTES(sp)
.endm

.macro EAPP_RESERVE_REG
    addi sp, sp, -256
    SREG ra, 1 * REGBYTES(sp)
    SREG gp, 3 * REGBYTES(sp)
    SREG tp, 4 * REGBYTES(sp)
    SREG t0, 5 * REGBYTES(sp)
    SREG t1, 6 * REGBYTES(sp)
    SREG t2, 7 * REGBYTES(sp)
    SREG s0, 8 * REGBYTES(sp)
    SREG s1, 9 * REGBYTES(sp)
    SREG a0, 10 * REGBYTES(sp)
    SREG a1, 11 * REGBYTES(sp)
    SREG a2, 12 * REGBYTES(sp)
    SREG a3, 13 * REGBYTES(sp)
    SREG a4, 14 * REGBYTES(sp)
    SREG a5, 15 * REGBYTES(sp)
    SREG a6, 16 * REGBYTES(sp)
    SREG a7, 17 * REGBYTES(sp)
    SREG s2, 18 * REGBYTES(sp)
    SREG s3, 19 * REGBYTES(sp)
    SREG s4, 20 * REGBYTES(sp)
    SREG s5, 21 * REGBYTES(sp)
    SREG s6, 22 * REGBYTES(sp)
    SREG s7, 23 * REGBYTES(sp)
    SREG s8, 24 * REGBYTES(sp)
    SREG s9, 25 * REGBYTES(sp)
    SREG s10, 26 * REGBYTES(sp)
    SREG s11, 27 * REGBYTES(sp)
    SREG t3, 28 * REGBYTES(sp)
    SREG t4, 29 * REGBYTES(sp)
    SREG t5, 30 * REGBYTES(sp)
    SREG t6, 31 * REGBYTES(sp)
.endm

.extern memset
.global main
.section .text._start
.align 4
main:
    EAPP_RESERVE_REG

    li    t0, RISCV_SSTATUS_SIE
    csrw  sstatus, t0
    la    t0, HalTrapVector
    csrw  stvec, t0      # direct mode

/*
    // NOTE(cyx): gp has been set in `musl/arch/riscv64/crt_arch.h`.
    .option push
    .option norelax
    la    gp, __global_pointer$
    .option pop
*/

/*
    la    t0, __bss_start
    la    t1, __bss_end
2:
    sw    zero, 0x0(t0)
    addi  t0, t0, 0x4
    bgtu  t1, t0, 2b
*/

    // NOTE(cyx): We assume that the kernel stack is large enough.
    // la    sp, __start_and_irq_stack_top

    call  LiteOS_main
