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

#include <kvx/syscall.h>

uint64_t __kvx_syscall(const uint32_t syscall_nb)
{
  register long ret __asm__("$r0");
  __asm__ __volatile__ ("scall %1\n\t;;"
			: "=r" (ret)
			: "ir" (syscall_nb)
			: "memory"); /* As we now make a fullish context backup, we only have to put memory into clobber */
  return (uint64_t)ret;
}

uint64_t __kvx_syscall_with_args(const uint32_t syscall_nb,
								uint64_t sc_arg0, uint64_t sc_arg1, uint64_t sc_arg2,
								uint64_t sc_arg3, uint64_t sc_arg4, uint64_t sc_arg5)
{
  register long arg0 __asm__("$r0")    = (long)sc_arg0;
  register long arg1 __asm__("$r1")    = (long)sc_arg1;
  register long arg2 __asm__("$r2")    = (long)sc_arg2;
  register long arg3 __asm__("$r3")    = (long)sc_arg3;
  register long arg4 __asm__("$r4")    = (long)sc_arg4;
  register long arg5 __asm__("$r5")    = (long)sc_arg5;
  __asm__ __volatile__ ("scall %6\n\t;;"
			: "+r" (arg0)
			: "r" (arg1), "r" (arg2), "r" (arg3), "r" (arg4), "r" (arg5), "ir" (syscall_nb)
			: "memory"); /* As we now make a fullish context backup, we only have to put memory into clobber */
  return (uint64_t)arg0;
}
