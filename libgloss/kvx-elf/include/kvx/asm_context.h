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

#ifndef __KVX_ASM_CONTEXT_H
#  define __KVX_ASM_CONTEXT_H

#define __KVX_CONTEXT_R0R1      0x000
#define __KVX_CONTEXT_R2R3      0x010
#define __KVX_CONTEXT_R4R5      0x020
#define __KVX_CONTEXT_R6R7      0x030
#define __KVX_CONTEXT_R8R9      0x040
#define __KVX_CONTEXT_R10R11    0x050
#define __KVX_CONTEXT_R13       0x068 /* We do not save $r12 */
#define __KVX_CONTEXT_R14R15    0x070
#define __KVX_CONTEXT_R16R17    0x080
#define __KVX_CONTEXT_R18R19    0x090
#define __KVX_CONTEXT_R20R21    0x0A0
#define __KVX_CONTEXT_R22R23    0x0B0
#define __KVX_CONTEXT_R24R25    0x0C0
#define __KVX_CONTEXT_R26R27    0x0D0
#define __KVX_CONTEXT_R28R29    0x0E0
#define __KVX_CONTEXT_R30R31    0x0F0
#define __KVX_CONTEXT_R32R33    0x100
#define __KVX_CONTEXT_R34R35    0x110
#define __KVX_CONTEXT_R36R37    0x120
#define __KVX_CONTEXT_R38R39    0x130
#define __KVX_CONTEXT_R40R41    0x140
#define __KVX_CONTEXT_R42R43    0x150
#define __KVX_CONTEXT_R44R45    0x160
#define __KVX_CONTEXT_R46R47    0x170
#define __KVX_CONTEXT_R48R49    0x180
#define __KVX_CONTEXT_R50R51    0x190
#define __KVX_CONTEXT_R52R53    0x1A0
#define __KVX_CONTEXT_R54R55    0x1B0
#define __KVX_CONTEXT_R56R57    0x1C0
#define __KVX_CONTEXT_R58R59    0x1D0
#define __KVX_CONTEXT_R60R61    0x1E0
#define __KVX_CONTEXT_R62R63    0x1F0

/* This will waste 3*64bits space in 32bits as pointers are not 64b wide. */
#define __KVX_CONTEXT_SPC_LS  0x200
#define __KVX_CONTEXT_LE_RA   0x210
#define __KVX_CONTEXT_SPS_CS  0x220
#define __KVX_CONTEXT_LC      0x230
#define __KVX_CONTEXT_LAST    0x240

#ifdef __ASSEMBLER__

#define __KVX_CONTEXT64_SIZE  __KVX_CONTEXT_LAST

