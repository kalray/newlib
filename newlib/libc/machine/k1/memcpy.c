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


#include <_ansi.h>
#include <string.h>

#define MEMCPY_STREAMING_PIPELINE_SIZE (256)

/**
 * This memcpy does not realign streams,
 * since it must use copro to absorb SMEM latency.
 */
void *
memcpy (void *__restrict dst0,
    const void *__restrict src0,
    size_t len0)
{
  void *ret = dst0;

  if (!len0)
    goto early_exit;

  if (len0 >= MEMCPY_STREAMING_PIPELINE_SIZE) {

    register __int128 tmp0 asm("$r32r33");
    register __int128 tmp1 asm("$r34r35");
    register __int128 tmp2 asm("$r36r37");
    register __int128 tmp3 asm("$r38r39");
    register __int128 tmp4 asm("$r40r41");
    register __int128 tmp5 asm("$r42r43");
    register __int128 tmp6 asm("$r44r45");
    register __int128 tmp7 asm("$r46r47");
    register __int128 tmp8 asm("$r48r49");
    register __int128 tmp9 asm("$r50r51");
    register __int128 tmp10 asm("$r52r53");
    register __int128 tmp11 asm("$r54r55");
    register __int128 tmp12 asm("$r56r57");
    register __int128 tmp13 asm("$r58r59");
    register __int128 tmp14 asm("$r60r61");
    register __int128 tmp15 asm("$r62r63");

    asm("lq.u %0 = 0[%1]\n\t;;\n"   : "=r"(tmp0)  : "r"(src0) :);
    asm("lq.u %0 = 16[%1]\n\t;;\n"  : "=r"(tmp1)  : "r"(src0) :);
    asm("lq.u %0 = 32[%1]\n\t;;\n"  : "=r"(tmp2)  : "r"(src0) :);
    asm("lq.u %0 = 48[%1]\n\t;;\n"  : "=r"(tmp3)  : "r"(src0) :);
    asm("lq.u %0 = 64[%1]\n\t;;\n"  : "=r"(tmp4)  : "r"(src0) :);
    asm("lq.u %0 = 80[%1]\n\t;;\n"  : "=r"(tmp5)  : "r"(src0) :);
    asm("lq.u %0 = 96[%1]\n\t;;\n"  : "=r"(tmp6)  : "r"(src0) :);
    asm("lq.u %0 = 112[%1]\n\t;;\n" : "=r"(tmp7)  : "r"(src0) :);
    asm("lq.u %0 = 128[%1]\n\t;;\n" : "=r"(tmp8)  : "r"(src0) :);
    asm("lq.u %0 = 144[%1]\n\t;;\n" : "=r"(tmp9)  : "r"(src0) :);
    asm("lq.u %0 = 160[%1]\n\t;;\n" : "=r"(tmp10) : "r"(src0) :);
    asm("lq.u %0 = 176[%1]\n\t;;\n" : "=r"(tmp11) : "r"(src0) :);
    asm("lq.u %0 = 192[%1]\n\t;;\n" : "=r"(tmp12) : "r"(src0) :);
    asm("lq.u %0 = 208[%1]\n\t;;\n" : "=r"(tmp13) : "r"(src0) :);
    asm("lq.u %0 = 224[%1]\n\t;;\n" : "=r"(tmp14) : "r"(src0) :);
    asm("lq.u %0 = 240[%1]\n\t;;\n" : "=r"(tmp15) : "r"(src0) :);

    len0 -= MEMCPY_STREAMING_PIPELINE_SIZE;
    src0 += MEMCPY_STREAMING_PIPELINE_SIZE;

    while (len0 >= MEMCPY_STREAMING_PIPELINE_SIZE) {

      len0 -= MEMCPY_STREAMING_PIPELINE_SIZE;

      asm("sq 0[%0] = %1\n\t;;\n"   : : "r"(dst0), "r"(tmp0)  :);
      asm("lq.u %0 = 0[%1]\n\t;;\n"   : "=r"(tmp0)  : "r"(src0) :);
      asm("sq 16[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp1)  :);
      asm("lq.u %0 = 16[%1]\n\t;;\n"  : "=r"(tmp1)  : "r"(src0) :);
      asm("sq 32[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp2)  :);
      asm("lq.u %0 = 32[%1]\n\t;;\n"  : "=r"(tmp2)  : "r"(src0) :);
      asm("sq 48[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp3)  :);
      asm("lq.u %0 = 48[%1]\n\t;;\n"  : "=r"(tmp3)  : "r"(src0) :);
      asm("sq 64[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp4)  :);
      asm("lq.u %0 = 64[%1]\n\t;;\n"  : "=r"(tmp4)  : "r"(src0) :);
      asm("sq 80[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp5)  :);
      asm("lq.u %0 = 80[%1]\n\t;;\n"  : "=r"(tmp5)  : "r"(src0) :);
      asm("sq 96[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp6)  :);
      asm("lq.u %0 = 96[%1]\n\t;;\n"  : "=r"(tmp6)  : "r"(src0) :);
      asm("sq 112[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp7)  :);
      asm("lq.u %0 = 112[%1]\n\t;;\n" : "=r"(tmp7)  : "r"(src0) :);
      asm("sq 128[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp8)  :);
      asm("lq.u %0 = 128[%1]\n\t;;\n" : "=r"(tmp8)  : "r"(src0) :);
      asm("sq 144[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp9)  :);
      asm("lq.u %0 = 144[%1]\n\t;;\n" : "=r"(tmp9)  : "r"(src0) :);
      asm("sq 160[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp10) :);
      asm("lq.u %0 = 160[%1]\n\t;;\n" : "=r"(tmp10) : "r"(src0) :);
      asm("sq 176[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp11) :);
      asm("lq.u %0 = 176[%1]\n\t;;\n" : "=r"(tmp11) : "r"(src0) :);
      asm("sq 192[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp12) :);
      asm("lq.u %0 = 192[%1]\n\t;;\n" : "=r"(tmp12) : "r"(src0) :);
      asm("sq 208[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp13) :);
      asm("lq.u %0 = 208[%1]\n\t;;\n" : "=r"(tmp13) : "r"(src0) :);
      asm("sq 224[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp14) :);
      asm("lq.u %0 = 224[%1]\n\t;;\n" : "=r"(tmp14) : "r"(src0) :);
      asm("sq 240[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp15) :);
      asm("lq.u %0 = 240[%1]\n\t;;\n" : "=r"(tmp15) : "r"(src0) :);

      src0 += MEMCPY_STREAMING_PIPELINE_SIZE;
      dst0 += MEMCPY_STREAMING_PIPELINE_SIZE;
    }

    asm("sq 0[%0] = %1\n\t;;\n"   : : "r"(dst0), "r"(tmp0)  :);
    asm("sq 16[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp1)  :);
    asm("sq 32[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp2)  :);
    asm("sq 48[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp3)  :);
    asm("sq 64[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp4)  :);
    asm("sq 80[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp5)  :);
    asm("sq 96[%0] = %1\n\t;;\n"  : : "r"(dst0), "r"(tmp6)  :);
    asm("sq 112[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp7)  :);
    asm("sq 128[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp8)  :);
    asm("sq 144[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp9)  :);
    asm("sq 160[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp10) :);
    asm("sq 176[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp11) :);
    asm("sq 192[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp12) :);
    asm("sq 208[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp13) :);
    asm("sq 224[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp14) :);
    asm("sq 240[%0] = %1\n\t;;\n" : : "r"(dst0), "r"(tmp15) :);

    dst0 += MEMCPY_STREAMING_PIPELINE_SIZE;
  }

  long long *__restrict dst8 = dst0;
  const long long *__restrict src8 = src0;

  while (len0 >= sizeof(*dst8)) {
    *dst8++ = *src8++;
    len0 -= sizeof(*dst8);
    dst0 += sizeof(*dst8);
    src0 += sizeof(*dst8);
  }

  char *__restrict dst = dst0;
  const char *__restrict src = src0;

  while (len0--) {
    *dst++ = *src++;
  }

early_exit:
  return ret;
}
