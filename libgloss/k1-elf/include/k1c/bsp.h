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

#ifndef _BSP_H
#define _BSP_H

#  ifndef __ASSEMBLER__

extern volatile void *_K1_PE_STACK_ADDRESS[];
extern volatile void *_K1_PE_ARGS_ADDRESS[];
extern volatile void *_K1_PE_START_ADDRESS[];

#endif /* __ASSEMBLER__ */

/**
 * Core interface
 */

#    ifndef _K1_RM_ID
#      define _K1_RM_ID 16
#    endif
#    ifndef _K1_CPU_FREQ
#      define _K1_CPU_FREQ (800 * 1000 * 1000) /* 800 MHz */
#    endif
#    ifndef __K1_CLOCKS_PER_SEC__
#      define __K1_CLOCKS_PER_SEC__ 1000000
#    endif

#    ifndef _K1_NB_PE
#      define _K1_NB_PE 16
#    endif /* _K1_NB_PE */

#    ifndef _K1_NB_RM
#      define _K1_NB_RM 1
#    endif /* _K1_NB_RM */

#define TOD_NANOSECONDS_PER_SECOND 1000000000ull

#    ifndef _K1_TIMESTAMP_FREQ
#      define _K1_TIMESTAMP_FREQ 100000000ULL
#    endif /* _K1_TIMESTAMP_FREQ */

#  ifndef __ASSEMBLER__

/**
 * \fn int __k1_is_rm(void)
 * \brief Check whether PE is a Ressource Manager
 * \return 1 if PE is a RM, else 0
 */
extern int __k1_is_rm(void) __attribute__((__const__));

/**
 * \fn int __k1_get_cpu_id(void)
 * \brief Get the PE ID
 * \return PE ID
 */
extern int __k1_get_cpu_id(void) __attribute__((__const__));

/**
 * \fn int __k1_get_rm_id(void)
 * \brief Get RM ID
 * \return _K1_RM_ID
 */
extern int __k1_get_rm_id(void);

/**
 * \fn void __k1_hwloops_enable(void)
 * \brief Enable hardware loops
 */
extern void __k1_hwloops_enable(void);

/**
 * \fn void __k1_hwloops_disable(void)
 * \brief Disable hardware loops
 */
extern void __k1_hwloops_disable(void);

extern void __k1_clear_k1_wup_mask(unsigned int mask);

extern void __k1_set_k1_wup_mask(unsigned int mask);

#endif /* __ASSEMBLER__ */

/**
 * Cluster interface
 */

#  ifndef __ASSEMBLER__

/**
 * \fn int __k1_get_cluster_id(void)
 * \brief Get cluster ID
 * \return Cluster ID
 */
extern int __k1_get_cluster_id(void) __attribute__((__const__));

#  endif /* __ASSEMBLER__ */

/**
 * Interrupts interface
 */

#    ifndef _K1_PE_INT_LINE_TIMER0
#      define _K1_PE_INT_LINE_TIMER0 0
#    endif
#    ifndef _K1_PE_INT_LINE_TIMER1
#      define _K1_PE_INT_LINE_TIMER1 1
#    endif
#    ifndef _K1_PE_INT_LINE_WATCHDOG
#      define _K1_PE_INT_LINE_WATCHDOG 2
#    endif
#    ifndef _K1_PE_INT_LINE_BIDIR0
#      define _K1_PE_INT_LINE_BIDIR0 8
#    endif
#    ifndef _K1_PE_INT_LINE_BIDIR1
#      define _K1_PE_INT_LINE_BIDIR1 9
#    endif
#    ifndef _K1_PE_INT_LINE_BIDIR2
#      define _K1_PE_INT_LINE_BIDIR2 10
#    endif
#    ifndef _K1_PE_INT_LINE_BIDIR3
#      define _K1_PE_INT_LINE_BIDIR3 11
#    endif
#    ifndef _K1_PE_INT_LINE_SHOOTDOWN
#      define _K1_PE_INT_LINE_SHOOTDOWN 15
#    endif
#    ifndef _K1_PE_INT_LINE_DAME
#      define _K1_PE_INT_LINE_DAME 16
#    endif
#    ifndef _K1_PE_INT_LINE_CLI
#      define _K1_PE_INT_LINE_CLI 17
#    endif