.macro __kvx_context64_save to
	sq    __KVX_CONTEXT_R0R1[\to]= $r0r1        ## $r0 - $r1
	;;
	get   $r2=$spc
	sq    __KVX_CONTEXT_R2R3[\to]= $r2r3        ## $r2 - $r3
	;;
	get   $r3 = $ls
	sq    __KVX_CONTEXT_R4R5[\to]= $r4r5       ## $r4 - $r5
	;;
	get   $r4 = $le
	sq    __KVX_CONTEXT_R6R7[\to]= $r6r7       ## $r6 - $r7
	;;
	get   $r5 = $ra
	sq    __KVX_CONTEXT_R8R9[\to]= $r8r9       ## $r8 - $r9
	;;
	get   $r6 = $sps
	sq    __KVX_CONTEXT_R10R11[\to]= $r10r11      ## $r10 - $r11
	;;
	get   $r7 = $cs
	sd    __KVX_CONTEXT_R13[\to]= $r13            ## $r13
	;;
	get   $r8 = $lc
	sq    __KVX_CONTEXT_R14R15[\to]= $r14r15      ## $r14 - $r15
	;;
	sq    __KVX_CONTEXT_R16R17[\to]= $r16r17      ## $r16 - $r17
	;;
	sq    __KVX_CONTEXT_R18R19[\to]= $r18r19      ## $r18 - $r19
	;;
	sq    __KVX_CONTEXT_R20R21[\to]= $r20r21      ## $r20 - $r21
	;;
	sq    __KVX_CONTEXT_R22R23[\to]= $r22r23      ## $r22 - $r23
	;;
	sq    __KVX_CONTEXT_R24R25[\to]= $r24r25      ## $r24 - $r25
	;;
	sq    __KVX_CONTEXT_R26R27[\to]= $r26r27      ## $r26 - $r27
	;;
	sq    __KVX_CONTEXT_R28R29[\to]= $r28r29      ## $r28 - $r29
	;;
	sq    __KVX_CONTEXT_R30R31[\to]= $r30r31      ## $r30 - $r31
	;;
	sq    __KVX_CONTEXT_R32R33[\to]= $r32r33      ## $r32 - $r33
	;;
	sq    __KVX_CONTEXT_R34R35[\to]= $r34r35      ## $r34 - $r35
	;;
	sq    __KVX_CONTEXT_R36R37[\to]= $r36r37      ## $r36 - $r37
	;;
	sq    __KVX_CONTEXT_R38R39[\to]= $r38r39      ## $r38 - $r39
	;;
	sq    __KVX_CONTEXT_R40R41[\to]= $r40r41      ## $r40 - $r41
	;;
	sq    __KVX_CONTEXT_R42R43[\to]= $r42r43      ## $r42 - $r43
	;;
	sq    __KVX_CONTEXT_R44R45[\to]= $r44r45      ## $r44 - $r45
	;;
	sq    __KVX_CONTEXT_R46R47[\to]= $r46r47      ## $r46 - $r47
	;;
	sq    __KVX_CONTEXT_R48R49[\to]= $r48r49      ## $r48 - $r49
	;;
	sq    __KVX_CONTEXT_R50R51[\to]= $r50r51      ## $r50 - $r51
	;;
	sq    __KVX_CONTEXT_R52R53[\to]= $r52r53      ## $r52 - $r53
	;;
	sq    __KVX_CONTEXT_R54R55[\to]= $r54r55      ## $r54 - $r55
	;;
	sq    __KVX_CONTEXT_R56R57[\to]= $r56r57      ## $r56 - $r57
	;;
	sq    __KVX_CONTEXT_R58R59[\to]= $r58r59      ## $r58 - $r59
	;;
	sq    __KVX_CONTEXT_R60R61[\to]= $r60r61      ## $r60 - $r61
	;;
	sq    __KVX_CONTEXT_R62R63[\to]= $r62r63      ## $r62 - $r63
	;;
	sq    __KVX_CONTEXT_SPC_LS[\to]= $r2r3    ## $spc - $ls
	;;
	sq    __KVX_CONTEXT_LE_RA[\to]= $r4r5     ## $le  - $ra
	;;
	sq    __KVX_CONTEXT_SPS_CS[\to]= $r6r7    ## $sps - $cs
	;;
	sd    __KVX_CONTEXT_LC[\to]= $r8          ## $lc
	;;
.endm

