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

#ifndef _K1_START_C_H
#  define _K1_START_C_H

/**
 * \fn void __k1_start_pe(int cpuid, void *start_address, void *args_address, void *stack_address)
 * \brief Start the given function on the given PE (implies __k1_set_pwc_wup)
 * \param start_address address of entry point (function) to execute on PE
 * \param args_address arguments address to be passed to function at start_address
 * \param stack_address address of new PE stack.
 */
extern void __k1_start_pe(int cpuid, void *start_address, void *args_address, void *stack_address);

/**
 * \fn void __k1_stop(void)
 * \brief Processor is stopping itself (IDLE2)
 */
extern void __k1_stop(void);

/* Defined in linker script */
extern void *K1_BOOT_ADDRESS;
extern void *K1_EXCEPTION_ADDRESS;
extern void *K1_DEBUG_RAM_ADDRESS;
extern void *K1_PE_STACK_START;

/* Entry point in newlib */
extern void __start1(int argc, char **argv, char  **envp);

#endif /* _K1_START_C_H */
