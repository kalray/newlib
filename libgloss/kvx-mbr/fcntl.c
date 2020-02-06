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

#include <mppa_bare_runtime/kv3/scall_no.h>

#include <fcntl.h>
#include <stdarg.h>
#include "errno.h"

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
