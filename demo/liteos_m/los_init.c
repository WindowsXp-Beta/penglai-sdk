#include "los_compiler.h"
#include "print.h"

/*****************************************************************************
 Function    : LOS_KernelInit
 Description : System kernel initialization function, configure all system modules
 Input       : None
 Output      : None
 Return      : LOS_OK on success or error code on failure
 *****************************************************************************/
UINT32 LOS_KernelInit(VOID)
{
    UINT32 ret;
    PRINTK("entering kernel init...\n");
    return LOS_OK;
#if 0
#if (LOSCFG_BACKTRACE_TYPE != 0)
    OSBackTraceInit();
#endif

    OsRegister();
    ret = OsMemSystemInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsMemSystemInit error %u\n", ret);
        return ret;
    }

    HalArchInit();

    ret = OsTaskInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsTaskInit error\n");
        return ret;
    }

#if (LOSCFG_BASE_CORE_TSK_MONITOR == 1)
    OsTaskMonInit();
#endif

#if (LOSCFG_BASE_CORE_CPUP == 1)
    ret = OsCpupInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsCpupInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_SEM == 1)
    ret = OsSemInit();
    if (ret != LOS_OK) {
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_MUX == 1)
    ret = OsMuxInit();
    if (ret != LOS_OK) {
        return ret;
    }
#endif

#if (LOSCFG_BASE_IPC_QUEUE == 1)
    ret = OsQueueInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsQueueInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_BASE_CORE_SWTMR == 1)
    ret = OsSwtmrInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsSwtmrInit error\n");
        return ret;
    }
#endif

    ret = OsIdleTaskCreate();
    if (ret != LOS_OK) {
        return ret;
    }

#if (LOSCFG_KERNEL_TRACE == 1)
    ret = OsTraceInit(LOSCFG_TRACE_BUFFER_SIZE);
    if (ret != LOS_OK) {
        PRINT_ERR("OsTraceInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_KERNEL_PM == 1)
    ret = OsPmInit();
    if (ret != LOS_OK) {
        PRINT_ERR("Pm init failed!\n");
        return ret;
    }
#endif

#if (LOSCFG_TEST == 1)
    ret = los_TestInit();
    if (ret != LOS_OK) {
        PRINT_ERR("los_TestInit error\n");
        return ret;
    }
#endif

#if (LOSCFG_PLATFORM_EXC == 1)
    OsExcMsgDumpInit();
#endif

#if (LOSCFG_DYNLINK == 1)
    ret = LOS_DynlinkInit();
    if (ret != LOS_OK) {
        return ret;
    }
#endif

    return LOS_OK;
#endif
}
