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

#include <k1c/context.h>
#include <k1c/trap.h>

#include <k1c/bsp.h>

#ifdef __GNUC__
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_ ## x
#endif

#define SEP_ERROR_MESSAGE "------------------------------------\n"
#define CLUS_ERROR_MESSAGE "@@@!!! Cluster 00: Trap taken !!!@@@\n"

#define CLUS_DAME_MESSAGE "@@@!!! Cluster 00: Data Asynchronous Memory Error taken (int 16) !!!@@@\n"

int write(int fildes, const void *buf, unsigned int nbyte) __attribute__((weak));
void exit(int status) __attribute__((weak));

int __k1_do_scall(int syscall_nb __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)), int arg0 __attribute__((unused)), int arg1 __attribute__((unused)), int arg2 __attribute__((unused)), int arg3 __attribute__((unused)), int arg4 __attribute__((unused)), int arg5 __attribute__((unused))) __attribute__ ((weak));

void __k1_do_hwtrap(int hwtrap_cause __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused))) __attribute__ ((weak));

void __k1_do_interrupt(int it_number, __k1_context_t *ctxt __attribute__((unused))) __attribute__ ((weak));

void __k1_do_interrupt_dame(int it_number __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused))) __attribute__ ((weak));

void __k1_do_debug(int debug_cause __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused))) __attribute__ ((weak));

void __k1_do_exceptions_pl0(int exception_class __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)), int scall_arg0 __attribute__((unused)), int scall_arg1 __attribute__((unused)), int scall_arg2 __attribute__((unused)), int scall_arg3 __attribute__((unused)), int scall_arg4 __attribute__((unused)), int scall_arg5 __attribute__((unused))) __attribute__ ((weak));

/** Default C-level syscall handler
 *
 * R0 is the syscall number. R1 is the context pointer. R2 to R7 are parameters passed to the syscall.**/
int __k1_do_scall(int syscall_nb __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)), int arg0 __attribute__((unused)), int arg1 __attribute__((unused)), int arg2 __attribute__((unused)), int arg3 __attribute__((unused)), int arg4 __attribute__((unused)), int arg5 __attribute__((unused)))
{
  /* enable hw_loops */
  __k1_hwloops_enable();
  switch (syscall_nb) {
  case 17: /* sc_write */ {
    register int buf asm ("r0") = arg1;
    register int len asm ("r1") = arg2;
    asm volatile ("scall 4094\n\t;;" :: "r"(buf), "r"(len));
    return len;
  }
  case 1: /* sc_exit */ {
    register int val asm ("r0") = arg0;
    asm volatile ("scall 4095\n\t;;" :: "r"(val));
    /* Exit magic syscall. */
  }
  case 4095:
    __k1_cluster_poweroff();
    break;
  default:
    return 0;
  }

  return 0;
}

/** Default C-level exception handler
 */
void __k1_do_hwtrap(int hwtrap_cause  __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)))
{
  char *message;
  int msg_len;
  int c_id = __k1_get_cluster_id();

  /* Manual sprintf to avoid messing with the stack */
  message = CLUS_ERROR_MESSAGE;
  msg_len = sizeof(CLUS_ERROR_MESSAGE);
  if (c_id <= 9) {
    message[16] = c_id + '0';
  } else {
    message[16] = (c_id - 10) + '0';
    message[15] = '1';
  }

  if (write) {
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
    write(1, message, msg_len);
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
  }
  if (exit) {
    exit(1);
  }

  __k1_cluster_poweroff();
}

/** Default C-level interrupt handler.
 *   R0 is the interrupt line.
 */
void (*__k1_int_handlers[_K1_MAX_INT_NUMBER + 1])(int);

void __k1_do_interrupt(int it_number __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)))
{
  if (__k1_int_handlers[it_number])
    __k1_int_handlers[it_number](it_number);

}

void __k1_do_interrupt_dame(int it_number __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)))
{
  char *message;
  int msg_len;
  int c_id = __k1_get_cluster_id();

  /* Manual sprintf to avoid messing with the stack */
  message = CLUS_DAME_MESSAGE;
  msg_len = sizeof(CLUS_DAME_MESSAGE);
  if (c_id <= 9) {
    message[16] = c_id + '0';
  } else {
    message[16] = (c_id - 10) + '0';
    message[15] = '1';
  }

  if (write) {
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
    write(1, message, msg_len);
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
  }
  if (exit) {
    exit(1);
  }

  __k1_cluster_poweroff();
}

void __k1_do_debug(int debug_cause __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)))
{
  char *message;
  int msg_len;
  int c_id = __k1_get_cluster_id();

  /* Manual sprintf to avoid messing with the stack */
  message = CLUS_ERROR_MESSAGE;
  msg_len = sizeof(CLUS_ERROR_MESSAGE);
  if (c_id <= 9) {
    message[16] = c_id + '0';
  } else {
    message[16] = (c_id - 10) + '0';
    message[15] = '1';
  }

  if (write) {
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
    write(1, message, msg_len);
    write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
  }
  if (exit) {
    exit(1);
  }

  __k1_cluster_poweroff();
}


void __k1_do_exceptions_pl0(int exception_class  __attribute__((unused)), __k1_context_t *ctxt __attribute__((unused)), int scall_arg0 __attribute__((unused)), int scall_arg1 __attribute__((unused)), int scall_arg2 __attribute__((unused)), int scall_arg3 __attribute__((unused)), int scall_arg4 __attribute__((unused)), int scall_arg5 __attribute__((unused)))
{

  if (exception_class != K1C_EC_SCALL) {
    char *message;
    int msg_len;
    int c_id = __k1_get_cluster_id();

    /* Manual sprintf to avoid messing with the stack */
    message = CLUS_ERROR_MESSAGE;
    msg_len = sizeof(CLUS_ERROR_MESSAGE);
    if (c_id <= 9) {
      message[16] = c_id + '0';
    } else {
      message[16] = (c_id - 10) + '0';
      message[15] = '1';
    }

    if (write) {
      write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
      write(1, message, msg_len);
      write(1, SEP_ERROR_MESSAGE, sizeof(SEP_ERROR_MESSAGE));
    }
    if (exit) {
      exit(1);
    }
    __k1_cluster_poweroff();
  }
}
