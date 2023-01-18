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

#include <kvx/asm_macros.h>
#include <kvx/asm_context.h>
#include <kvx/registers.h>
#include <kvx/trap.h>

#include <kvx/bsp.h>

	.section .exceptions, "ax", @progbits
	.globl __kvx_asm_exceptions_handler
	.proc __kvx_asm_exceptions_handler
__kvx_asm_exceptions_handler:
	ADD_PTR   $sp, $sp, -__KVX_CONTEXT64_SIZE    ## space for the registers
	;;
	__kvx_context64_save $sp
	;;
	get   $r0 = $es
	copyd $r1 = $sp
	make  $r2 = (KVX_SFR_PS_HLE_MASK << 32 | KVX_SFR_PS_ET_MASK)
        ;;
	wfxl  $ps, $r2               ## set HLE + clear ET to allow nesting
        ;;
	extfz  $r0 = $r0, (KVX_SFR_ES_EC_WIDTH + KVX_SFR_ES_EC_SHIFT - 1), KVX_SFR_ES_EC_SHIFT ## Extract 2 lsb of $es.ec
        ;;
	cb.deqz $r0? .L__kvx_asm_debug_handler ## $es.ec = KV3_EC_DEBUG
	compd.eq $r2 = $r0, KV3_EC_HWTRAP
        ;;
	cb.dnez $r2? .L__kvx_asm_hwtrap_handler ## $es.ec = KV3_EC_HWTRAP
	compd.eq $r2 = $r0, KV3_EC_INTERRUPT
        ;;
	cb.dnez $r2? .L__kvx_asm_interrupt_handler ## $es.ec = KV3_EC_INTERRUPT
	compd.eq $r2 = $r0, KV3_EC_SCALL
        ;;
	cb.dnez $r2? .L__kvx_asm_scall_handler ## $es.ec = KV3_EC_SCALL
	compd.eq $r2 = $r0, KV3_EC_DE_HWTRAP
        ;;
	cb.dnez $r2? .L__kvx_asm_hwtrap_handler ## $es.ec = KV3_EC_DE_HWTRAP
	compd.eq $r2 = $r0, KV3_EC_DE_INTERRUPT
        ;;
	cb.dnez $r2? .L__kvx_asm_hwtrap_handler ## $es.ec = KV3_EC_DE_INTERRUPT
	compd.eq $r2 = $r0, KV3_EC_DE_SCALL
        ;;
	cb.dnez $r2? .L__kvx_asm_hwtrap_handler ## $es.ec = KV3_EC_DE_SCALL
        ;;
	goto .L__kvx_asm_bad_exception_handler
        ;;
.L__kvx_asm_hwtrap_handler:
        .global __kvx_do_hwtrap
        .type __kvx_do_hwtrap, @function
	get   $r0 = $es
        ;;
	extfz  $r0 = $r0, (KVX_SFR_ES_HTC_WIDTH + KVX_SFR_ES_HTC_SHIFT - 1), KVX_SFR_ES_HTC_SHIFT ## Extract HTC from ES
	call  __kvx_do_hwtrap       ## jump to C code
        ;;
	goto .L__kvx_asm_return_from_exceptions
        ;;
.L__kvx_asm_interrupt_handler:
	get   $r0 = $es
	;;
	extfz $r0 = $r0, (KVX_SFR_ES_ITN_WIDTH + KVX_SFR_ES_ITN_SHIFT - 1), KVX_SFR_ES_ITN_SHIFT ## Extract ITN from ES
	;;
	.global __kvx_do_interrupt
	.type __kvx_do_interrupt, @function
	.global __kvx_do_interrupt_dame
	.type __kvx_do_interrupt_dame, @function

	compd.eq $r2 = $r0, __GLOSS_KVX_PE_INT_LINE_DAME
	make     $r3 = __kvx_do_interrupt
	make     $r4 = __kvx_do_interrupt_dame
	;;
	cmoved.dnez $r2 ? $r3 = $r4
	;;
	## jump to C code, calling either __kvx_do_interrupt_dame (special interrupt handler for DAME (Data Asynchronous Memory Error)), or __kvx_do_interrupt (general interrupt handler)
	## according to the number of the interrupt we took
	icall $r3
	;;
	goto .L__kvx_asm_return_from_exceptions
	;;
.L__kvx_asm_debug_handler:
	.global __kvx_do_debug
	.type __kvx_do_debug, @function

	get   $r0 = $es
	;;
	#ifdef __kvxarch_kv3_1
	extfz  $r0 = $r0, (KVX_SFR_ES_DC_WIDTH + KVX_SFR_ES_DC_SHIFT - 1), KVX_SFR_ES_DC_SHIFT ## Extract DC from ES
	#else
	extfz  $r0 = $r0, (KVX_SFR_ES_DCV2_WIDTH + KVX_SFR_ES_DCV2_SHIFT - 1), KVX_SFR_ES_DCV2_SHIFT ## Extract DCF from ES
	#endif
	call  __kvx_do_debug       ## jump to C code
	;;
	goto .L__kvx_asm_return_from_exceptions
	;;
.L__kvx_asm_scall_handler:
	.global __kvx_do_scall
	.type __kvx_do_scall, @function

	lq $r2r3 = 0[$sp]
	;;
	lq $r4r5 = 16[$sp]
	;;
	lq $r6r7 = 32[$sp]
	;;
	get   $r0 = $es
	;;
	extfz  $r0 = $r0, (KVX_SFR_ES_SN_WIDTH + KVX_SFR_ES_SN_SHIFT - 1), KVX_SFR_ES_SN_SHIFT ## Extract HTC from ES
	call  __kvx_do_scall       ## jump to C code
	;;
	sd 0[$sp] = $r0 ## Store back return value (r0) into context register r0
	;;
	goto .L__kvx_asm_return_from_exceptions
	;;
.L__kvx_asm_bad_exception_handler:
	make $r0 = 1
	;;
	scall 4095
	;;
.L__kvx_asm_return_from_exceptions:
	make  $r2 = KVX_SFR_PS_IE_MASK
	;;
	wfxl  $ps, $r2                ## disable interrupts for context restoration
	;;
	__kvx_context64_restore $sp
	;;
	ADD_PTR  $sp, $sp, __KVX_CONTEXT64_SIZE
	;;
	rfe
	;;
	.endp __kvx_asm_exceptions_handler
