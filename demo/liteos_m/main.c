#include "eapp.h"
#include "print.h"
#include "los_compiler.h"

int prime_loop(int num)
{
  unsigned long count;
  int i;
  for(i = 2; i < num; i++)
  {
    if (num % i ==0)
      count++;
  }
  return count;
}

int prime(unsigned long * args)
{
  eapp_print("%s is running\n", "Prime");
  unsigned long ret;
  ret = prime_loop(111);
  EAPP_RETURN(ret);
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

// int EAPP_ENTRY main(){
//   unsigned long * args;
//   EAPP_RESERVE_REG;
//   LiteOS_main();
// }