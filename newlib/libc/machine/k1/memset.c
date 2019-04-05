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

#include <inttypes.h>
#include <stdlib.h>

#define USE_DZEROL_THRESHOLD   (96)
#define _K1_DCACHE_LINE_SIZE   ((64*8)/8)

static void *
__newlib_k1_memset_double (void *m, int c, unsigned int n)
{
  unsigned long long cc;
  void *dest  = m;
  char *s     = (char *) m;
  cc = __builtin_k1_sbmm8(c, 0x0101010101010101ULL);
  for (; n >= 8; n -= 8) {
    /* Volatile so that the access isn't split by the compiler */
    *(volatile unsigned long long*)s = cc;
    s += 8;
  }

  if (n & 4) {
    *(unsigned int *)s = cc;
    s += 4;
  }

  if (__builtin_expect(n & 3, 0)) {
    if (n & 2) {
      *(unsigned short *)s = cc;
      s += 2;
    }

    if (n & 1)
      *(unsigned char *)s = cc;
  }

  return dest;
}


static void*
__newlib_k1_memset0(void *m, unsigned int n)
{
  int remain, loop_n;
  void *dest = m;
  char *s = (char *) m;
  int mod = (uintptr_t)s % _K1_DCACHE_LINE_SIZE;

  if (mod) {
    __newlib_k1_memset_double (s, 0, _K1_DCACHE_LINE_SIZE - mod);
    s += _K1_DCACHE_LINE_SIZE - mod;
    n -= _K1_DCACHE_LINE_SIZE - mod;
  }
  remain = n % _K1_DCACHE_LINE_SIZE;
  loop_n = n / _K1_DCACHE_LINE_SIZE;
  if (!loop_n) goto endloop;
  /*
   * What does assembly code
   * int i;
   * for (i = 0; i < loop_n; i++) {
   *   __builtin_k1_dzerol(0, (unsigned int)s);
   *   s += 32;
   * }
   */
#ifdef __K1_64__
  __asm__ __volatile__ (
			"loopdo %1, 1f\n;;\n"

			"dzerol 0[%0]\n"
			"addd %0 = %2, %0\n;;\n"

			"1:\n"
			: "+r" (s)
			: "r" (loop_n), "r" (_K1_DCACHE_LINE_SIZE)
			: "memory"
			);
#else
  __asm__ __volatile__ (
			"loopdo %1, 1f\n;;\n"

			"dzerol 0[%0]\n"
			"addw %0 = %0, %2\n;;\n"

			"1:\n"
			: "+r" (s)
			: "r" (loop_n), "r" (_K1_DCACHE_LINE_SIZE)
			: "memory"
			);
#endif
 endloop:
  if (remain)
    __newlib_k1_memset_double (s, 0, remain);

  return dest;
}

void*
memset(void *m, int c, size_t n)
{
  void *res   = m;
  char *s     = (char *) m;
#ifdef __STRICT_ALIGN__
  while (n > 0 && (long)s & 7) {
    *(char *)s = c;
    ++s; --n;
  }
#endif
  if (c == 0 && n >= USE_DZEROL_THRESHOLD)
    __newlib_k1_memset0(s, n);
  else
    __newlib_k1_memset_double(s, c, n);
  return res;
}
