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
#include <kvx/registers.h>
#define __NL__

	.section .boot.startup, "ax", @progbits
	.align 8
	.global __GLOSS_KVX_PE_STACK_ADDRESS
	.global __GLOSS_KVX_PE_START_ADDRESS
	.global __GLOSS_KVX_PE_ARGS_ADDRESS
	.globl __kvx_pe_c_startup
	.globl __kvx_rm_c_startup

	.global _start
	.proc _start
_start:
#ifdef __KV3_64__
	make $r0 = 0x1000000000000
	;;
	wfxl $ps, $r0      #    go 64b
	;;
#endif /* __KV3_64__ */
	# Get proc ID
	get $r5 = $pcr
	;;
	extfz $r0 = $r5, (KVX_SFR_PCR_PID_WIDTH + KVX_SFR_PCR_PID_SHIFT - 1), KVX_SFR_PCR_PID_SHIFT
	;;
	compw.eq $r1 = $r0, 0x10
	;;
	cb.weqz $r1, .L__kvx_asm_start_pe
	;;
#__kvx_asm_start_rm:
	make $sp = _rm_stack_start
	make $r1 = __kvx_rm_c_startup
	;;
	icall $r1 # use icall to get a long reach, just in case .boot.startup is linked far from .text (e.g. boot in flash, .text in smem)
	;;
	goto .     # just in case ...
	;;
.L__kvx_asm_start_pe:
	make $r2 = __GLOSS_KVX_PE_STACK_ADDRESS
	make $r1 = __kvx_pe_c_startup
	;;
	LOAD_PTR.xs $sp = $r0[$r2]  # init pe stack @ $r2 + pid * 8 (64 bits mode) or * 4 (32 bits mode)
	;;
	icall $r1
	;;
	goto .     # just in case ...
	;;
	.endp _start

	.section .bss
	.align 8
	__GLOSS_KVX_PE_STACK_ADDRESS:   .space 0x80  # Space: 16 * 8 bytes or 16 * 4 bytes (64 or 32 bits modes)
	__GLOSS_KVX_PE_START_ADDRESS:   .space 0x80
	__GLOSS_KVX_PE_ARGS_ADDRESS:    .space 0x80


	.section .exception.debug, "ax", @progbits ;\
	.globl kv3_debug_handler_trampoline ;\
	.proc kv3_debug_handler_trampoline
kv3_debug_handler_trampoline:
	goto __kvx_asm_exceptions_handler
	;;
	.endp kv3_debug_handler_trampoline

	.section .exception.trap, "ax", @progbits ;\
	.globl kv3_trap_handler_trampoline ;\
	.proc kv3_trap_handler_trampoline
kv3_trap_handler_trampoline:
	goto __kvx_asm_exceptions_handler
	;;
	.endp kv3_trap_handler_trampoline

	.section .exception.interrupt, "ax", @progbits ;\
	.globl kv3_interrupt_handler_trampoline ;\
	.proc kv3_interrupt_handler_trampoline
kv3_interrupt_handler_trampoline:
	goto __kvx_asm_exceptions_handler
	;;
	.endp kv3_interrupt_handler_trampoline

	.section .exception.syscall, "ax", @progbits ;\
	.globl kv3_syscall_handler_trampoline ;\
	.proc kv3_syscall_handler_trampoline
kv3_syscall_handler_trampoline:
	goto __kvx_asm_exceptions_handler
	;;
	.endp kv3_syscall_handler_trampoline

