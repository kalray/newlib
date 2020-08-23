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

#ifndef _KVX_SCALL_NO_H
#define _KVX_SCALL_NO_H

#ifdef __linux__
#  ifdef __KERNEL__
#    define _KVX_SCALL_NO_H_EMPTY
#  endif
#endif

#ifndef _KVX_SCALL_NO_H_EMPTY

#  ifndef _KVX_SCALL_NO_NATIF

/* 'open'/'fcntl' flags that will be passed between newlib/host */
#    define S_RDONLY    0x001
#    define S_WRONLY    0x002
#    define S_RDWR      0x004
#    define S_APPEND    0x008
#    define S_CREAT     0x010
#    define S_TRUNC     0x020
#    define S_EXCL      0x040
#    define S_SYNC      0x080
#    define S_NDELAY    0x100
#    define S_NONBLOCK  0x200
#    define S_NOCTTY    0x400

/* Those are syscall numbers for the ISS.
 *    TODO: split this into OS-dependant parts, with different compilations
 *          of newlib for each of them
 */
#    define __NR_exit           1
#    define __NR_close          4
#    define __NR_fstat          6
#    define __NR_link           7
#    define __NR_unlink         8
#    define __NR_lseek          9
#    define __NR_open           10
#    define __NR_read           11
#    define __NR_stat           14
#    define __NR_gettimeofday   16
#    define __NR_write          17
#    define __NR_chmod          18
#    define __NR_isatty         19
#    define __NR_dup            28
#    define __NR_dup2           29
#    define __NR_fcntl          48
#    define __NR_mkdir          50
#    define __NR_rmdir          51
#    define __NR_access         52
#    define __NR_chdir          54
#    define __NR_mkfifo         55
#    define __NR_cache_flush    196
#    define __NR_exit_thread    197
#    define __NR_send_command   198
#    define __NR_readtimer      200
#define  __NR_probe_address_space 201

#    define __NR_last_syscall 202 /* Set to highest syscall number */


/* Special syscalls for internal use by the ISS */

#    define __NR_BREAKPOINT_PL0     0xfd2 /* 4050 */
#    define __NR_BREAKPOINT_PL1     0xfd3 /* 4051 */
#    define __NR_BREAKPOINT_PL2     0xfd4 /* 4052 */
#    define __NR_BREAKPOINT_PL3     0xfd5 /* 4053 */
#    define __NR_BREAKPOINT_JTAGISS 0xfd6 /* 4054 */
#    define __NR_iss_trace_notify   0xfd7 /* 4055 */
#    define __NR_iss_is_simu        0xfd8 /* 4056 */
#    define __NR_iss_notify_spawn   0xfd9 /* 4057 */
#    define __NR_iss_inbyte         0xfda /* 4058 */
#    define __NR_iss_poll           0xfdb /* 4059 */
#    define __NR_iss_close          0xfde /* 4062 */
#    define __NR_iss_fstat          0xfdf /* 4063 */
#    define __NR_iss_load_elf       0xfe8 /* 4072 */
#    define __NR_iss_mkfifo         0xfe9 /* 4073 */
#    define __NR_iss_link           0xfea /* 4074 */
#    define __NR_iss_unlink         0xfeb /* 4075 */
#    define __NR_iss_lseek          0xfec /* 4076 */
#    define __NR_iss_open           0xfed /* 4077 */
#    define __NR_iss_read           0xfee /* 4078 */
#    define __NR_iss_stat           0xfef /* 4079 */
#    define __NR_iss_gettimeofday   0xff0 /* 4080 */
#    define __NR_iss_write          0xff1 /* 4081 */
#    define __NR_iss_chmod          0xff2 /* 4082 */
#    define __NR_iss_isatty         0xff3 /* 4083 */
#    define __NR_iss_dup            0xff4 /* 4084 */
#    define __NR_iss_dup2           0xff5 /* 4085 */
#    define __NR_iss_fcntl          0xff6 /* 4086 */
#    define __NR_iss_mkdir          0xff7 /* 4087 */
#    define __NR_iss_rmdir          0xff8 /* 4088 */
#    define __NR_iss_access         0xff9 /* 4089 */
#    define __NR_iss_chdir          0xffa /* 4090 */
#    define __NR_iss_getdents       0xffb /* 4091 */
#    define __NR_iss_readtimer      0xffd /* 4093 */
#    define __NR_iss_printf         0xffe /* 4094 */
#    define __NR_iss_exit           0xfff /* 4095 */

#  endif    /* _KVX_SCALL_NO_NATIF */

#endif      /*_KVX_SCALL_NO_H_EMPTY */

#endif      /* _KVX_SCALL_NO_H */
