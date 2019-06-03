/*
 * Stub version of times.
 */

#include <sys/types.h>
#include <sys/times.h>
#include <errno.h>

#include <hal/cos_cpu.h>
#include <hal/cos_diagnostic.h>

int amp_do_syscall_times(struct tms *buf) __attribute__((weak));


int __gloss_times(struct tms *buf)
{
  /*  errno = ENOSYS; */
  int cycle_ratio = _COS_CPU_FREQ / __COS_CLOCKS_PER_SEC__;
  clock_t cycles = __cos_counter_num(0)/ cycle_ratio;
  /* User time */
  if (buf != NULL) {
    buf->tms_utime = cycles;
    /* System time */
    buf->tms_stime = 0;
    /* children's user time */
    buf->tms_cutime = 0;
    /* children's system time */
    buf->tms_cstime = 0;
  }
  return cycles;
}

clock_t
_times (struct tms *buf)
{
  return __gloss_times(buf);
}

clock_t times (struct tms *buf)
    __attribute__ ((weak, alias ("_times")));
