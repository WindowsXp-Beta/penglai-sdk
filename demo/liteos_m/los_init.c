#include "los_compiler.h"
#include "los_task.h"
#include "los_memory.h"
#include "los_context.h"
#include "target_config.h"
#include "print.h"

/*****************************************************************************
 Function    : OsRegister
 Description : Configuring the maximum number of tasks
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
LITE_OS_SEC_TEXT_INIT static VOID OsRegister(VOID)
{
    // TODO(zhidong): remove comment after los_task.c is ported
    // g_taskMaxNum = LOSCFG_BASE_CORE_TSK_LIMIT + 1; /* Reserved 1 for IDLE */

    return;
}

LITE_OS_SEC_TEXT_INIT VOID LOS_Panic(const CHAR *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    PRINT_ERR(fmt, ap);
    va_end(ap);
    HalSysExit();
}

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

    OsRegister();
    ret = OsMemSystemInit();
    if (ret != LOS_OK) {
        PRINT_ERR("OsMemSystemInit error %u\n", ret);
        return ret;
    }

    // HalArchInit();

    // ret = OsTaskInit();
    // if (ret != LOS_OK) {
    //     PRINT_ERR("OsTaskInit error\n");
    //     return ret;
    // }

    // ret = OsIdleTaskCreate();
    // if (ret != LOS_OK) {
    //     return ret;
    // }

    return LOS_OK;
}
