#ifndef _LOS_CONTEXT_H
#define _LOS_CONTEXT_H

#include "los_compiler.h"
#include "los_interrupt.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup  los_context
 * @brief: Task stack initialization.
 *
 * @par Description:
 * This API is used to initialize the task stack.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param  taskID     [IN] Type#UINT32: TaskID.
 * @param  stackSize  [IN] Type#UINT32: Total size of the stack.
 * @param  topStack   [IN] Type#VOID *: Top of task's stack.
 *
 * @retval: context Type#TaskContext *.
 * @par Dependency:
 * <ul><li>los_context.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID *HalTskStackInit(UINT32 taskID, UINT32 stackSize, VOID *topStack);

/**
 * @ingroup  los_context
 * @brief: Function to sys exit.
 *
 * @par Description:
 * This API is used to sys exit.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param  None.
 *
 * @retval: None.
 * @par Dependency:
 * <ul><li>los_context.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
LITE_OS_SEC_TEXT_MINOR NORETURN VOID HalSysExit(VOID);

/**
 * @ingroup  los_context
 * @brief: Task scheduling Function.
 *
 * @par Description:
 * This API is used to scheduling task.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param  None.
 *
 * @retval: None.
 * @par Dependency:
 * <ul><li>los_context.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID HalTaskSchedule(VOID);

typedef VOID (*OS_TICK_HANDLER)(VOID);
UINT32 HalStartSchedule(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_CONTEXT_H */
