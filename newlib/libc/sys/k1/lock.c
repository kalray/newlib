/*
 * Copyright 2009-2019
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

#ifdef __mppa_bare_runtime__

#include <sys/lock.h>

#include <mppa_bare_runtime/k1c/context.h>
#include <mppa_bare_runtime/k1c/syscall.h>
#include <mppa_bare_runtime/k1c/scall_no.h>
#include <mppa_bare_runtime/k1c/registers.h>
#include <mppa_bare_runtime/k1c/atomic.h>
#include <mppa_bare_runtime/k1c/cache.h>

static inline unsigned long long libc_get_id(void)
{
  return __k1_get_cpu_id() + 1;
}

static inline void libc_cache_flush(void)
{
  __k1_mb();
}

int __libc_lock_init_recursive(__libc_lock_recursive_t *lock)
{
	 __k1_recursive_initlock_base(&lock->lock);
	 return 0;
}

int __libc_lock_close_recursive(__libc_lock_recursive_t *lock)
{
  return 0;
}

int __libc_lock_acquire_recursive(__libc_lock_recursive_t *lock)
{
  unsigned int backoff;
  while (__libc_lock_try_acquire_recursive(lock)) {
    volatile int i;
    backoff = libc_get_id ();
    for (i = 0; i < backoff; i++);
    backoff += 13;
  }
  /* invalidate cache when we get lock */
  libc_cache_flush();
  return 0;
}

int __libc_lock_try_acquire_recursive(__libc_lock_recursive_t *lock)
{
	 unsigned long long myself;
	 unsigned long long owner;
	 int res;

	 myself = libc_get_id();
	 res = __k1_recursive_trylock_base(&lock->lock, myself);
	 if (res == 1)
	   libc_cache_flush();
	 return !res;
}

int __libc_lock_release_recursive(__libc_lock_recursive_t *lock)
{
	 unsigned long long myself;
	 myself = libc_get_id();
	 libc_cache_flush();
	 __k1_recursive_unlock_base(&lock->lock, myself);
	 return 0;
}
#endif
