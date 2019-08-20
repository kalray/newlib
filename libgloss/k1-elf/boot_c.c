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

#include <stdlib.h>
#include <k1c/registers.h>
#include <k1c/trap.h>
#include <k1c/boot_args.h>
#include <k1c/context.h>
#include <k1c/assert.h>
#include <k1c/linker_symbols.h>

#include <k1c/boot_c.h>
#include <k1c/bsp.h>

void __k1_start_pe(int cpuid, void *start_address, void *args_address, void *stack_address)
{
  _K1_PE_START_ADDRESS[cpuid] = start_address;
  _K1_PE_ARGS_ADDRESS[cpuid]  = args_address;
  _K1_PE_STACK_ADDRESS[cpuid] = stack_address;

  __builtin_k1_fence();
  __k1_set_pwc_wup(cpuid);
}

void __k1_stop(void)
{
  /* The goal here is to try stopping execution as hard as we can, but not to reboot if ever we were sent a subsequent wup by mistake
   * => make sure that pwc reset_on_wakeup + wup bits are cleared before going to idle
   */
  int cpuid;

  cpuid = __k1_get_cpu_id();

  __k1_clear_pwc_reset_on_wup(cpuid);

  while (1) {
    __k1_clear_pwc_wup(cpuid);
    __builtin_k1_fence();

    __k1_clear_k1_wup_mask(K1_SFR_WS_WU2_MASK);
    __builtin_k1_stop();
  }
}

static void __k1_low_level_startup()
{
  /* set exception vector */
  __builtin_k1_set(K1_SFR_EV, (uintptr_t)&K1_EXCEPTION_ADDRESS);

  /* set PS fields */
  uint64_t flags = ((uint64_t)(K1_SFR_PS_ICE_MASK /* icache enable */
			       | K1_SFR_PS_DCE_MASK /* dcache enable */
			       | K1_SFR_PS_USE_MASK /* streaming load enable */
			       | K1_SFR_PS_HLE_MASK /* hardware loop enable */
			       ) << 32);

  /* clear PS fields */
  flags |= K1_SFR_PS_ET_MASK; /* Clear Exception Taken bit */

  /* Set PS register */
  __builtin_k1_wfxl(K1_SFR_PS, flags);

  /* enable interrupts */
  __k1_interrupt_init();

  /* enable DAME (Data Asynchronous Memory Error) interrupt + configure its priority to the maximum level (15) */
  __k1_interrupt_configure_dame();


  if (__k1_is_rm()) {
    /* initialization of RAMs*/
    l2_init_metadata();
    apic_gic_init();
    apic_mailbox_init();
  }

  __builtin_k1_wfxm(K1_SFR_PCR, K1_SFR_WFXM_VALUE(PCR_L1CE, 1)); /* L1 coherency enable */
  __builtin_k1_dinval(); /* invalidate the data cache after turning on the L1 coherency so that we don't keep hot data in the cache that the directory is not aware of  */

  /* If power controler exists, switch it on */
  __k1_pwc_init();
}

void __k1_do_rm_before_startup(void) __attribute__ ((weak));
void __k1_do_rm_before_startup(void) { }

void __k1_pe_libc_start(void *_args)
{
  k1_boot_args_t *args = (k1_boot_args_t*)_args;
  __start1(args->argc, args->argv, args->envp); /* jump to libc */
}

static k1_boot_args_t __k1_libc_args;

/** Start the main program on RM or on PE0 **/
static void __k1_do_rm_startup(void)
{
  int execute_main_on_rm = 0;

  get_k1_boot_args(&__k1_libc_args);
  if(execute_main_on_rm) {
    __k1_do_rm_before_startup();
    /* jump to libc */
    __start1(__k1_libc_args.argc, __k1_libc_args.argv, __k1_libc_args.envp);
  }
  else {
    /* Execute main on pe0 */
    int pe_id = 0;
    __k1_start_pe(pe_id,
		  (void*)&__k1_pe_libc_start,
		  (void*)&__k1_libc_args,     /* main routine arguments passed to PE0 */
		  (void*)&K1_PE_STACK_START); /* Only stack for PE0 is reserved in linker script bare.ld */

  }
}

/** Set up thread local storage for RM **/
static void __k1_setup_tls(uint8_t *_tls_base)
{
  uintptr_t tls_address = (uintptr_t)_tls_base;

#ifdef __K1_64__
  __asm__ __volatile__ ("addd $tp = %0, 0\n\t;;" : /* no outputs */ : "r"(tls_address) : "$r13");
#else
  __asm__ __volatile__ ("addw $tp = %0, 0\n\t;;" : /* no outputs */ : "r"(tls_address) : "$r13");
#endif

}

static void __k1_bss_section(uint8_t *dst, uint32_t size)
{
  memset(dst, 0, size);
  __builtin_k1_fence();
}


