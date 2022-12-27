#include "soc.h"

.global  HalEnableIRQ
.global  HalDisableIRQ
.global  HalIntLock
.global  HalIntUnLock
.global  HalIntRestore
.global  HalStartToRun
.global  HalTaskContextSwitch
.extern  __irq_stack_top
.section .interrupt.text

.macro PUSH_ALL_REG
    addi sp, sp, -(32 * REGBYTES)
    SREG  t6, 2 * REGBYTES(sp)
    SREG  t5, 3 * REGBYTES(sp)
    SREG  t4, 4 * REGBYTES(sp)
    SREG  t3, 5 * REGBYTES(sp)
    SREG  t2, 6 * REGBYTES(sp)
    SREG  t1, 7 * REGBYTES(sp)
    SREG  t0, 8 * REGBYTES(sp)
    SREG  s11, 9 * REGBYTES(sp)
    SREG  s10, 10 * REGBYTES(sp)
    SREG  s9, 11 * REGBYTES(sp)
    SREG  s8, 12 * REGBYTES(sp)
    SREG  s7, 13 * REGBYTES(sp)
    SREG  s6, 14 * REGBYTES(sp)
    SREG  s5, 15 * REGBYTES(sp)
    SREG  a7, 18 * REGBYTES(sp)
    SREG  a6, 19 * REGBYTES(sp)
    SREG  a5, 20 * REGBYTES(sp)
    SREG  a4, 21 * REGBYTES(sp)
    SREG  a3, 22 * REGBYTES(sp)
    SREG  a2, 23 * REGBYTES(sp)
    SREG  a1, 24 * REGBYTES(sp)
    SREG  a0, 25 * REGBYTES(sp)
    SREG  s4, 26 * REGBYTES(sp)
    SREG  s3, 27 * REGBYTES(sp)
    SREG  s2, 28 * REGBYTES(sp)
    SREG  s1, 29 * REGBYTES(sp)
    SREG  s0, 30 * REGBYTES(sp)
    SREG  ra, 31 * REGBYTES(sp)
.endm

.macro POP_ALL_REG
    LREG  t6, 2 * REGBYTES(sp)
    LREG  t5, 3 * REGBYTES(sp)
    LREG  t4, 4 * REGBYTES(sp)
    LREG  t3, 5 * REGBYTES(sp)
    LREG  t2, 6 * REGBYTES(sp)
    LREG  t1, 7 * REGBYTES(sp)
    LREG  t0, 8 * REGBYTES(sp)
    LREG  s11, 9 * REGBYTES(sp)
    LREG  s10, 10 * REGBYTES(sp)
    LREG  s9, 11 * REGBYTES(sp)
    LREG  s8, 12 * REGBYTES(sp)
    LREG  s7, 13 * REGBYTES(sp)
    LREG  s6, 14 * REGBYTES(sp)
    LREG  s5, 15 * REGBYTES(sp)
    LREG  a7, 18 * REGBYTES(sp)
    LREG  a6, 19 * REGBYTES(sp)
    LREG  a5, 20 * REGBYTES(sp)
    LREG  a4, 21 * REGBYTES(sp)
    LREG  a3, 22 * REGBYTES(sp)
    LREG  a2, 23 * REGBYTES(sp)
    LREG  a1, 24 * REGBYTES(sp)
    LREG  a0, 25 * REGBYTES(sp)
    LREG  s4, 26 * REGBYTES(sp)
    LREG  s3, 27 * REGBYTES(sp)
    LREG  s2, 28 * REGBYTES(sp)
    LREG  s1, 29 * REGBYTES(sp)
    LREG  s0, 30 * REGBYTES(sp)
    LREG  ra, 31 * REGBYTES(sp)
    addi  sp, sp, 32 * REGBYTES
.endm

/*
// not sure, see doc
HalTaskContextSwitch:
    PUSH_ALL_REG

    // clear spie
    li   a2, RISCV_SSTATUS_SPIE
    not  a2, a2
    and  a0, a0, a2

    // get sie
    andi a1, a0, RISCV_SSTATUS_SIE

    // must be in supervisor mode
    ori  a1, a1, 0x10
    slli a1, a1, 0x4
    or   a0, a0, a1

    // clear sie
    li   a2, RISCV_SSTATUS_SIE
    not  a2, a2
    and  a0, a0, a2

    SREG a0, 16 * REGBYTES(sp)
    SREG ra, 17 * REGBYTES(sp)

    la   a1, g_losTask
    ld   a0, 0(a1)
    sd   sp, TASK_CB_KERNEL_SP(a0)

    ld   a0, 8(a1)
    sd   a0, 0(a1)

HalStartToRun:
    la   a1, g_losTask
    ld   a0, 8(a1)
*/
// retireve stack pointer
    ld      sp, TASK_CB_KERNEL_SP(a0)

// enable global interrupts
    ld      t0, 16 * REGBYTES(sp)
    csrw    sstatus, t0

// retrieve the address at which exception happened
    lw      t0, 17 * REGBYTES(sp)
    csrw    sepc, t0

// retrieve the registers
    POP_ALL_REG

    sret

.section .text
HalDisableIRQ:
    li      t0, (RISCV_SSTATUS_SPIE | RISCV_SSTATUS_SIE) // spie | sie
    csrrc   zero, sstatus, t0
    ret

HalEnableIRQ:
    csrsi  sstatus, RISCV_SSTATUS_SIE
    ret

HalIntLock:
    csrr    a0, sstatus           // return value
    li      t0, RISCV_SSTATUS_SIE   // sie
    csrrc   zero, sstatus, t0
    ret


HalIntUnLock:
    csrr    a0, sstatus           // return value
    li      t0, RISCV_SSTATUS_SIE   // sie
    csrrs   zero, sstatus, t0
    ret

HalIntRestore:
    csrw sstatus, a0
    ret
