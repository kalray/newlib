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

#include <fenv.h>

int feholdexcept(fenv_t *envp)
{
  /* Get the current environment ($cs) */
  fenv_t fe;
  asm volatile("get %0 = $cs" : "=r"(fe));

  /* Mask $cs status to keep exception flags and rounding mode only. */
  *envp = (fe & (FE_ALL_EXCEPT | FE_RND_MASK));

  /* The wfxl insn allows to set the least significant word of the
   * operated system register (here $cs), with 'FE_ALL_EXCEPT' as a
   * clear mask.
   */
  asm volatile ("wfxl $cs, %0" : : "r"(FE_ALL_EXCEPT) : "$cs");

  /* K1 does not raise FP traps so it is always in a "non-stop" mode */

  /* The above insn cannot fail (while the OS allows access to the
   * floating-point exception flags of the $cs register). Return
   * success.
   */
  return 0;
}
