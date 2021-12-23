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

#include <sys/reent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"	{
#endif

  extern void  __libc_init_array(void);
  extern void  __libc_fini_array(void);
  extern int trace_pc_config(void) __attribute__((weak));

  __thread struct _reent _impure_thread_data;

  void __kvx_finish_newlib_init(void)
  {
    _REENT_INIT_PTR(&_impure_thread_data);
    /* Finish initialization of reent */
    _REENT->_stdin = &(_REENT->__sf[0]);
    _REENT->_stdout = &(_REENT->__sf[1]);
    _REENT->_stderr = &(_REENT->__sf[2]);
  }

  int __kvx_trace_pc_init(void)
  {
    if (trace_pc_config)
      return trace_pc_config();
    return 0;
  }

  extern int    _fwalk_reent (struct _reent *, int (*)(struct _reent *, FILE *));
  void __kvx_newlib_flushall()
  {
    /* Flush all I/O for the current core */
    _fwalk_reent (_REENT, _fflush_r);
  }

  extern int main (int argc, char **argv, char **env);


  void __start1(int argc, char **argv, char  **envp)
  {
    int res;

    __kvx_finish_newlib_init();

    /* Run the main function */
    __libc_init_array ();
    atexit (__libc_fini_array);

    atexit (__kvx_newlib_flushall);


    res = __kvx_trace_pc_init();
    if (!res)
      res = main(argc, argv, envp);

    exit(res);
    while(1);
  }

#ifdef __cplusplus
}
#endif
