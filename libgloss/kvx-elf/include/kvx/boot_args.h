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

#ifndef __KVX_BOARD_BOOT_ARGS_H
#define __KVX_BOARD_BOOT_ARGS_H

#include <stdint.h>

/* In memory, we have the following mappping
 *                                 +-------------------------+
 * MPPA_ARGAREA_START              |__kvx_boot_args_mmap_t { |
 *                                 |.magic_value             |
 *                                 |.spawn_type              |
 *                                 |.spawner_id              |
 *                                 |.remote_console_enable   |
 *                                 |.frequency               |
 *                                 |.argc                    |
 *                                 |.envc                    |
 *                                 |.argv_ptr; ----------+   |
 *                                 |.envp_ptr; ----------|-+ |
 *                                 |}                    | | |
 * + sizeof(__kvx_boot_args_mmap_t) |argv[0] -----------+<+| |
 *                                 |argv[1] ---------+ |   | |
 *                                 |argv[2] -------+ | |   | |
 *                                 |.......        | | |   | |
 *                                 |NULL           | | |   | |
 *                                 |argv_data[0] <-|-|-+   | |
 *                                 |············   | |     | |
 *                                 |············   | |     | |
 *                                 |argv_data[1] <-|-+     | |
 *                                 |············   |       | |
 *                                 |············   |       | |
 *                                 |argv_data[2] <-+       | |
 *                                 |············           | |
 *                                 |············           | |
 *                                 |············           | |
 *                                 |64 bits padding        | |
 *                                 |envp[0] -----------+<--+ |
 *                                 |envp[1] ---------+ |     |
 *                                 |NULL             | |     |
 *                                 |envp_data[0] <---|-+     |
 *                                 |············     |       |
 *                                 |············     |       |
 *                                 |············     |       |
 *                                 |envp_data[1] <---+       |
 *                                 |············             |
 *                                 |············             |
 *                                 |············             |
 *                                 |············             |
 *                                 |                         |
 * MPPA_ARGAREA_START              |                         |
 * + MPPA_ARGAREA_SIZE             |                         |
 *                                 +-------------------------+
 */

#  define __MPPA_MAGIC_BOOT_ARGS_VALUE 0xDEADBEEF

typedef struct kvx_boot_args {
  int     argc;
  int     envc;
  char    **argv;
  char    **envp;
} kvx_boot_args_t;

/*
 * Types used for storing and doing pointer arithmetic on /remote/ KVX pointers.
 */
typedef uint32_t __kvx_boot_args_uptr32_t;
typedef uint64_t __kvx_boot_args_uptr64_t;

/*
 * boot_args_mmapX struct are used to map the remote kvx_boot_args
 * struct on a local memory buffer.  The struct contains remote
 * pointer and thus 2 types exist for 32 and 64 bits targets.
 */
typedef struct __kvx_boot_args_mmap32 {
	uint32_t  magic_value;
	uint32_t  spawn_type;     /* kvx_spawn_type_t */
	uint32_t  spawner_id;     /* Cluster ID of spawner */
	uint32_t  remote_console_enable;
	uint32_t  frequency;      /* frequency of the cluster */
	uint32_t  argc;
	uint32_t  envc;
	__kvx_boot_args_uptr32_t       argv_ptr;
	__kvx_boot_args_uptr32_t       envp_ptr;
} __kvx_boot_args_mmap32_t __attribute__((aligned(8)));

typedef struct __kvx_boot_args_mmap64 {
	uint32_t  magic_value;
	uint32_t  spawn_type;     /* kvx_spawn_type_t */
	uint32_t  spawner_id;     /* Cluster ID of spawner */
	uint32_t  remote_console_enable;
	uint32_t  frequency;      /* frequency of the cluster */
	uint32_t  argc;
	uint32_t  envc;
	__kvx_boot_args_uptr64_t        argv_ptr;
	__kvx_boot_args_uptr64_t        envp_ptr;
} __kvx_boot_args_mmap64_t __attribute__((aligned(8)));

typedef __SIZE_TYPE__ local_pointer_size_t;

/*
 * Map the correct type for the local handling of boot args.
 */
#if defined(__KV3_64__)
typedef __kvx_boot_args_mmap64_t __kvx_boot_args_mmap_t;
#else
typedef __kvx_boot_args_mmap32_t __kvx_boot_args_mmap_t;
#endif

extern __kvx_boot_args_mmap_t MPPA_ARGAREA_START __attribute__((weak));

extern void __kvx_get_boot_args(kvx_boot_args_t *args);

#endif  /*  __KVX_BOARD_BOOT_ARGS_H */
