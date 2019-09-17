/*
 * Copyright 2019
 * Kalray Inc. All rights reserved.
 *
 * This software is furnished under license and may be used and copied only
 * in accordance with the following terms and conditions.  Subject to these
 * conditions, you may download, copy, install, use, modify and distribute
 * modified or unmodified copies of this software in source and/or binary
 * form. No title or ownership is transferred hereby.
 *
 * 1) Any source code used, modified or distributed must reproduce and
 *    retain this copyright notice and list of conditions as they appear in
 *    the source file.
 *
 * 2) No right is granted to use any trade name, trademark, or logo of
 *    Kalray Inc.  The "Kalray Inc" name may not be
 *    used to endorse or promote products derived from this software
 *    without the prior written permission of Kalray Inc.
 *
 * 3) THIS SOFTWARE IS PROVIDED "AS-IS" AND ANY EXPRESS OR IMPLIED
 *    WARRANTIES, INCLUDING BUT NOT LIMITED TO, ANY IMPLIED WARRANTIES OF
 *    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 *    NON-INFRINGEMENT ARE DISCLAIMED. IN NO EVENT SHALL KALRAY BE LIABLE
 *    FOR ANY DAMAGES WHATSOEVER, AND IN PARTICULAR, KALRAY SHALL NOT BE
 *    LIABLE FOR DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *    OR OTHERWISE), EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _K1_SYSCALL_H
#define _K1_SYSCALL_H

#include <stdint.h>

/*
 * Syscalls.
 */

/**
 * \fn uint64_t __k1_syscall(const __k1_uint32_t syscall)
 * \brief Do syscall with no arguments
 * \param syscall Syscall number
 * \return Result of the syscall
 */
extern uint64_t __k1_syscall(const uint32_t syscall_nb);

/**
 * \fn uint64_t __k1_syscall_with_args(const uint64_t syscall, uint64_t sc_arg0,
 *                       uint64_t sc_arg1,uint64_t sc_arg2,
 *                       uint64_t sc_arg3, uint64_t sc_arg4,
 *                       uint64_t sc_arg5)
 * \brief Do syscall with 6 arguments
 * \param syscall Syscall number
 * \param sc_arg0 First syscall argument
 * \param sc_arg1 Second syscall argument
 * \param sc_arg2 Third syscall argument
 * \param sc_arg3 Fourth syscall argument
 * \param sc_arg4 Fifth syscall argument
 * \param sc_arg5 Sixth syscall argument
 * \return Result of the syscall
 */
extern uint64_t __k1_syscall_with_args(const uint32_t syscall_nb,
                    uint64_t sc_arg0, uint64_t sc_arg1, uint64_t sc_arg2,
                    uint64_t sc_arg3, uint64_t sc_arg4, uint64_t sc_arg5);

#endif      /* ndef _K1_SYSCALL_H */
