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

.text
    .align 16
    .global memset
    .type memset, @function
memset:
    zxbd $r1 = $r1
    ;;
    make $r3 = 0
    copyd $r10 = $r0
    ;;
    andd $r1 = $r1, 255
    ;;
    slld $r4 = $r1, 8
    slld $r5 = $r1, 16
    slld $r6 = $r1, 24
    slld $r7 = $r1, 32
    ;;
    slld $r8 = $r1, 40
    slld $r9 = $r1, 48
    slld $r11 = $r1, 56
    ;;
    ord $r4 = $r1, $r4
    ord $r5 = $r5, $r6
    ord $r6 = $r7, $r8
    ord $r7 = $r9, $r11
    ;;
    ord $r4 = $r4, $r5
    ord $r5 = $r6, $r7
    ;;
    ord $r4 = $r4, $r5
    ord $r5 = $r4, $r5
    ord $r6 = $r4, $r5
    ord $r7 = $r4, $r5
    ;;
.L4: # prologue unaligned
    cb.weqz $r2? .L6
    andd $r8 = $r10, 31
    ;;
    cb.weqz $r8? .L3
    ;;
    sb $r3[$r0] = $r1
    addw $r3 = $r3, 1
    addw $r2 = $r2, -1
    addd $r10 = $r10, 1
    ;;
    goto .L4
    ;;
.L3: # kernel aligned
    srld $r9 = $r2, 5
    ;;
    cb.deqz $r9? .L5
    ;;
    loopdo $r9, .L5
    ;;
    so $r3[$r0] = $r4r5r6r7
    addw $r3 = $r3, 32
    addw $r2 = $r2, -32
    ;;
.L5: # epilogue unaligned
    cb.weqz $r2? .L6
    ;;
    sb $r3[$r0] = $r1
    addw $r3 = $r3, 1
    addw $r2 = $r2, -1
    ;;
    goto .L5
    ;;
.L6:
    ret
    ;;
