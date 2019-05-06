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

#ifndef _LINKER_SYMBOLS_H_
#define  _LINKER_SYMBOLS_H_

/* Defined in tls.ld linker script. */
extern unsigned char _tls_rm_start[];

extern unsigned char _tdata_start[];
extern unsigned char _tdata_end[];

extern unsigned char _tbss_start[];
extern unsigned char _tbss_end[];

extern unsigned char _bss_start[];
extern unsigned char _bss_end[];

extern unsigned char _sbss_start[];
extern unsigned char _sbss_end[];

/* These are left commented.
 *
 * GCC may make false asumption on these being non-NULL.  It can work
 * in certain cases.  Stay safe here and compute the size at startup.
 * Leaving this comment so that these do not pop-up unknowingly.
 */
/* extern uint32_t _tbss_size __attribute__((weak)); */
/* extern uint32_t _tdata_size __attribute__((weak)); */

#endif  /* _MPPA_BARE_RUNTIME_LINKER_SYMBOLS_H_ */
