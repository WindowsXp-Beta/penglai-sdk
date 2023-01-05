#include "eapp.h"
#include "print.h"
#include "los_compiler.h"
#include "los_task.h"
#include "riscv_asm.h"
#include "riscv_encoding.h"

static void TaskSampleEntry2(void)
{
    while(1) {
        eapp_print("TaskSampleEntry2 running...\n\r");
        LOS_TaskDelay(1000);
    }
}


static void TaskSampleEntry1(void)
{
    while(1) {
        eapp_print("TaskSampleEntry1 running...\n\r");
        LOS_TaskDelay(1000);
    }
}

unsigned int LosAppInit(VOID)
{
    unsigned int ret;
    unsigned int taskID1, taskID2;
    TSK_INIT_PARAM_S task1 = { 0 };
    task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskSampleEntry1;
    task1.uwStackSize  = 0x1000;
    task1.pcName       = "TaskSampleEntry1";
    task1.usTaskPrio   = 6;
    ret = LOS_TaskCreate(&taskID1, &task1);
    if (ret != LOS_OK) {
        eapp_print("Create Task failed! ERROR: 0x%x\n", ret);
        return ret;
    }

    task1.pfnTaskEntry = (TSK_ENTRY_FUNC)TaskSampleEntry2;
    task1.uwStackSize  = 0x1000;
    task1.pcName       = "TaskSampleEntry2";
    task1.usTaskPrio   = 7;
    ret = LOS_TaskCreate(&taskID2, &task1);
    if (ret != LOS_OK) {
        eapp_print("Create Task failed! ERROR: 0x%x\n", ret);
    }

    eapp_print("Task created! taskID1 = %u, taskID2 = %u\n", taskID1, taskID2);

    return ret;
}


/*****************************************************************************
 Function    : main
 Description : Main function entry
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
INT32 LiteOS_main(VOID)
{
    UINT32 ret;

    eapp_print("\n OHOS start \n\r");

    ret = LOS_KernelInit();
    if (ret != LOS_OK) {
        eapp_print("Liteos kernel init failed! ERROR: 0x%x\n", ret);
        goto START_FAILED;
    }

    eapp_print("Liteos kernel init success!\n");

    ret = LosAppInit();
    if (ret != LOS_OK) {
        eapp_print("LosAppInit failed! ERROR: 0x%x\n", ret);
        goto START_FAILED;
    }

    eapp_print("Liteos application init success!\n");

    LOS_Start();

START_FAILED:
    while (1) {
        __asm volatile("wfi");
    }
    
    EAPP_RETURN(ret);
}
