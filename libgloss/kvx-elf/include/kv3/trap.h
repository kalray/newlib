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

#ifndef _KVX_TRAP_H_
#define _KVX_TRAP_H_

#define KV3_TRAP_RESET          0x0
#define KV3_TRAP_OPCODE         0x1
#define KV3_TRAP_PRIVILEGE      0x2
#define KV3_TRAP_DMISALIGN      0x3
#define KV3_TRAP_PSYSERROR      0x4
#define KV3_TRAP_DSYSERROR      0x5
#define KV3_TRAP_PDECCERROR     0x6
#define KV3_TRAP_DDECCERROR     0x7
#define KV3_TRAP_PPARERROR      0x8
#define KV3_TRAP_DPARERROR      0x9
#define KV3_TRAP_PSECERROR      0xA
#define KV3_TRAP_DSECERROR      0xB
#define KV3_TRAP_NOMAPPING      0xC
#define KV3_TRAP_PROTECTION     0xD
#define KV3_TRAP_WRITETOCLEAN   0xE
#define KV3_TRAP_ATOMICTOCLEAN  0xF
#define KV3_TRAP_TPARERROR      0x10
#define KV3_TRAP_NONE           TRAP_NONE

#define KV3_EC_DEBUG        0
#define KV3_EC_HWTRAP       1
#define KV3_EC_INTERRUPT    2
#define KV3_EC_SCALL        3
#define KV3_EC_DE_HWTRAP    9
#define KV3_EC_DE_INTERRUPT 10
#define KV3_EC_DE_SCALL     11

#  ifndef __ASSEMBLER__
/**
 * \fn void __kvx_trap_enable(void)
 * \brief Enables Traps
 */
extern void __kvx_trap_enable(void);

/**
 * \fn void __kvx_trap_disable(void)
 * \brief Disable Traps
 */
extern void __kvx_trap_disable(void);

/**
 * \fn void __kvx_clear_exception_taken(void)
 * \brief Clear Exception Taken bit of $ps ($ps.ET) to enable exception nesting
 */
extern void __kvx_clear_exception_taken(void);

/**
 * \fn void __kvx_set_exception_taken(void)
 * \brief Set Exception Taken bit of $ps ($ps.ET) to enable exception nesting
 */
extern void __kvx_set_exception_taken(void);

#endif /* __ASSEMBLER__ */

#endif /* _KVX_TRAP_H_ */
