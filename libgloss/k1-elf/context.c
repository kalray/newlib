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

#include <k1c/context.h>
#include <k1c/registers.h>

unsigned int __k1_get_privilege_level(void)
{
  return K1_SFR_GET_FIELD(__builtin_k1_get(K1_SFR_PS), PS_PL);
}

void __k1_ctx_save(__k1_context_t *to __attribute__((unused)))
{

}

void __k1_ctx_restore(__k1_context_t *from __attribute__((unused)), __k1_context_t *to __attribute__((unused)))
{
}

void __k1_ctx_load(__k1_context_t *from __attribute__((unused)))
{

}

void __k1_switch_to_smem_user(void)
{
  unsigned int privilege_level = __k1_get_privilege_level();

  if (privilege_level != 3) {

    unsigned int relative_pl = 3 - privilege_level;

    // $sps should already have been set to a good value during mbrt init => just set $sps.PL to the needed relative value, and RFE
    __builtin_k1_wfxl(K1_SFR_SPS, ((unsigned long long)relative_pl << 32 | K1_SFR_PS_PL_MASK));

    __builtin_k1_set(K1_SFR_EV_PL3, __builtin_k1_get(K1_SFR_EV));

    __asm__ __volatile__ (
			  "make $r1 = spc_label\n"
			  ";;\n"
			  "set $spc = $r1\n"
			  ";;\n"
			  "rfe\n"
			  ";;\n"
			  "spc_label:\n"
			  : /* no outputs */ : : "r1");
  }
}
