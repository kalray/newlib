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

#include <stdint.h>
#include <assert.h>
#include <kv3/registers.h>
#include <kv3/bsp.h>

/**
 * Core routines
 */

int __gloss_kvx_is_rm(void)
{
  if (KVX_SFR_GET_FIELD(__builtin_kvx_get(KVX_SFR_PCR), PCR_PID) == 0x10)
    return 1;

  return 0;
}

int __gloss_kvx_get_cpu_id(void)
{
  return (int) KVX_SFR_GET_FIELD(__builtin_kvx_get(KVX_SFR_PCR), PCR_PID);
}

int __gloss_kvx_get_rm_id(void)
{
  return __GLOSS_KVX_RM_ID;
}

void __gloss_kvx_hwloops_enable(void)
{
  __builtin_kvx_wfxl(KVX_SFR_PS, KVX_SFR_PS_HLE_WFXL_SET);
}

void __gloss_kvx_hwloops_disable(void)
{
  __builtin_kvx_wfxl(KVX_SFR_PS, KVX_SFR_PS_HLE_WFXL_CLEAR);
}

void __gloss_kvx_clear_wup_mask(unsigned int mask)
{
  __builtin_kvx_wfxl(KVX_SFR_WS, mask);
}

void __gloss_kvx_set_wup_mask(unsigned int mask)
{
  __builtin_kvx_wfxl(KVX_SFR_WS, (uint64_t)mask << 32);
}

/**
 * Cluster routines
 */

int __gloss_kvx_get_cluster_id(void)
{
  return (int)KVX_SFR_GET_FIELD(__builtin_kvx_get(KVX_SFR_PCR), PCR_CID);
}

/**
 * Interrupts routines
 */

/**
 * \fn void __gloss_kvx_interrupt_level_set(uint32_t level)
 * \brief Sets the current level of priority.
 * \param level new level of priority
 */

void __gloss_kvx_interrupt_level_set(uint32_t level)
{
  __builtin_kvx_wfxl(KVX_SFR_PS, KVX_SFR_WFXL_VALUE(PS_IL, level));
}

/**
 * \fn static inline void __gloss_kvx_interrupt_priorities_equal(void)
 * \brief Set all interrupt lines to the same priority (1)
 */
void __gloss_kvx_interrupt_priorities_equal(void)
{
  __builtin_kvx_set(KVX_SFR_ILL, 0x5555555555555555ULL);
}

/**
 * \fn void __gloss_kvx_interrupt_enable(void)
 * \brief Enable interrupts
 */
void __gloss_kvx_interrupt_enable(void)
{
  __builtin_kvx_wfxl(KVX_SFR_PS, (long long)KVX_SFR_PS_IE_MASK << 32);
}

/**
 * \fn void __gloss_kvx_interrupt_disable(void)
 * \brief Disable interrupts
 */
void
__gloss_kvx_interrupt_disable(void)
{
  __builtin_kvx_wfxl(KVX_SFR_PS, KVX_SFR_PS_IE_MASK);
}

/**
 * \fn void __gloss_kvx_interrupt_init(void)
 * \brief Enable interrupts and set them to equal priority
 */
void
__gloss_kvx_interrupt_init(void)
{
  __gloss_kvx_interrupt_level_set(0);
  __gloss_kvx_interrupt_priorities_equal();
  __gloss_kvx_interrupt_enable();
}

/**
 * \fn void __gloss_kvx_interrupt_enable_num(unsigned int x)
 * \brief Enable an interrupt line
 * \param x Interrupt number
 */
void __gloss_kvx_interrupt_enable_num(unsigned int x)
{
  __builtin_kvx_wfxl(KVX_SFR_ILE, 1ull << (32 + x));
}

/**
 * \fn void __gloss_kvx_interrupt_set_priority(unsigned int num, uint8_t prio)
 * \brief Set interrupt line to given priority
 * \param num Interrupt number
 * \param prio Priority number
 */
void __gloss_kvx_interrupt_set_priority(unsigned int num, uint8_t prio)
{
  unsigned int num_sfr = num >> 5;
  unsigned int sfr_half = (num & 0x10) >> 4;
  uint64_t prio4 = prio & 0x3;
  uint64_t num_it = num;

  assert(num_sfr == 0);
  assert(prio <= 3);

  if (sfr_half == 0) {
    uint64_t clrmask = (0x3ULL << (2*(num_it & 0xF)));
    uint64_t setmask = (prio4 << (32 + 2*(num_it & 0xF)));

    __builtin_kvx_wfxl(KVX_SFR_ILL, setmask | clrmask);
  } else {
    uint64_t clrmask = (0x3ULL << (2*num_it - 32));
    uint64_t setmask = (prio4 << (2*num_it));

    __builtin_kvx_wfxm(KVX_SFR_ILL, setmask | clrmask);
  }
}

/**
 * \fn void __gloss_kvx_interrupt_configure_dame(void)
 * \brief Configure DAME interrupt : enable it + set its (relative) priority to 3
 */
void __gloss_kvx_interrupt_configure_dame(void)
{
  __gloss_kvx_interrupt_set_priority(__GLOSS_KVX_PE_INT_LINE_DAME, 3);
  __gloss_kvx_interrupt_enable_num(__GLOSS_KVX_PE_INT_LINE_DAME);
}

