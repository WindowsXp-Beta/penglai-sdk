#include "los_arch_context.h"
#include "los_arch_interrupt.h"
#include "los_arch_timer.h"
#include "los_context.h"
#include "los_sched.h"
#include "los_task.h"
#include "print.h"

STATIC UINT32 g_sysNeedSched = FALSE;

LITE_OS_SEC_TEXT_INIT VOID HalArchInit(VOID)
{
    UINT32 ret;
    HalHwiInit();

    ret = HalTickStart();
    PRINT_INFO("After LiteOS HalTickStart\n");
    if (ret != LOS_OK) {
        PRINT_ERR("Tick start failed!\n");
        return;
    }
}

VOID HalIrqEndCheckNeedSched(VOID)
{
    if (g_sysNeedSched) {
        LOS_Schedule();
    }
}

VOID HalTaskSchedule(VOID)
{
    UINT64 intSave;

    if (OS_INT_ACTIVE) {
        g_sysNeedSched = TRUE;
        return;
    }

    intSave = LOS_IntLock();
    g_sysNeedSched = FALSE;
    BOOL isSwitch = OsSchedTaskSwitch();
    if (isSwitch) {
        HalTaskContextSwitch(intSave);
        return;
    }

    LOS_IntRestore(intSave);
    return;
}

/* ****************************************************************************
 Function    : HalSysExit
 Description : Task exit function
 Input       : None
 Output      : None
 Return      : None
 **************************************************************************** */
LITE_OS_SEC_TEXT_MINOR VOID HalSysExit(VOID)
{
    LOS_IntLock();
    while (1) {
    }
}

LITE_OS_SEC_TEXT_INIT VOID *HalTskStackInit(UINT32 taskID, UINT64 stackSize, VOID *topStack)
{
    UINT64 index;
    TaskContext  *context = NULL;

    /* initialize the task stack, write magic num to stack top */
    for (index = 1; index < (stackSize / sizeof(UINT64)); index++) {
        *((UINT64 *)topStack + index) = OS_TASK_STACK_INIT;
    }
    *((UINT64 *)(topStack)) = OS_TASK_MAGIC_WORD;

    context = (TaskContext *)(((UINTPTR)topStack + stackSize) - sizeof(TaskContext));

    context->sstatus = RISCV_SSTATUS_SPP | RISCV_SSTATUS_SPIE;
    context->sepc = (UINT64)(UINTPTR)OsTaskEntry;
    context->tp = TP_INIT_VALUE;
    context->sp = SP_INIT_VALUE;
    context->s11 = S11_INIT_VALUE;
    context->s10 = S10_INIT_VALUE;
    context->s9 = S9_INIT_VALUE;
    context->s8 = S8_INIT_VALUE;
    context->s7 = S7_INIT_VALUE;
    context->s6 = S6_INIT_VALUE;
    context->s5 = S5_INIT_VALUE;
    context->s4 = S4_INIT_VALUE;
    context->s3 = S3_INIT_VALUE;
    context->s2 = S2_INIT_VALUE;
    context->s1 = S1_INIT_VALUE;
    context->s0 = FP_INIT_VALUE;
    context->t6 = T6_INIT_VALUE;
    context->t5 = T5_INIT_VALUE;
    context->t4 = T4_INIT_VALUE;
    context->t3 = T3_INIT_VALUE;
    context->a7 = A7_INIT_VALUE;
    context->a6 = A6_INIT_VALUE;
    context->a5 = A5_INIT_VALUE;
    context->a4 = A4_INIT_VALUE;
    context->a3 = A3_INIT_VALUE;
    context->a2 = A2_INIT_VALUE;
    context->a1 = A1_INIT_VALUE;
    context->a0 = taskID;
    context->t2 = T2_INIT_VALUE;
    context->t1 = T1_INIT_VALUE;
    context->t0 = T0_INIT_VALUE;
    context->ra = (UINT64)(UINTPTR)HalSysExit;
    return (VOID *)context;
}

LITE_OS_SEC_TEXT_INIT UINT32 HalStartSchedule(VOID)
{
    (VOID)LOS_IntLock();
    OsSchedStart();
    HalStartToRun();
    return LOS_OK; /* never return */
}

LITE_OS_SEC_TEXT VOID wfi(VOID)
{
    __asm__ __volatile__("wfi");
}

LITE_OS_SEC_TEXT VOID mb(VOID)
{
    __asm__ __volatile__("fence":::"memory");
}

LITE_OS_SEC_TEXT VOID dsb(VOID)
{
    __asm__ __volatile__("fence":::"memory");
}