.macro __kvx_context64_restore from
	lq.u  $r2r3  = __KVX_CONTEXT_SPC_LS[\from]  ## $spc - $ls
	;;
	lq.u  $r4r5  = __KVX_CONTEXT_LE_RA[\from]   ## $le - $ra
	;;
	get   $r33   = $sps
	lq.u  $r6r7  = __KVX_CONTEXT_SPS_CS[\from]  ## $sps  - $cs
	;;
	set   $spc   = $r2
	eord  $r33   = $r6, $r33         # generate a mask of ones with a '1' at each bit where the current $sps ($r33) differs from the $sps ($r6) to be restored
	notd  $r34   = $r6               # prepare WFXL clear mask on LSBs
	slld  $r35   = $r6, 32           # prepare WFXL set mask on MSBs
	ld.u  $r8    = __KVX_CONTEXT_LC[\from]      ## $lc
	;;
	set   $ls = $r3
	sbmm8 $r33 = $r33, 0x0804020108040201      # replicate the mask of ones on the 32 MSBs
	insf  $r35 = $r34, 31, 0                   # combine the set and clear maks => almost ready to WFXL
	lq.u  $r62r63  = __KVX_CONTEXT_R62R63[\from]
	;;
	set   $le = $r4
	andd  $r35 = $r35, $r33                    # drop the bits that are already identical to avoid useless set/clear attempts that may lead to PRIVILEGE hwtraps
	lq.u  $r60r61  = __KVX_CONTEXT_R60R61[\from]
	;;
	wfxl  $sps , $r35                # finally restore $sps
	;;
	lq.u  $r58r59  = __KVX_CONTEXT_R58R59[\from]
	;;
	set   $ra = $r5
	lq.u  $r56r57  = __KVX_CONTEXT_R56R57[\from]
	;;
	set   $cs = $r7
	lq.u  $r54r55  = __KVX_CONTEXT_R54R55[\from]
	;;
	set   $lc = $r8
	lq.u  $r52r53  = __KVX_CONTEXT_R52R53[\from]
	;;
	lq.u  $r50r51  = __KVX_CONTEXT_R50R51[\from]
	;;
	lq.u  $r48r49  = __KVX_CONTEXT_R48R49[\from]
	;;
	lq.u  $r46r47  = __KVX_CONTEXT_R46R47[\from]
	;;
	lq.u  $r44r45  = __KVX_CONTEXT_R44R45[\from]
	;;
	lq.u  $r42r43  = __KVX_CONTEXT_R42R43[\from]
	;;
	lq.u  $r40r41  = __KVX_CONTEXT_R40R41[\from]
	;;
	lq.u  $r38r39  = __KVX_CONTEXT_R38R39[\from]
	;;
	lq.u  $r36r37  = __KVX_CONTEXT_R36R37[\from]
	;;
	lq.u  $r34r35  = __KVX_CONTEXT_R34R35[\from]
	;;
	lq.u  $r32r33  = __KVX_CONTEXT_R32R33[\from]
	;;
	lq.u  $r30r31  = __KVX_CONTEXT_R30R31[\from]
	;;
	lq.u  $r28r29  = __KVX_CONTEXT_R28R29[\from]
	;;
	lq.u  $r26r27  = __KVX_CONTEXT_R26R27[\from]
	;;
	lq.u  $r24r25  = __KVX_CONTEXT_R24R25[\from]
	;;
	lq.u  $r22r23  = __KVX_CONTEXT_R22R23[\from]
	;;
	lq.u  $r20r21  = __KVX_CONTEXT_R20R21[\from]
	;;
	lq.u  $r18r19  = __KVX_CONTEXT_R18R19[\from]
	;;
	lq.u  $r16r17  = __KVX_CONTEXT_R16R17[\from]
	;;
	lq.u  $r14r15  = __KVX_CONTEXT_R14R15[\from]
	;;
	ld.u  $r13     = __KVX_CONTEXT_R13[\from]
	;;
	lq.u  $r10r11  = __KVX_CONTEXT_R10R11[\from]
	;;
	lq.u  $r8r9   = __KVX_CONTEXT_R8R9[\from]
	;;
	lq.u  $r6r7   = __KVX_CONTEXT_R6R7[\from]
	;;
	lq.u  $r4r5   = __KVX_CONTEXT_R4R5[\from]
	;;
	lq.u  $r2r3   = __KVX_CONTEXT_R2R3[\from]
	;;
	lq.u  $r0r1   = __KVX_CONTEXT_R0R1[\from]
	;;
.endm

#endif /* __ASSEMBLER__ */

#endif      /* __KVX_ASM_CONTEXT_H */