/* TLS base address for RM and PEs. */
static uint8_t *__k1_tls_rm_base_address(void)
{
  return _tls_rm_start;
}

uint8_t _tls_pe0_start;
uint8_t _tls_pe1_start;
uint8_t _tls_pe2_start;
uint8_t _tls_pe3_start;
uint8_t _tls_pe4_start;
uint8_t _tls_pe5_start;
uint8_t _tls_pe6_start;
uint8_t _tls_pe7_start;
uint8_t _tls_pe8_start;
uint8_t _tls_pe9_start;
uint8_t _tls_pe10_start;
uint8_t _tls_pe11_start;
uint8_t _tls_pe12_start;
uint8_t _tls_pe13_start;
uint8_t _tls_pe14_start;
uint8_t _tls_pe15_start;

static uint8_t *__k1_tls_pe_base_address(int pid) __attribute__((noinline));
static uint8_t *__k1_tls_pe_base_address(int pid)
{
  switch (pid) {
  case 0:	 return &_tls_pe0_start;
  case 1:	 return &_tls_pe1_start;
  case 2:	 return &_tls_pe2_start;
  case 3:	 return &_tls_pe3_start;
  case 4:	 return &_tls_pe4_start;
  case 5:	 return &_tls_pe5_start;
  case 6:	 return &_tls_pe6_start;
  case 7:	 return &_tls_pe7_start;
  case 8:	 return &_tls_pe8_start;
  case 9:	 return &_tls_pe9_start;
  case 10: return &_tls_pe10_start;
  case 11: return &_tls_pe11_start;
  case 12: return &_tls_pe12_start;
  case 13: return &_tls_pe13_start;
  case 14: return &_tls_pe14_start;
  case 15: return &_tls_pe15_start;
  default:
    __k1_assert(0);
  }
  return (uint8_t *) 0;
}

static void __k1_rm_init(void)
{
  uint8_t *tls_base = __k1_tls_rm_base_address();
  uint8_t *tls_data = tls_base;
  uint8_t *tls_bss = tls_data + (_tbss_start - _tdata_start);
  const size_t tdata_sz = _tdata_end - _tdata_start;
  const size_t tbss_sz = _tbss_end - _tbss_start;

  /* The 0 test is needed to workaround a GCC bug: See T6031 */
  if (tdata_sz != 0)
    __builtin_memcpy(tls_data, _tdata_start, tdata_sz);

  __k1_setup_tls(tls_base);

  __k1_bss_section(tls_bss, tbss_sz);

  __k1_bss_section(_bss_start, _bss_end - _bss_start);
  __k1_bss_section(_sbss_start, _sbss_end - _sbss_start);
}

static void __k1_pe_init(int pid)
{
  uint8_t *tls_base = __k1_tls_pe_base_address(pid);
  uint8_t *tls_data = tls_base;
  uint8_t *tls_bss = tls_data + (_tbss_start - _tdata_start);
  const size_t tdata_sz = _tdata_end - _tdata_start;
  const size_t tbss_sz = _tbss_end - _tbss_start;

  /* The 0 test is needed to workaround a GCC bug: See T6031 */
  if (tdata_sz != 0)
    __builtin_memcpy(tls_data, _tdata_start, tdata_sz);

  /* tls setup need to be after the section copy in native simulation in order to set the tls pointer */
  __k1_setup_tls(tls_base);
  __k1_bss_section(tls_bss, tbss_sz);
}


void __k1_rm_c_startup(void) __attribute__ ((weak));
void __k1_rm_c_startup(void)
{
  __k1_low_level_startup();
  __k1_rm_init();
  __k1_do_rm_startup();
  __k1_stop();
}

void __k1_do_pe_before_startup(void) __attribute__ ((weak));
void __k1_do_pe_before_startup(void)
{
}

/** Exit thread */
void __k1_do_thread_exit(void) __attribute__ ((weak));
void __k1_do_thread_exit(void)
{
}

/* Defined in newlib: libgloss/k1-elf/crt0.c */
void __k1_finish_newlib_init(void);

/** Do PE startup **/
static void __k1_do_pe_startup(void)
{
  void (*__k1_code_ptr)(volatile void *) = 0;
  int pid = __k1_get_cpu_id();

  volatile void *args_ptr = 0;

  __k1_pe_init(pid);
  __k1_code_ptr = _K1_PE_START_ADDRESS[pid];
  args_ptr = _K1_PE_ARGS_ADDRESS[pid];

  __k1_do_pe_before_startup();

  __k1_finish_newlib_init();

  __k1_code_ptr(args_ptr);
  __k1_do_thread_exit();
}

/** Configure PE and run the application **/
void __k1_pe_c_startup(void) __attribute__ ((weak));
void __k1_pe_c_startup(void)
{
  __k1_low_level_startup();
  __k1_do_pe_startup();
  __k1_stop();
}
