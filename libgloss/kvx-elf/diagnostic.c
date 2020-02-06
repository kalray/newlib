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

#include <kv3/assert.h>
#include <kv3/registers.h>
#include <kv3/diagnostic.h>

int __kvx_counter_control(void)
{
  return __builtin_kvx_get(KVX_SFR_PMC);
}

uint64_t __kvx_counter_num(unsigned int n)
{

  __kvx_assert(n < _KVX_PM_NB);

  switch (n) {
  case _KVX_PM0:
    return __builtin_kvx_get(KVX_SFR_PM0);
  case _KVX_PM1:
    return __builtin_kvx_get(KVX_SFR_PM1);
  case _KVX_PM2:
    return __builtin_kvx_get(KVX_SFR_PM2);
  case _KVX_PM3:
    return __builtin_kvx_get(KVX_SFR_PM3);
  default:
    break;
  }
  return 0;
}

void __kvx_counter_start(unsigned int counter_num, int metric)
{

  uint64_t pmc_metric_wfx = 0;

  __kvx_assert(counter_num < _KVX_PM_NB);
  switch (counter_num) {
  case _KVX_PM0:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM0C, metric);
    break;
  case _KVX_PM1:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM1C, metric);
    break;
  case _KVX_PM2:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM2C, metric);
    break;
  case _KVX_PM3:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM3C, metric);
    break;
  default:
    break;
  }
  __builtin_kvx_wfxl(KVX_SFR_PMC, pmc_metric_wfx);
}

void __kvx_counter_stop(unsigned int counter_num)
{

  uint64_t pmc_metric_wfx = 0;

  __kvx_assert(counter_num < _KVX_PM_NB);
  switch (counter_num) {
  case _KVX_PM0:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM0C, _KVX_PM_SE);
    break;
  case _KVX_PM1:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM1C, _KVX_PM_SE);
    break;
  case _KVX_PM2:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM2C, _KVX_PM_SE);
    break;
  case _KVX_PM3:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM3C, _KVX_PM_SE);
    break;
  default:
    break;
  }
  __builtin_kvx_wfxl(KVX_SFR_PMC, pmc_metric_wfx);
}

void __kvx_counter_reset(unsigned int counter_num)
{

  uint64_t pmc_metric_wfx = 0;

  __kvx_assert(counter_num < _KVX_PM_NB);
  switch (counter_num) {
  case _KVX_PM0:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM0C, _KVX_PM_RE);
    break;
  case _KVX_PM1:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM1C, _KVX_PM_RE);
    break;
  case _KVX_PM2:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM2C, _KVX_PM_RE);
    break;
  case _KVX_PM3:
    pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM3C, _KVX_PM_RE);
    break;
  default:
    break;
  }
  __builtin_kvx_wfxl(KVX_SFR_PMC, pmc_metric_wfx);
}



void __kvx_counter_stop_all(void)
{
  uint64_t pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM0C, _KVX_PM_SE) |
    KVX_SFR_WFXL_VALUE(PMC_PM1C, _KVX_PM_SE) |
    KVX_SFR_WFXL_VALUE(PMC_PM2C, _KVX_PM_SE) |
    KVX_SFR_WFXL_VALUE(PMC_PM3C, _KVX_PM_SE);

  __builtin_kvx_wfxl(KVX_SFR_PMC, pmc_metric_wfx);
}


void __kvx_counter_reset_all(void)
{
  uint64_t pmc_metric_wfx = KVX_SFR_WFXL_VALUE(PMC_PM0C, _KVX_PM_RE) |
    KVX_SFR_WFXL_VALUE(PMC_PM1C, _KVX_PM_RE) |
    KVX_SFR_WFXL_VALUE(PMC_PM2C, _KVX_PM_RE) |
    KVX_SFR_WFXL_VALUE(PMC_PM3C, _KVX_PM_RE);

  __builtin_kvx_wfxl(KVX_SFR_PMC, pmc_metric_wfx);
}
