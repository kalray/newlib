/*
 * Stub version of getpid.
 */

#include <errno.h>

#include <hal/cos_bsp.h>

int
_getpid ()
{
  return 0x1000 | (__cos_get_cluster_id() << 4) | __cos_get_cpu_id();
}

int getpid ()
    __attribute__ ((weak, alias ("_getpid")));
