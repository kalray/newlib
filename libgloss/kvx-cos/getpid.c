/*
 * Stub version of getpid.
 */

#include <errno.h>

int
_getpid ()
{
  errno = ENOSYS;
  return -1;
}

int getpid ()
    __attribute__ ((weak, alias ("_getpid")));
