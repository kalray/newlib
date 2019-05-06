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

#include "asm.h"

	## int setjmp(jmp_buf)
	##
	## Basically setjmp saves the set of callee saved registers in jmp_buf
	## Also saving cs, the loop registers, ra and sp
_ENTRY(setjmp)
	.file 1 "setjmp.S"
	.loc 1 12 0
	.loc 1 12 0
	## All preserved registers
	sq	0x0[$r0] = $r18r19
;;
	sq	0x10[$r0] = $r20r21
;;
	sq	0x20[$r0] = $r22r23
;;
	sq	0x30[$r0] = $r24r25
;;
	sq	0x40[$r0] = $r26r27
;;
	sq	0x50[$r0] = $r28r29
;;
	sq	0x60[$r0] = $r30r31
;;
	sd	0x70[$r0] = $r13
;;
	sd	0x78[$r0] = $r14
	get     $r1 = $ls
;;
	sd	0x80[$r0] = $r1
	get     $r1 = $le
;;
	sd	0x88[$r0] = $r1
	get     $r1 = $lc
;;
	sd	0x90[$r0] = $r1
	get     $r1 = $cs
;;
	sd	0x98[$r0] = $r1
	get     $r1 = $ra
;;
	sd	0xa0[$r0] = $r1    ## Warning!!!! $ra offset must be set in gdb port in gdb/gdb/k1-common-tdep.c
;;
	sd	0xa8[$r0] = $r12
	make    $r0 = 0
;;
	## Must return zero if called to set up jm_buf
	ret
;;
	.endp setjmp



	## void longjmp(jmp_buf env, int val)
	##
	## Basically restore the saved register set found in env to processor
	## Restoring also sp. Note that it jumps back to original location
_ENTRY(longjmp)
        .loc 1 55 0
        .loc 1 55 0
	lq	$r18r19 = 0x0[$r0]
;;
	lq	$r20r21 = 0x10[$r0]
;;
	lq	$r22r23 = 0x20[$r0]
;;
	lq	$r24r25 = 0x30[$r0]
;;
	lq	$r26r27 = 0x40[$r0]
;;
	lq	$r28r29 = 0x50[$r0]
;;
	lq	$r30r31 = 0x60[$r0]
;;
	ld	$r13 = 0x70[$r0]
;;
	ld	$r14 = 0x78[$r0]
;;
	ld	$r2  = 0x80[$r0]
;;
	ld	$r2  = 0x88[$r0]
	set     $ls  = $r2
;;
	ld	$r2  = 0x90[$r0]
	set     $le  = $r2
;;
	ld	$r2  = 0x98[$r0]
	set     $lc  = $r2
;;
	ld	$r2  = 0xa0[$r0]
	set     $cs  = $r2
;;
	set     $ra  = $r2
;;
	ld	$r12 = 0xa8[$r0]
	copyd   $r0 = $r1
	make    $r2 = 1
;;
	## Finally if called with val==0, return one else val

	## FIXME AUTO: reuse cmoved.weqz
	## cmoved.weqz $r0? $r0 = $r2

        ## start of cmoved replacement
	cb.weqz $r0, 1f
	;;
	ret
	;;
1:
	copyd $r0 = $r2
	ret
	;;
        ## end of cmoved replacement
	.endp longjmp
