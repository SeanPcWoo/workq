/**
 * @file
 * work_queue.
 * Verification using sylixos(tm) real-time operating system
 */

/*
 * Copyright (c) 2006-2018 SylixOS Group.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 4. This code has been or is applying for intellectual property protection
 *    and can only be used with acoinfo software products.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * Author: Wu.PengCheng <wupengcheng@acoinfo.com>
 *
 */
#define __SYLIXOS_KERNEL
#include "stdio.h"
#include "SylixOS.h"
#include "workq.h"

int taskq_data_update (struct taskq_struct *t, unsigned long data)
{
    if (!t) {
        return  (-1);
    }

    t->data = data;

    return  (0);
}

int taskq_schedule (struct taskq_struct *t)
{
    if (!t) {
        return  (-1);
    }
    return  API_WorkQueueInsert(t->job_q, 0,
                                t->func,(PVOID)t->data, NULL, NULL, NULL, NULL, NULL);
}

int taskq_init (struct taskq_struct *t, void (*func)(unsigned long), unsigned long data)
{
    if (!t || !func) {
        return  (-1);
    }

    if (!t->job_q_name) {
        t->job_q_name = JOB_Q_THREAD_DEFAULT_NAME;
    }

    t->job_q = API_WorkQueueCreate(t->job_q_name, 4096, FALSE, 0, NULL);
    if (!t->job_q) {
        return  (-1);
    }

    t->func = func;
    t->data = data;

    return  (0);
}

void taskq_deinit(struct taskq_struct *t)
{
    if (t && t->job_q) {
        API_WorkQueueDelete(t->job_q);
    }
}


