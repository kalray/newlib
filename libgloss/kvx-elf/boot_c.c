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
#include <string.h>
#include <kv3/registers.h>
#include <kv3/trap.h>
#include <kv3/boot_args.h>
#include <kv3/context.h>
#include <kv3/assert.h>
#include <kv3/linker_symbols.h>

#include <kv3/boot_c.h>
#include <kv3/bsp.h>

void __kvx_start_pe(int cpuid, void *start_address, void *args_address, void *stack_address)
{
  __GLOSS_KVX_PE_START_ADDRESS[cpuid] = start_address;
  __GLOSS_KVX_PE_ARGS_ADDRESS[cpuid]  = args_address;
  __GLOSS_KVX_PE_STACK_ADDRESS[cpuid] = stack_address;

  __builtin_kvx_fence();
  __gloss_kvx_set_pwc_wup(cpuid);
}

void __kvx_stop(void)
{
  /* The goal here is to try stopping execution as hard as we can, but not to reboot if ever we were sent a subsequent wup by mistake
   * => make sure that pwc reset_on_wakeup + wup bits are cleared before going to idle
   */
  int cpuid;

  cpuid = __gloss_kvx_get_cpu_id();

  __gloss_kvx_clear_pwc_reset_on_wup(cpuid);

  while (1) {
    __gloss_kvx_clear_pwc_wup(cpuid);
    __builtin_kvx_fence();

    __gloss_kvx_clear_wup_mask(KVX_SFR_WS_WU2_MASK);
    __builtin_kvx_stop();
  }
}

static void __kvx_low_level_startup()
{
  /* set exception vector */
  __builtin_kvx_set(KVX_SFR_EV, (uintptr_t)&KVX_EXCEPTION_ADDRESS);

  /* set PS fields */
  uint64_t flags = ((uint64_t)(KVX_SFR_PS_ICE_MASK /* icache enable */
			       | KVX_SFR_PS_DCE_MASK /* dcache enable */
			       | KVX_SFR_PS_USE_MASK /* streaming load enable */
			       | KVX_SFR_PS_HLE_MASK /* hardware loop enable */
			       ) << 32);

  /* clear PS fields */
  flags |= KVX_SFR_PS_ET_MASK; /* Clear Exception Taken bit */

  /* Set PS register */
  __builtin_kvx_wfxl(KVX_SFR_PS, flags);

  /* enable interrupts */
  __gloss_kvx_interrupt_init();

  /* enable DAME (Data Asynchronous Memory Error) interrupt + configure its priority to the maximum level (15) */
  __gloss_kvx_interrupt_configure_dame();


  if (__gloss_kvx_is_rm()) {
    /* initialization of RAMs*/
    __l2_init_metadata();
    __apic_gic_init();
    __apic_mailbox_init();
  }

  __builtin_kvx_wfxm(KVX_SFR_PCR, KVX_SFR_WFXM_VALUE(PCR_L1CE, 1)); /* L1 coherency enable */
  __builtin_kvx_dinval(); /* invalidate the data cache after turning on the L1 coherency so that we don't keep hot data in the cache that the directory is not aware of  */

  /* Check PL : if PL0 : switch to PL1, if not
   *(i.e. with jtag already in PL1) do nothing
   */
  if (__kvx_get_privilege_level() == 0) {

    /* Currently on PL0 : switch to PL1 to support debug hot attach */
    /* Delegate IT management to PL1, except ITs 23:21 (SW ITs) */
    __builtin_kvx_wfxl(KVX_SFR_ITOW, 0x5555555500000000);

    __builtin_kvx_wfxm(KVX_SFR_ITOW, 0x5555015500000000);

    /* Delegate syscall to PL1 : except Q3 */
    __builtin_kvx_wfxl(KVX_SFR_SYOW, 0x1500000000);

    /* Delegate all PS management to PL1 */
    /* Except SMR, SME and HTD */
    __builtin_kvx_wfxl(KVX_SFR_PSOW, 0x5555551500000000);

    __builtin_kvx_wfxm(KVX_SFR_PSOW, 0x1550500000000);

    /* Delegate all Misc ownership to PL1 */
    __builtin_kvx_wfxl(KVX_SFR_MOW, 0x5555555500000000);

    __builtin_kvx_wfxm(KVX_SFR_MOW, 0x100000000);

    #ifndef __kvxarch_kv3_1
    __builtin_kvx_wfxm(KVX_SFR_MOW,
              (1ULL << KVX_SFR_MOW_TPCM_SHIFT)
            | (1ULL << KVX_SFR_MOW_PM4_SHIFT)
            | (1ULL << KVX_SFR_MOW_PM5_SHIFT)
            | (1ULL << KVX_SFR_MOW_PM6_SHIFT)
            | (1ULL << KVX_SFR_MOW_PM7_SHIFT)
    );
    #endif

    /* Delegate all traps to PL1 except DE, *ECC, *PAR */
    __builtin_kvx_wfxl(KVX_SFR_HTOW, 0x145505500000000);

    /* Delegate Breakpoint1 and Watchpoint1 to PL1 */
    __builtin_kvx_wfxl(KVX_SFR_DOW, 0x4400000000);

    __builtin_kvx_set(KVX_SFR_SPS,
		     (__builtin_kvx_get(KVX_SFR_PS) & (~KVX_SFR_PS_PL_MASK))|0x1);

    __asm__ goto __volatile__ (
			  "make $r1 = %l0\n"
			  ";;\n"
			  "set $spc = $r1\n"
			  ";;\n"
			  "rfe\n"
			  ";;\n"
			  : /* no outputs */
                          : /* no inputs */
                          : "r1" /* clobbers */
                          : spc_pl1_label ); /* labels */
    spc_pl1_label:
        /* set ev_pl1 to default exception vector as for privilege level 0 */
        __builtin_kvx_set(KVX_SFR_EV, (uintptr_t)&KVX_EXCEPTION_ADDRESS);
  }

  /* If power controler exists, switch it on */
  __gloss_kvx_pwc_init();
}

