/*
 * Copyright (c) 2013-2020, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _LOS_ARCH_CONTEXT_H
#define _LOS_ARCH_CONTEXT_H

#include "los_compiler.h"
#include "los_context.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/**
 * @ingroup los_arch_context
 * The initialization value of stack space.
 */
#define EMPTY_STACK                 0xCACA

#define TP_INIT_VALUE  0x0202020202020202LL
#define SP_INIT_VALUE  0x0303030303030303LL
#define S11_INIT_VALUE 0x0404040404040404LL
#define S10_INIT_VALUE 0x0505050505050505LL
#define S9_INIT_VALUE  0x0606060606060606LL
#define S8_INIT_VALUE  0x0707070707070707LL
#define S7_INIT_VALUE  0x0808080808080808LL
#define S6_INIT_VALUE  0x0909090909090909LL
#define S5_INIT_VALUE  0x1010101010101010LL
#define S4_INIT_VALUE  0x1111111111111111LL
#define S3_INIT_VALUE  0x1212121212121212LL
#define S2_INIT_VALUE  0x1313131313131313LL
#define S1_INIT_VALUE  0x1414141414141414LL
#define FP_INIT_VALUE  0x1515151515151515LL
#define T6_INIT_VALUE  0x1616161616161616LL
#define T5_INIT_VALUE  0x1717171717171717LL
#define T4_INIT_VALUE  0x1818181818181818LL
#define T3_INIT_VALUE  0x1919191919191919LL
#define A7_INIT_VALUE  0x2020202020202020LL
#define A6_INIT_VALUE  0x2121212121212121LL
#define A5_INIT_VALUE  0x2222222222222222LL
#define A4_INIT_VALUE  0x2323232323232323LL
#define A3_INIT_VALUE  0x2424242424242424LL
#define A2_INIT_VALUE  0x2525252525252525LL
#define A1_INIT_VALUE  0x2626262626262626LL
#define T2_INIT_VALUE  0x2828282828282828LL
#define T1_INIT_VALUE  0x2929292929292929LL
#define T0_INIT_VALUE  0x3030303030303030LL

/**
 * @ingroup los_arch_context
 * Define the type of a task context control block.
 */
typedef struct {
    UINT64 sp;
    UINT64 tp;
    UINT64 t6;
    UINT64 t5;
    UINT64 t4;
    UINT64 t3;
    UINT64 t2;
    UINT64 t1;
    UINT64 t0;
    UINT64 s11;
    UINT64 s10;
    UINT64 s9;
    UINT64 s8;
    UINT64 s7;
    UINT64 s6;
    UINT64 s5;
    UINT64 sstatus;
    UINT64 sepc;
    UINT64 a7;
    UINT64 a6;
    UINT64 a5;
    UINT64 a4;
    UINT64 a3;
    UINT64 a2;
    UINT64 a1;
    UINT64 a0;
    UINT64 s4;
    UINT64 s3;
    UINT64 s2;
    UINT64 s1;
    UINT64 s0;
    UINT64 ra;
} TaskContext;

STATIC INLINE UINTPTR GetSP(VOID)
{
    UINTPTR spSave;
    __asm__ __volatile__("mv %0, sp" : "=r"(spSave));
    return spSave;
}

STATIC INLINE UINTPTR GetFp(VOID)
{
    UINTPTR fpSave = 0;
    __asm__ __volatile__("mv %0, s0" : "=r"(fpSave));
    return fpSave;
}

extern VOID HalStartToRun(VOID);

extern VOID HalTaskContextSwitch(UINT32 intSave);

/**
 * @ingroup los_arch_context
 * @brief Wait for interrupt.
 *
 * @par Description:
 * <ul>
 * <li>This API is used to suspend execution until interrupt or a debug request occurs.</li>
 * </ul>
 * @attention None.
 *
 * @param None.
 *
 * @retval: None.
 *
 * @par Dependency:
 * los_arch_context.h: the header file that contains the API declaration.
 * @see None.
 */
extern VOID wfi(VOID);

/**
 * @ingroup los_arch_context
 * @brief: mem fence function.
 *
 * @par Description:
 * This API is used to fence for memory.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval:None.
 * @par Dependency:
 * <ul><li>los_arch_context.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID mb(VOID);

/**
 * @ingroup los_arch_context
 * @brief: mem fence function.
 *
 * @par Description:
 * This API is same as mb, it just for adaptation.
 *
 * @attention:
 * <ul><li>None.</li></ul>
 *
 * @param: None.
 *
 * @retval:None.
 * @par Dependency:
 * <ul><li>los_arch_context.h: the header file that contains the API declaration.</li></ul>
 * @see None.
 */
extern VOID dsb(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /* _LOS_ARCH_CONTEXT_H */
