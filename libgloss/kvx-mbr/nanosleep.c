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
#include <mppa_bare_runtime/kvx/cpu.h>
#include <machine/kv3/mppa3-80/pwr_ctrl.h>
#include <sys/types.h>
#include <stdint.h>

/* _POSIX_TIMERS is not defined for mppa bare runtime. Internal routine __kvx_nanosleep is provided and used in sleep implementation. */
int __kvx_nanosleep(const struct timespec *req, struct timespec *rem)
{
  uint64_t ticks = 0;
  uint64_t cycles;
  uint64_t end;
  if (req) {
    cycles  = mppa_pwr_ctrl_local->dsu_timestamp.dword;
    ticks   = (req->tv_sec + req->tv_nsec / (float) _KVX_NANOSECONDS_PER_SECOND) * _KVX_TIMESTAMP_FREQ;
    end     = cycles + ticks;
    while (mppa_pwr_ctrl_local->dsu_timestamp.dword < end)
      ;

    if (rem) {
      rem->tv_nsec = rem->tv_sec = 0;
    }
  }
  return 0;
}