#    ifndef _K1_RM_INT_LINE_TIMER0
#      define _K1_RM_INT_LINE_TIMER0 0
#    endif
#    ifndef _K1_RM_INT_LINE_TIMER1
#      define _K1_RM_INT_LINE_TIMER1 1
#    endif
#    ifndef _K1_RM_INT_LINE_WATCHDOG
#      define _K1_RM_INT_LINE_WATCHDOG 2
#    endif

#    ifndef _K1_RM_INT_LINE_CNOCRX
#      define _K1_RM_INT_LINE_CNOCRX 3
#    endif
#    ifndef _K1_RM_INT_LINE_DNOCRX
#      define _K1_RM_INT_LINE_DNOCRX 4
#    endif
#    ifndef _K1_RM_INT_LINE_DNOCTX
#      define _K1_RM_INT_LINE_DNOCTX 5
#    endif
#    ifndef _K1_RM_INT_LINE_DNOCERR
#      define _K1_RM_INT_LINE_DNOCERR 6
#    endif

#    ifndef _K1_RM_INT_GIC_BASE
#      define _K1_RM_INT_GIC_BASE 7
#    endif
#    ifndef _K1_RM_INT_LINE_BIDIR0
#      define _K1_RM_INT_LINE_BIDIR0 8
#    endif
#    ifndef _K1_RM_INT_LINE_BIDIR1
#      define _K1_RM_INT_LINE_BIDIR1 9
#    endif
#    ifndef _K1_RM_INT_LINE_BIDIR2
#      define _K1_RM_INT_LINE_BIDIR2 10
#    endif
#    ifndef _K1_RM_INT_LINE_BIDIR3
#      define _K1_RM_INT_LINE_BIDIR3 11
#    endif
#    ifndef _K1_RM_INT_LINE_PEWATCHDOGIRQ
#      define _K1_RM_INT_LINE_PEWATCHDOGIRQ 14
#    endif
#    ifndef _K1_RM_INT_LINE_SHOOTDOWN
#      define _K1_RM_INT_LINE_SHOOTDOWN 15
#    endif
/* Data Asynchronous Memory Error */
#    ifndef _K1_RM_INT_LINE_DAME
#      define _K1_RM_INT_LINE_DAME 16
#    endif
/* Cache Line Invalidation */
#    ifndef _K1_RM_INT_LINE_CLI
#      define _K1_RM_INT_LINE_CLI 17
#    endif

#    ifndef _K1_INT_GIC_BASE
#      define _K1_INT_GIC_BASE (_K1_RM_INT_GIC_BASE)
#    endif
#    ifndef _K1_INT_GIC0
#      define _K1_INT_GIC0 _K1_INT_GIC_BASE
#    endif
#    ifndef _K1_INT_GIC1
#      define _K1_INT_GIC1 (_K1_INT_GIC_BASE + 1)
#    endif
#    ifndef _K1_INT_GIC2
#      define _K1_INT_GIC2 (_K1_INT_GIC_BASE + 2)
#    endif
#    ifndef _K1_INT_GIC3
#      define _K1_INT_GIC3 (_K1_INT_GIC_BASE + 3)
#    endif

#    ifndef _K1_MAX_INT_NUMBER
#      define _K1_MAX_INT_NUMBER 32
#    endif

#  ifndef __ASSEMBLER__

/**
 * \fn void __k1_interrupt_priorities_equal(void)
 * \brief Set all interrupt lines to the same priority
 */
  extern void __k1_interrupt_priorities_equal(void);

/**
 * \fn void __k1_interrupt_level_set(uint32_t level)
 * \brief Sets the current level of priority.
 * \param level new level of priority
 */

extern void __k1_interrupt_level_set(uint32_t level);

/**
 * \fn void __k1_interrupt_enable(void)
 * \brief Enable interrupts
 */
extern void __k1_interrupt_enable(void);

/**
 * \fn void __k1_interrupt_disable(void)
 * \brief Disable interrupts
 */
extern void __k1_interrupt_disable(void);

/**
 * \fn void __k1_interrupt_init(void)
 * \brief Enable interrupts and set them to equal priority
 */
extern void __k1_interrupt_init(void);

/**
 * \fn void __k1_interrupt_enable_num(unsigned int x)
 * \brief Enable an interrupt line
 * \param x Interrupt number
 */
extern void __k1_interrupt_enable_num(unsigned int x);

/**
 * \fn void __k1_interrupt_set_priority(unsigned int num, uint8_t prio)
 * \brief Set interrupt line to given priority
 * \param num Interrupt number
 * \param prio Priority number
 */
extern void __k1_interrupt_set_priority(unsigned int num, uint8_t prio);

