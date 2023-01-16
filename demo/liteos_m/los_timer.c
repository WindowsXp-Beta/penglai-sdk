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

#include "los_tick.h"
#include "los_timer.h"
#include "los_config.h"
#include "los_arch_interrupt.h"
#include "los_arch_timer.h"
#include "riscv_encoding.h"
#include "riscv_asm.h"
#include "print.h"

#ifndef TICK_CYCLE
#define TICK_CYCLE 6000000000
#endif

void HandleTimerIRQ()
{
    // eapp_print("\n Timer IRQ! \n\r");
    csr_clear(CSR_SIP, SIP_STIP);

    OsTickHandler();

    /*
     * Note(DD): uncomment the following line to enable multiple
     * 			 timer interrupts.
     * */
    EAPP_SET_TIMER(TICK_CYCLE);
}

WEAK UINT32 HalTickStart()
{
    UINT32 ret;

    ret = HalHwiCreate(RISCV_SUPE_TIMER_IRQ, 0x1, 0, (HWI_PROC_FUNC)HandleTimerIRQ, 0);
    if (ret != LOS_OK) {
        return ret;
    }

    csr_set(CSR_SIE, SIP_STIP);
    EAPP_SET_TIMER(TICK_CYCLE);

    return LOS_OK;
}

WEAK VOID HalSysTickReload(UINT64 nextResponseTime)
{
    UINT64 timeMax = (UINT64)LOSCFG_BASE_CORE_TICK_RESPONSE_MAX - 1;

    nextResponseTime = 
        csr_read(time) + nextResponseTime > timeMax ? timeMax - csr_read(time) : nextResponseTime;

    csr_clear(sie, RISCV_SIE_STIE);  // disable timer irq
    EAPP_SET_TIMER(nextResponseTime);
    csr_set(sie, RISCV_SIE_STIE);  // enable timer irq
}

WEAK UINT64 HalGetTickCycle(UINT32 *period)
{
    (VOID)period;
    return csr_read(time);
}

UINT32 HalEnterSleep(VOID)
{
    wfi();

    return LOS_OK;
}
