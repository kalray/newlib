#include <sys/reent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"	{
#endif


  extern void _init(void) __attribute__((weak));
  extern void _fini(void) __attribute__((weak));

  __thread struct _reent _impure_thread_data;

  void __k1_finish_newlib_init(void)
  {
    _REENT_INIT_PTR(&_impure_thread_data);
    /* Finish initialization of reent */
    _REENT->_stdin = &(_REENT->__sf[0]);
    _REENT->_stdout = &(_REENT->__sf[1]);
    _REENT->_stderr = &(_REENT->__sf[2]);
  }


  extern int    _fwalk_reent (struct _reent *, int (*)(struct _reent *, FILE *));
  void newlib_flushall()
  {
    /* Flush all I/O for the current core */
    _fwalk_reent (_REENT, _fflush_r);
  }

  void __start1(int argc, char **argv, char  **envp)
  {


    int res;
    //  _bsp_initialize();

    __k1_finish_newlib_init();

    /* Run the main function */
    if (_init) _init ();
    if (_fini) atexit (_fini);

    atexit (newlib_flushall);

    res = main(argc, argv, envp);
    exit(res);
    while(1);
  }

#ifdef __cplusplus
}
#endif
