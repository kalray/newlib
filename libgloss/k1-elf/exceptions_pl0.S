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

#include <k1c/asm_macros.h>
#include <k1c/asm_context.h>
#include <k1c/registers.h>
#include <k1c/trap.h>

	.section .bare_dsu, "ax", @progbits
	.globl __k1_asm_exceptions_pl0_handler
	.proc __k1_asm_exceptions_pl0_handler
__k1_asm_exceptions_pl0_handler:
	ADD_PTR   $sp, $sp, -_K1_CONTEXT64_SIZE    ## space for the registers
	;;
	_k1_context64_save $sp
	;;
	make  $r2 = (K1_SFR_PS_HLE_MASK << 32 | K1_SFR_PS_ET_MASK)
	copyd $r1 = $sp
	get   $r0 = $es
	;;
	wfxl  $ps, $r2               ## set HLE + clear ET to allow nesting
	;;
	.global __k1_do_exceptions_pl0
	.type __k1_do_exceptions_pl0, @function

	lq $r2r3 = 0[$sp]            ## Restore arguments in case of syscall
	;;
	lq $r4r5 = 16[$sp]
	;;
	lq $r6r7 = 32[$sp]
	;;
	extfz  $r0 = $r0, (K1_SFR_ES_EC_WIDTH + K1_SFR_ES_EC_SHIFT - 1), K1_SFR_ES_EC_SHIFT ## Extract EC from ES
	call  __k1_do_exceptions_pl0       ## jump to C code
	;;
	extfz  $r1 = $r1, (K1_SFR_ES_EC_WIDTH + K1_SFR_ES_EC_SHIFT - 1), K1_SFR_ES_EC_SHIFT ## Extract 2 lsb of $es.ec
	;;
	compd.eq $r1 = $r1, K1C_EC_SCALL
	;;
	make  $r2 = K1_SFR_PS_IE_MASK
	sd.wnez $r1 ? 0[$sp] = $r0 ## Store back return value (r0) into context regist	er r0 only in case of syscall
	;;
	wfxl  $ps, $r2                ## disable interrupts for context restoration
	;;
	_k1_context64_restore $sp
	;;
	ADD_PTR  $sp, $sp, _K1_CONTEXT64_SIZE
	;;
	rfe
	;;
	.endp __k1_asm_exceptions_pl0_handler
