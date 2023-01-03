#include "eapp.h"
#include "print.h"
#include "los_compiler.h"
#include "riscv_asm.h"
#include "riscv_encoding.h"

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

	  volatile int dummy_count = 1000;
	  while (dummy_count) {dummy_count--;}

    EAPP_RETURN(ret);
//     if (ret != LOS_OK) {
//         printf("Liteos kernel init failed! ERROR: 0x%x\n", ret);
//         goto START_FAILED;
//     }

//     ret = LosAppInit();
//     if (ret != LOS_OK) {
//         printf("LosAppInit failed! ERROR: 0x%x\n", ret);
//     }

//     LOS_Start();

// START_FAILED:
//     while (1) {
//         __asm volatile("wfi");
//     }
}
