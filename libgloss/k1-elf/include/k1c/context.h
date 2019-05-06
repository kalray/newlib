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

#ifndef _K1_CONTEXT_H
#  define _K1_CONTEXT_H

#include <stdint.h>

#    ifndef __k1_context_t
/**
 * \struct __k1_context_t
 * \brief Process context TODO
 */
typedef struct __k1_context __k1_context_t;

struct __k1_context {
  uint64_t regs[64];
  uint64_t spc;
  uint64_t ls;
  uint64_t le;
  uint64_t ra;
  uint64_t sps;
  uint64_t cs;
  uint64_t lc;
};
#endif

/**
 * \fn unsigned int __k1_get_mode(void)
 * \brief Get current privilege level
 * \return levels 0, 1, 2 or 3
 */
extern unsigned int __k1_get_privilege_level(void);

/**
 * \fn void __k1_ctx_save(__k1_context_t * to)
 * \brief Save process context TODO
 */
extern void __k1_ctx_save(__k1_context_t *to);

/**
 * \fn void __k1_ctx_restore(__k1_context_t * from, __k1_context_t * to)
 * \brief Restore process context TODO
 */
extern void __k1_ctx_restore(__k1_context_t *from, __k1_context_t *to);

/**
 * \fn void __k1_ctx_load(__k1_context_t * from)
 * \brief Load process context
 */
extern void __k1_ctx_load(__k1_context_t *from);

/**
 * \fn void __k1_switch_to_smem_user(void)
 * \brief Switch from PL0, 1, 2 to PL3 (legacy smem user)
 */
extern void __k1_switch_to_smem_user(void);

#endif      /* _K1_CONTEXT_H */