/**
 * APIC routines
 */

#include <machine/kv3/mppa3-80/gic.h>

void __apic_gic_init(void)
{
  int i;
  int j;
  int k;

  // Write zeroes
  for (i = 0; i < NB_APIC_GIC_INTERRUPT_GROUP; i++) {
    for (j = 0; j < NB_APIC_GIC_INTERRUPT_PER_GROUP; j++) {
      for (k = 0; k < NB_APIC_GIC_INTERRUPT_SOURCE; k++) {
	mppa_gic_local->gic[i][j].enable[k].reg = 0;
      }

      for (k = 0; k < NB_APIC_GIC_INTERRUPT_STATUS; k++) {
	mppa_gic_local->gic[i][j].status[k].reg = 0xFFFFFFFFFFFFFFFFULL;
      }

      mppa_gic_local->gic[i][j].access_policy.reg = 0;
    }
  }
}

#include <machine/kv3/mppa3-80/mailbox.h>

void __apic_mailbox_init(void)
{
  int i;
  int j;

  // Write zeroes
  for (i = 0; i < NB_APIC_MAILBOX_GROUP; i++) {
    for (j = 0; j < NB_APIC_MAILBOX_PER_GROUP; j++) {
#ifdef __kvxarch_kv3_1
      mppa_mailbox_local->mailbox[i][j].access_policy.reg = 0;
#endif
      mppa_mailbox_local->mailbox[i][j].mask.reg          = 0;
      mppa_mailbox_local->mailbox[i][j].funct.reg         = 0;
      mppa_mailbox_local->mailbox[i][j].mailbox.reg       = 0;
    }
  }

}

/**
 * L2 cache routines
 */

#include <machine/kv3/mppa3-80/pwr_ctrl.h>
#include <machine/kv3/mppa3-80/secure_cluster_regs.h>
#include <machine/kv3/mppa3-80/l2_cache.h>

static void __l2_enable(void)
{
  /* Enable L1 cache */
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->global_config.set), 1 << PWR_GLOB_CACHE_EN_IDX);
}

static void __l2_disable(void)
{
  /* Enable L1 cache */
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->global_config.clear), 1 << PWR_GLOB_CACHE_EN_IDX);
}

void __l2_init_metadata(void)
{
  int i;
  uint64_t ecc_status;

  /* Need to enable the l2 cache to be able to write the metadata */
  __l2_enable();

  /* initialize L2 TAGS, readers and dirty */
  for (i = 0; i < NB_SMEM_READERS; i++) {
    mppa_l2_local->tcm_metadata[i].tcm_tag.dword[0] = (0xFull << ((unsigned long long) L2_TAG_RDR_CLR_IDX)
						       | 1ull << ((unsigned long long) L2_TAG_DRT_CLR_IDX));
  }
  for (i = 0; i < NB_TAGS; i++) {
    mppa_l2_local->l2_metadata[i].l2_tag.dword[0] = (0xFull << ((unsigned long long) L2_TAG_RDR_CLR_IDX)
						     | 1ull << ((unsigned long long) L2_TAG_DRT_CLR_IDX));
  }
  /* Initializing L2 Tag generates SECC Error => clear ecc_status of power controler*/
  __builtin_kvx_fence();
  ecc_status = mppa_pwr_ctrl_local->ecc_status.reg;

  if (ecc_status != 0) {
    ecc_status = mppa_pwr_ctrl_local->ecc_status_clear.reg;
  }

  __l2_disable();
}

/**
 * Power Controller routines
 */

void __gloss_kvx_set_pwr_pen_uen(void)
{
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->global_config.set), MPPA_PWR_CTRL_GLOBAL_CONFIG_USER_EN__MASK | MPPA_PWR_CTRL_GLOBAL_CONFIG_PE_EN__MASK);
}

void __gloss_kvx_clear_pwc_reset_on_wup(int cpuid)
{
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->vector_proc_control.reset_on_wakeup.clear), (1ULL << cpuid));
}

void __gloss_kvx_set_pwc_wup(int cpuid)
{
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->vector_proc_control.wup.set), (1ULL << cpuid));
}

void __gloss_kvx_clear_pwc_wup(int cpuid)
{
  __gloss_kvx_volatile_write64((void *)&(mppa_pwr_ctrl_local->vector_proc_control.wup.clear), (1ULL << cpuid));
}

void __gloss_kvx_pwc_init(void)
{
  int cpuid;

  cpuid = __gloss_kvx_get_cpu_id();

  /* PEN/KEN settings */
  if (cpuid == __GLOSS_KVX_RM_ID) {
    __gloss_kvx_set_pwr_pen_uen();
  }
  /* Default settings : be ready to idle + resume execution linearly after wup
   * (after clearing the relevant WS.WU* bits)
   */
  __gloss_kvx_clear_pwc_reset_on_wup(cpuid);
  __gloss_kvx_clear_pwc_wup(cpuid);
  __builtin_kvx_fence();
}

extern void __kvx_stop(void);
void __gloss_kvx_cluster_poweroff(void)
{
  /* Waiting for power controler implementation */
  __kvx_stop();
}

/**
 * IO write routine
 */

void __gloss_kvx_volatile_write64(void *addr, uint64_t val)
{
  *(volatile uint64_t *)addr = val;
}
