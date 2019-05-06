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

#ifndef _K1_DIAGNOSTIC_H
#  define _K1_DIAGNOSTIC_H

#include <stdint.h>

/*
 * Metrics, more details can be found in the architecture reference manual
 */
#define _K1_PM_PCC 0     //  Processor Clock CycleSAT                            ,  None
#define _K1_PM_ICC 1     //  Idle Clock Cycle                                    ,  None
#define _K1_PM_EBE 2     //  Executed Bundle Event                               ,  PC
#define _K1_PM_ENIE 3    //  Executed N Instructions Event                       ,  PC
#define _K1_PM_ENSE 4    //  Executed N Syllables Event                          ,  PC
#define _K1_PM_ICHE 5    //  I$ Hit Event                                        ,  A
#define _K1_PM_ICME 6    //  I$ Miss Event                                       ,  A
#define _K1_PM_ICMABE 7  //  I$ Memory Accesses Burst Event                      ,  A
#define _K1_PM_MNGIC 8   //  Memory Not Granting Instruction cache access Cycle  ,  None
#define _K1_PM_MIMHE 9   //  MMU Instruction Micro-tlb Hit Event                 ,  A
#define _K1_PM_MIMME 10  //  MMU Instruction Micro-tlb Miss Event                ,  A
#define _K1_PM_IATSC 11  //  Instruction Address Translation Stall Cycle         ,  None
#define _K1_PM_FE 12     //  Fetch Event                                         ,  None
#define _K1_PM_PBSC 13   //  Prefetch Buffer Starvation Cycle                    ,  None
#define _K1_PM_PNVC 14   //  Pipeline No Valid Cycle                             ,  None
#define _K1_PM_PSC 15    //  Pipeline Starvation Cycle                           ,  None
#define _K1_PM_TADBE 16  //  Taken Applicative Direct Branch Event               ,  PC
#define _K1_PM_TABE 17   //  Taken Applicative Branch Event                      ,  PC
#define _K1_PM_TBE 18    //  Taken Branch Event                                  ,  None
#define _K1_PM_MDMHE 19  //  MMU Data  Micro-tlb Hit Event                       ,  PC
#define _K1_PM_MDMME 20  //  MMU Data Micro-tlb Miss Event                       ,  PC
#define _K1_PM_DATSC 21  //  Data Address Translation Stall Cycle                ,  None
#define _K1_PM_DCLHE 22  //  D$ Load Hit Event                                   ,  PC
#define _K1_PM_DCHE 23   //  D$ Hit Event                                        ,  PC
#define _K1_PM_DCLME 24  //  D$ Load Miss Event                                  ,  PC
#define _K1_PM_DCME 25   //  D$ Miss Event                                       ,  PC
#define _K1_PM_DARSC 26  //  Data Access Related Stall Cycle                     ,  None
#define _K1_PM_LDSC 27   //  Load Dependency Stall Cycle                         ,  None
#define _K1_PM_DCNGC 28  //  Data Cache Not Granting Cycle                       ,  None
#define _K1_PM_DMAE 29   //  Data Misaligned Access Event                        ,  PC
#define _K1_PM_LCFSC 30  //  Load Cam Full Stall Cycle                           ,  None
#define _K1_PM_MNGDC 31  //  Memory Not Granting Data cache access Cycle         ,  None
#define _K1_PM_MACC 32   //  Memory Accesses Conflict Cycle                      ,  None
#define _K1_PM_TACC 33   //  TLB Accesses Conflict Cycle                         ,  None
#define _K1_PM_IWC 34    //  Idle Wait Cycle                                     ,  None
#define _K1_PM_WISC 35   //  Wait Instruction Stall Cycle                        ,  None
#define _K1_PM_SISC 36   //  Synchronization Instruction Stall Cycle             ,  None
#define _K1_PM_DDSC 37   //  Data Dependency Stall Cycle                         ,  None
#define _K1_PM_SC 38     //  Stall Cycle                                         ,  None
#define _K1_PM_ELE 39    //  Executed Load Event                                 ,  PC
#define _K1_PM_ELNBE 40  //  Executed Load N Bytes Event                         ,  PC
#define _K1_PM_ELUE 41   //  Executed Load Uncached Event                        ,  PC
#define _K1_PM_ELUNBE 42 //  Executed Load Uncached N Bytes Event                ,  PC
#define _K1_PM_ESE 43    //  Executed Store Event                                ,  PC
#define _K1_PM_ESNBE 44  //  Executed Store N Bytes Event                        ,  PC
#define _K1_PM_EAE 45    //  Executed Atomics Event                              ,  PC
#define _K1_PM_CIRE 46   //  Coherency Invalidation Request Event                ,  A
#define _K1_PM_CIE 47    //  Coherency Invalidation Event                        ,  A
#define _K1_PM_SE 48     //  Stop Event                                          ,  None
#define _K1_PM_RE 49     //  Reset Event                                         ,  None
#define _K1_PM_FSC 50    //  Fetch Stall Cycle                                   ,  None


#define _K1_PM0 0
#define _K1_PM1 1
#define _K1_PM2 2
#define _K1_PM3 3

#define _K1_PM_NB 4


/**
 * \fn static inline int __k1_counter_control(void)
 * \brief Get value of counter control register
 */
extern int __k1_counter_control(void);

/*
 * New scheme routines
 */

/**
 * \fn static inline uint32_t __k1_counter_num(unsigned int n)
 * \brief Get value of counters
 * \param n Number of counter (0-3)
 * \return Content of counter
 */
extern uint64_t __k1_counter_num(unsigned int n);

/**
 * \fn static inline void __k1_counter_control(void)
 * \brief Enable performance counter for a specific metric
 * \param counter_num Number of counter (0-3)
 * \param metric specified metric
 */
extern void __k1_counter_start(unsigned int counter_num, int metric);

/**
 * \fn static inline void __k1_counter_stop(unsigned int counter_num)
 * \brief Stop counter n
 * \param counter_num Number of counter (0-3)
 */
extern void __k1_counter_stop(unsigned int counter_num);

/**
 * \fn static inline void __k1_counter_reset(unsigned int counter_num)
 * \brief Reset value of counter n
 * \param n Number of counter (0-3)
 */
extern void __k1_counter_reset(unsigned int counter_num);

/**
 * \fn static inline void __k1_counter_stop_all(void)
 * \brief Stop all counters
 */
extern void __k1_counter_stop_all(void);

/**
 * \fn static inline void __k1_counter_reset_all(unsigned int counter_num)
 * \brief Reset all counters
 */
extern void __k1_counter_reset_all(void);

#endif      /* _K1_DIAGNOSTIC_H */