/**
 * \fn void __k1_interrupt_configure_dame(void)
 * \brief Configure DAME interrupt : enable it + set its priority to 15
 */
extern void __k1_interrupt_configure_dame(void);

#endif /* __ASSEMBLER__ */

/**
 * APIC interface
 */

/* GIC defines */
#define NB_APIC_GIC_INTERRUPT_GROUP 18
#define NB_APIC_GIC_INTERRUPT_PER_GROUP 4
#define NB_APIC_GIC_INTERRUPT (NB_APIC_GIC_INTERRUPT_GROUP*NB_APIC_GIC_INTERRUPT_PER_GROUP)

#define NB_APIC_GIC_INTERRUPT_SOURCE 157
#define NB_APIC_GIC_INTERRUPT_STATUS 3

/* Mailbox defines */
#define NB_APIC_MAILBOX_GROUP 16
#define NB_APIC_MAILBOX_PER_GROUP 8
#define NB_APIC_MAILBOX (NB_APIC_MAILBOX_GROUP*NB_APIC_MAILBOX_PER_GROUP)

#  ifndef __ASSEMBLER__

// Typedef
typedef enum {
  NO_TRIG   = 0,
  DOORBELL  = 1,
  MATCH     = 2,
  BARRIER   = 3,
  THRESHOLD = 4

} apic_mailbox_trig_e;

typedef enum {

  WRITE = 0,
  OR    = 1,
  ADD   = 2

} apic_mailbox_ifunct_e;

extern void __apic_gic_init(void);
extern void __apic_mailbox_init(void);

#endif /* __ASSEMBLER__ */

/**
 * L2 cache interface
 */

/* L2 cache defines */
#define NB_TAGS           8192
#define NB_SMEM_READERS   8192

#define L2_TAG_TAG_IDX         0
#define L2_TAG_UREFILL_IDX     27
#define L2_TAG_ATALLOW_IDX     28
#define L2_TAG_WALLOW_IDX      29
#define L2_TAG_VALID_IDX       30
#define L2_TAG_RDR_CLR_IDX     32
#define L2_TAG_VAL_CLR_IDX     40
#define L2_TAG_DRT_CLR_IDX     48

#define PWR_GLOB_UEN_IDX               0
#define PWR_GLOB_PEN_IDX               1
#define PWR_GLOB_CACHE_EN_IDX          2
#define PWR_GLOB_CACHE_CONFIG_IDX      3

#  ifndef __ASSEMBLER__

extern void __l2_init_metadata(void);

#endif /* __ASSEMBLER__ */

/**
 * Power controller interface
 */

#  ifndef __ASSEMBLER__

/**
 * \fn void __k1_set_pwr_pen_uen(void)
 * \brief Set PEN and UEN bit in the local power_controller
 */
extern void __k1_set_pwr_pen_uen(void);

/**
 * \fn void __k1_set_pwc_reset_on_wup(int cpuid)
 * \brief Set the reset_on_wakeup bit associated to PE cpuid in the local power_controller
 * \param cpuid PE id
 */
extern void __k1_clear_pwc_reset_on_wup(int cpuid);

/**
 * \fn void __k1_set_pwc_wup(int cpuid)
 * \brief Set the wup bit corresponding to PE cpuid in the local power_controller => wup the corresponding PE
 * \param cpuid PE id
 */
extern void __k1_set_pwc_wup(int cpuid);

/**
 * \fn void __k1_clear_pwc_wup(int cpuid)
 * \brief Clear the wup bit corresponding to PE cpuid in the local power_controller
 * \param cpuid PE id
 */
extern void __k1_clear_pwc_wup(int cpuid);

/**
 * \fn void __k1_pwc_init(void)
 * \brief Initializes basic power_controller features
 */
extern void __k1_pwc_init(void);

/**
 * \fn void __k1_cluster_poweroff(void)
 * \brief Power off cluster
 */
extern void __k1_cluster_poweroff(void);

#endif /* __ASSEMBLER__ */

/**
 * IO read/write interface
 */

#  ifndef __ASSEMBLER__

/*
 * I/O Write
 */

/**
 * \fn uint64_t __k1_io_write64(void *addr, uint64_t val)
 * \brief Write 64 bits
 * \param addr Pointer to the adress where data will be written
 * \param val Data to write
 */
extern void __k1_io_write64(void *addr, uint64_t val);

#endif /* __ASSEMBLER__ */

#endif /* _BSP_H */
