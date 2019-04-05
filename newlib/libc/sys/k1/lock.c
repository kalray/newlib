/* This file has been modified or added by Kalray, SA. 2010-11 */
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
