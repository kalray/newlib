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

#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <stdint.h>

#include <machine/kv3/mppa3-80/trace.h>
#include <kv3/bsp.h>

/* _POSIX_TIMERS is not defined for bare. Internal routine __gloss_kvx_nanosleep is provided and used in sleep implementation. */
int __gloss_kvx_nanosleep(const struct timespec *req, struct timespec *rem)
{
  if (req) {
    uint64_t start  = mppa_trace[0]->timestamp_value.dword;
    uint64_t ticks  = (uint64_t)((req->tv_sec + req->tv_nsec /
      (float) TOD_NANOSECONDS_PER_SECOND) * __GLOSS_KVX_TIMESTAMP_FREQ);

    while (ticks > (mppa_trace[0]->timestamp_value.dword - start))
      ;

    if (rem) {
      rem->tv_nsec = rem->tv_sec = 0;
    }
  }
  return 0;
}
