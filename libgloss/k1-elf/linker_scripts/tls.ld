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

  /* TLS support */
  .tdata   ALIGN(8):
  {
    _tdata_start = ABSOLUTE(.);
    *(.tdata)
    *(.tdata.*)
    . = ALIGN(8);
    _tdata_end = ABSOLUTE(.);
  }  > REGION_TLS
  _tdata_size = _tdata_end - _tdata_start;

  .tbss   ALIGN(8):
  {
    _tbss_start = ABSOLUTE(.);
    *(.tbss)
    *(.tbss.*)
    *(.tcommon)
    *(.gnu.linkonce.tb.*)
    . = ALIGN(8);
    _tbss_end = ABSOLUTE(.);
  }  > REGION_TLS
  _tbss_size = _tbss_end - _tbss_start;

  /* DO NOT USE THIS IN C CODE.  */
  __tls_size = _tbss_end - _tdata_start;

  /* Reserve space for the TLS data of the 17 processors (1 RM + 16 PEs).
   * '.tdata' must not be modified in order to keep a reference version during the programme execution,
   * thus we need to reserve 17 slots in order to copy the .data in it.
   * '.tbss' won't get reserved by the linker, thus we need to reserve 17 slots.
   *
   * Note that the bellow is just a space reservation, it says nothing about
   * the layout of the data in memory. We compute separately the tbss and
   * tdata space, but the runtime layout will intermingle the slots:
   *
   *    <_tdata_start>
   *	.tdata[PE0]
   *	.tbss[PE0]
   *	.tdata[PE1]
   *	.tbss[PE1]
   *	....
   *	.tdata[PE15]
   *	.tbss[PE15]
   *	.tdata[RM]
   *	.tbss[RM]
   *	<_end>
   */

   .tls_pe0 ALIGN(8):
   {
    _tls_pe0_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE0 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe0_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe1 ALIGN(8):
   {
    _tls_pe1_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE1 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe1_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe2 ALIGN(8):
   {
    _tls_pe2_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE2 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe2_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe3 ALIGN(8):
   {
    _tls_pe3_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE3 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe3_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe4 ALIGN(8):
   {
    _tls_pe4_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE4 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe4_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe5 ALIGN(8):
   {
    _tls_pe5_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE5 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe5_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe6 ALIGN(8):
   {
    _tls_pe6_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE6 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe6_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe7 ALIGN(8):
   {
    _tls_pe7_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE7 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe7_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe8 ALIGN(8):
   {
    _tls_pe8_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE8 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe8_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe9 ALIGN(8):
   {
    _tls_pe9_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE9 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe9_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe10 ALIGN(8):
   {
    _tls_pe10_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE10 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe10_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe11 ALIGN(8):
   {
    _tls_pe11_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE11 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe11_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe12 ALIGN(8):
   {
    _tls_pe12_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE12 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe12_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe13 ALIGN(8):
   {
    _tls_pe13_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE13 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe13_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe14 ALIGN(8):
   {
    _tls_pe14_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE14 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe14_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_pe15 ALIGN(8):
   {
    _tls_pe15_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for PE15 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_pe15_end = ABSOLUTE(.);
   } > REGION_TLS

   .tls_rm ALIGN(8):
   {
    _tls_rm_start = ABSOLUTE(.);
   /* Reserve room for .tdata and .tbss for RM0 */
    . += __tls_size;
    . = ALIGN(8);
    _tls_rm_end = ABSOLUTE(.);
    _end = ABSOLUTE(.);
  } > REGION_TLS
