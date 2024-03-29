/*-
 * Copyright (c) 2008,	Jeffrey Roberson <jeff@freebsd.org>
 * All rights reserved.
 *
 * Copyright (c) 2008 Nokia Corporation
 * All rights reserved.
 *
 * Copyright (c) 2013 On-Line Applications Research Corporation.
 * All rights reserved.
 *
 *  On-Line Applications Research Corporation
 *  7047 Old Madison Pike Suite 320
 *  Huntsville Alabama 35806
 *  <info@oarcorp.com>
 *
 * Copyright 2022
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

#ifndef _SYS_CPUSET_H_
#define	_SYS_CPUSET_H_

#include <sys/cdefs.h>
#include <sys/_cpuset.h>
#include <sys/bitset.h>

#define	_NCPUBITS	_BITSET_BITS
#define	_NCPUWORDS	__bitset_words(CPU_SETSIZE)

#define	CPUSETBUFSIZ	((2 + sizeof(long) * 2) * _NCPUWORDS)

#define	CPU_SETOF(n, p)			BIT_SETOF(CPU_SETSIZE, n, p)
#define	CPU_ISFULLSET(p)		BIT_ISFULLSET(CPU_SETSIZE, p)
#define	CPU_SUBSET(p, c)		BIT_SUBSET(CPU_SETSIZE, p, c)
#define	CPU_OVERLAP(p, c)		BIT_OVERLAP(CPU_SETSIZE, p, c)
#define	CPU_CLR_ATOMIC(n, p)		BIT_CLR_ATOMIC(CPU_SETSIZE, n, p)
#define	CPU_SET_ATOMIC(n, p)		BIT_SET_ATOMIC(CPU_SETSIZE, n, p)
#define	CPU_SET_ATOMIC_ACQ(n, p)	BIT_SET_ATOMIC_ACQ(CPU_SETSIZE, n, p)
#define	CPU_AND_ATOMIC(n, p)		BIT_AND_ATOMIC(CPU_SETSIZE, n, p)
#define	CPU_OR_ATOMIC(d, s)		BIT_OR_ATOMIC(CPU_SETSIZE, d, s)
#define	CPU_COPY_STORE_REL(f, t)	BIT_COPY_STORE_REL(CPU_SETSIZE, f, t)
#define	CPU_FFS(p)			BIT_FFS(CPU_SETSIZE, p)
#define	CPUSET_FSET			BITSET_FSET(_NCPUWORDS)
#define	CPUSET_T_INITIALIZER		BITSET_T_INITIALIZER

typedef cpuset_t cpu_set_t;

#define	_cpu_set_bits(_setsize) (8 * (_setsize))

#define	CPU_ALLOC_SIZE(_num_cpus) (sizeof(long) * __bitset_words(_num_cpus))

__BEGIN_DECLS

cpu_set_t *__cpuset_alloc(int num_cpus);

void __cpuset_free(cpu_set_t *set);

static __inline cpu_set_t *CPU_ALLOC(int num_cpus)
{
  return __cpuset_alloc(num_cpus);
}

static __inline void CPU_FREE(cpu_set_t *set)
{
  __cpuset_free(set);
}

static __inline void CPU_ZERO_S(size_t setsize, cpu_set_t *set)
{
  BIT_ZERO(_cpu_set_bits(setsize), set);
}

static __inline void CPU_ZERO(cpu_set_t *set)
{
  CPU_ZERO_S(sizeof(*set), set);
}

static __inline void CPU_FILL_S(size_t setsize, cpu_set_t *set)
{
  BIT_FILL(_cpu_set_bits(setsize), set);
}

static __inline void CPU_FILL(cpu_set_t *set)
{
  CPU_FILL_S(sizeof(*set), set);
}

static __inline void CPU_SET_S(int cpu, size_t setsize, cpu_set_t *set)
{
  BIT_SET(_cpu_set_bits(setsize), cpu, set);
}

static __inline void CPU_SET(int cpu, cpu_set_t *set)
{
  CPU_SET_S(cpu, sizeof(*set), set);
}

static __inline void CPU_CLR_S(int cpu, size_t setsize, cpu_set_t *set)
{
  BIT_CLR(_cpu_set_bits(setsize), cpu, set);
}

static __inline void CPU_CLR(int cpu, cpu_set_t *set)
{
  CPU_CLR_S(cpu, sizeof(*set), set);
}

static __inline int CPU_ISSET_S(int cpu, size_t setsize, const cpu_set_t *set)
{
  return BIT_ISSET(_cpu_set_bits(setsize), cpu, set);
}

static __inline int CPU_ISSET(int cpu, const cpu_set_t *set)
{
  return CPU_ISSET_S(cpu, sizeof(*set), set);
}

static __inline void CPU_COPY(const cpu_set_t *src, cpu_set_t *dest)
{
  BIT_COPY(_cpu_set_bits(setsize), src, dest);
}

static __inline void CPU_AND_S(size_t setsize, cpu_set_t *destset,
  const cpu_set_t *srcset1, const cpu_set_t *srcset2)
{
  BIT_AND2(_cpu_set_bits(setsize), destset, srcset1, srcset2);
}

static __inline void CPU_AND(cpu_set_t *destset, const cpu_set_t *srcset1,
  const cpu_set_t *srcset2)
{
  CPU_AND_S(sizeof(*destset), destset, srcset1, srcset2);
}

static __inline void CPU_OR_S(size_t setsize, cpu_set_t *destset,
  const cpu_set_t *srcset1, const cpu_set_t *srcset2)
{
  BIT_OR2(_cpu_set_bits(setsize), destset, srcset1, srcset2);
}

static __inline void CPU_OR(cpu_set_t *destset, const cpu_set_t *srcset1,
  const cpu_set_t *srcset2)
{
  CPU_OR_S(sizeof(*destset), destset, srcset1, srcset2);
}

static __inline void CPU_XOR_S(size_t setsize, cpu_set_t *destset,
  const cpu_set_t *srcset1, const cpu_set_t *srcset2)
{
  BIT_XOR2(_cpu_set_bits(setsize), destset, srcset1, srcset2);
}

static __inline void CPU_XOR(cpu_set_t *destset, const cpu_set_t *srcset1,
  const cpu_set_t *srcset2)
{
  CPU_XOR_S(sizeof(*destset), destset, srcset1, srcset2);
}

static __inline void CPU_NAND_S(size_t setsize, cpu_set_t *destset,
  const cpu_set_t *srcset1, const cpu_set_t *srcset2)
{
  BIT_NAND2(_cpu_set_bits(setsize), destset, srcset1, srcset2);
}

static __inline void CPU_NAND(cpu_set_t *destset, const cpu_set_t *srcset1,
  const cpu_set_t *srcset2)
{
  CPU_NAND_S(sizeof(*destset), destset, srcset1, srcset2);
}

static __inline int CPU_COUNT_S(size_t setsize, const cpu_set_t *set)
{
  return BIT_COUNT(_cpu_set_bits(setsize), set);
}

static __inline int CPU_COUNT(const cpu_set_t *set)
{
  return CPU_COUNT_S(sizeof(*set), set);
}

static __inline int CPU_EQUAL_S(size_t setsize, const cpu_set_t *set1,
  const cpu_set_t *set2)
{
  return !BIT_CMP(_cpu_set_bits(setsize), set1, set2);
}

static __inline int CPU_EQUAL(const cpu_set_t *set1, const cpu_set_t *set2)
{
  return CPU_EQUAL_S(sizeof(*set1), set1, set2);
}

static __inline int CPU_CMP(const cpu_set_t *set1, const cpu_set_t *set2)
{
  return BIT_CMP(CPU_SETSIZE, set1, set2);
}

static __inline int CPU_EMPTY(const cpu_set_t *set)
{
  return BIT_EMPTY(_cpu_set_bits(sizeof(*set)), set);
}

__END_DECLS

#endif /* !_SYS_CPUSET_H_ */
