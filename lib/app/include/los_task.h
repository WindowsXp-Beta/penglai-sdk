#ifndef _LOS_TASK_H
#define _LOS_TASK_H

#include "los_compiler.h"

/**
 * @ingroup los_task
 * Maximum number of tasks.
 *
 */
extern UINT32               g_taskMaxNum;

extern NORETURN VOID LOS_Panic(const CHAR *fmt, ...);

#endif