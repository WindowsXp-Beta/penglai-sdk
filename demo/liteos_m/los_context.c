#include "los_arch_interrupt.h"
#include "los_context.h"
#include "print.h"

LITE_OS_SEC_TEXT_INIT VOID HalArchInit(VOID)
{
    UINT32 ret;
    HalHwiInit();

    ret = HalTickStart();
    if (ret != LOS_OK) {
        PRINT_ERR("Tick start failed!\n");
        return;
    }
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