void __kvx_do_rm_before_startup(void) __attribute__ ((weak));
void __kvx_do_rm_before_startup(void) { }

void __kvx_pe_libc_start(void *_args)
{
  kvx_boot_args_t *args = (kvx_boot_args_t*)_args;
  __start1(args->argc, args->argv, args->envp); /* jump to libc */
}

static kvx_boot_args_t __kvx_libc_args;

extern int execute_main_on_rm __attribute((weak));

/** Start the main program on RM or on PE0 **/
static void __kvx_do_rm_startup(void)
{

  __kvx_get_boot_args(&__kvx_libc_args);
  if(&execute_main_on_rm) {
    __kvx_do_rm_before_startup();
    /* jump to libc */
    __start1(__kvx_libc_args.argc, __kvx_libc_args.argv, __kvx_libc_args.envp);
  }
  else {
    /* Execute main on pe0 */
    int pe_id = 0;
    __kvx_start_pe(pe_id,
		  (void*)&__kvx_pe_libc_start,
		  (void*)&__kvx_libc_args,     /* main routine arguments passed to PE0 */
		  (void*)&KVX_PE_STACK_START); /* Only stack for PE0 is reserved in linker script bare.ld */

  }
}

/** Set up thread local storage for RM **/
static void __kvx_setup_tls(uint8_t *_tls_base)
{
  uintptr_t tls_address = (uintptr_t)_tls_base;

#ifdef __KV3_64__
  __asm__ __volatile__ ("addd $tp = %0, 0\n\t;;" : /* no outputs */ : "r"(tls_address) : "$r13");
#else
  __asm__ __volatile__ ("addw $tp = %0, 0\n\t;;" : /* no outputs */ : "r"(tls_address) : "$r13");
#endif

}

static void __kvx_bss_section(uint8_t *dst, uint32_t size)
{
  memset(dst, 0, size);
  __builtin_kvx_fence();
}


/* TLS base address for RM and PEs. */
static uint8_t *__kvx_tls_rm_base_address(void)
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

static uint8_t *__kvx_tls_pe_base_address(int pid) __attribute__((noinline));
static uint8_t *__kvx_tls_pe_base_address(int pid)
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
    __gloss_kvx_assert(0);
  }
  return (uint8_t *) 0;
}

static void __kvx_rm_init(void)
{
  uint8_t *tls_base = __kvx_tls_rm_base_address();
  uint8_t *tls_data = tls_base;
  uint8_t *tls_bss = tls_data + (_tbss_start - _tdata_start);
  const size_t tdata_sz = _tdata_end - _tdata_start;
  const size_t tbss_sz = _tbss_end - _tbss_start;

  /* The 0 test is needed to workaround a GCC bug: See T6031 */
  if (tdata_sz != 0)
    __builtin_memcpy(tls_data, _tdata_start, tdata_sz);

  __kvx_setup_tls(tls_base);

  __kvx_bss_section(tls_bss, tbss_sz);

  __kvx_bss_section(_bss_start, _bss_end - _bss_start);
}

static void __kvx_pe_init(int pid)
{
  uint8_t *tls_base = __kvx_tls_pe_base_address(pid);
  uint8_t *tls_data = tls_base;
  uint8_t *tls_bss = tls_data + (_tbss_start - _tdata_start);
  const size_t tdata_sz = _tdata_end - _tdata_start;
  const size_t tbss_sz = _tbss_end - _tbss_start;

  /* The 0 test is needed to workaround a GCC bug: See T6031 */
  if (tdata_sz != 0)
    __builtin_memcpy(tls_data, _tdata_start, tdata_sz);

  /* tls setup need to be after the section copy in native simulation in order to set the tls pointer */
  __kvx_setup_tls(tls_base);
  __kvx_bss_section(tls_bss, tbss_sz);
}


void __kvx_rm_c_startup(void) __attribute__ ((weak));
void __kvx_rm_c_startup(void)
{
  __kvx_low_level_startup();
  __kvx_rm_init();
  __kvx_do_rm_startup();
  __kvx_stop();
}

void __kvx_do_pe_before_startup(void) __attribute__ ((weak));
void __kvx_do_pe_before_startup(void)
{
}

/** Exit thread */
void __kvx_do_thread_exit(void) __attribute__ ((weak));
void __kvx_do_thread_exit(void)
{
}

/* Defined in newlib: libgloss/kvx-elf/crt0.c */
void __kvx_finish_newlib_init(void);
int __kvx_trace_pc_init(void);

/** Do PE startup **/
static void __kvx_do_pe_startup(void)
{
  void (*__kvx_code_ptr)(volatile void *) = 0;
  int pid = __gloss_kvx_get_cpu_id();

  volatile void *args_ptr = 0;

  __kvx_pe_init(pid);
  __kvx_code_ptr = __GLOSS_KVX_PE_START_ADDRESS[pid];
  args_ptr = __GLOSS_KVX_PE_ARGS_ADDRESS[pid];

  __kvx_do_pe_before_startup();

  __kvx_finish_newlib_init();

  __kvx_trace_pc_init();
  __kvx_code_ptr(args_ptr);

  __kvx_do_thread_exit();
}

/** Configure PE and run the application **/
void __kvx_pe_c_startup(void) __attribute__ ((weak));
void __kvx_pe_c_startup(void)
{
  __kvx_low_level_startup();
  __kvx_do_pe_startup();
  __kvx_stop();
}
