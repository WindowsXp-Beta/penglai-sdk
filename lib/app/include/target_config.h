#ifndef _TARGETS_CONFIG_H
#define _TARGETS_CONFIG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define OS_SYS_CLOCK                                  10000000UL

#define LOSCFG_BASE_CORE_TICK_PER_SECOND              1000

/****************************** System clock module configuration ****************************/
#define LOSCFG_BASE_CORE_TIMER_NUM                      7

/****************************** Task module configuration ********************************/
#define LOSCFG_BASE_CORE_TSK_LIMIT                      20            // max num task
#define LOSCFG_BASE_CORE_TSK_IDLE_STACK_SIZE            (0x500U)      // IDLE task stack
#define LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE         (0x2D0U)      // default stack
#define LOSCFG_BASE_CORE_TSK_MIN_STACK_SIZE             (0x130U)
#define LOSCFG_BASE_CORE_TIMESLICE                      1             // task-ROBIN moduel cutting switch
#define LOSCFG_BASE_CORE_TIMESLICE_TIMEOUT              10
/****************************** Semaphore module configuration ******************************/
#define LOSCFG_BASE_IPC_SEM                             0
#define LOSCFG_BASE_IPC_SEM_LIMIT                       10              // the max sem-numb
/****************************** mutex module configuration ******************************/
#define LOSCFG_BASE_IPC_MUX                             0
#define LOSCFG_BASE_IPC_MUX_LIMIT                       10              // the max mutex-num
/****************************** Queue module configuration ********************************/
#define LOSCFG_BASE_IPC_QUEUE                           0
#define LOSCFG_BASE_IPC_QUEUE_LIMIT                     10              //the max queue-numb

/****************************** Software timer module configuration **************************/
#define LOSCFG_BASE_CORE_SWTMR                          0
#define LOSCFG_BASE_CORE_SWTMR_LIMIT                    10				// the max SWTMR numb

/****************************** Memory module configuration **************************/
#define LOSCFG_MEM_MUL_POOL                             0
#define OS_SYS_MEM_NUM                                  20
/*=============================================================================
                                       Exception module configuration
=============================================================================*/
#define LOSCFG_PLATFORM_EXC                             0
/* =============================================================================
                                       printf module configuration
============================================================================= */
#define LOSCFG_KERNEL_PRINTF                            1

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif /* _TARGETS_CONFIG_H */
