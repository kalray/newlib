/* This file has been modified or added by Kalray, SA. 2010 */

#include <hal/cos_scall_no.h>

#include <fcntl.h>
#include <stdarg.h>
#include "errno.h"

/***************************************************************
 *	fcntl
 ***************************************************************/
int sc_fcntl(int fd, int command, long arg);

int _fcntl(int fd, int command, long arg)
{
  int ret;
  int oflags = arg;

  if (command == F_SETFL) {
      oflags = 0;
      if (arg & O_RDONLY)   oflags |= S_RDONLY;
      if (arg & O_WRONLY)   oflags |= S_WRONLY;
      if (arg & O_RDWR)     oflags |= S_RDWR;
      if (arg & O_APPEND)   oflags |= S_APPEND;
      if (arg & O_CREAT)    oflags |= S_CREAT;
      if (arg & O_TRUNC)    oflags |= S_TRUNC;
      if (arg & O_EXCL)     oflags |= S_EXCL;
      if (arg & O_SYNC)     oflags |= S_SYNC;
#ifdef O_NDELAY
      if (arg & O_NDELAY)   oflags |= S_NDELAY;
#endif
      if (arg & O_NONBLOCK) oflags |= S_NONBLOCK;
      if (arg & O_NOCTTY)   oflags |= S_NOCTTY;
  }

  ret = sc_fcntl(fd,command,oflags);

  if( ret < 0 ) {
    errno = ret * -1;
    ret = -1;
  } else if (command == F_GETFL) {
      arg = ret;
      ret = 0;

      if (arg & S_RDONLY)   ret |= O_RDONLY;
      if (arg & S_WRONLY)   ret |= O_WRONLY;
      if (arg & S_RDWR)     ret |= O_RDWR;
      if (arg & S_APPEND)   ret |= O_APPEND;
      if (arg & S_CREAT)    ret |= O_CREAT;
      if (arg & S_TRUNC)    ret |= O_TRUNC;
      if (arg & S_EXCL)     ret |= O_EXCL;
      if (arg & S_SYNC)     ret |= O_SYNC;
#ifdef O_NDELAY
      if (arg & S_NDELAY)   ret |= O_NDELAY;
#endif
      if (arg & S_NONBLOCK) ret |= O_NONBLOCK;
      if (arg & S_NOCTTY)   ret |= O_NOCTTY;
  }

  return ret;
}

int fcntl(int fd, int command, ...)  __attribute__ ((weak, alias ("_fcntl")));
