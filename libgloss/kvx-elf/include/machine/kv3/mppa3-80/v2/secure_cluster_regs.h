/*
 * secure_cluster_regs.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2023.
 */

#ifndef _INCLUDED_V2_SECURE_CLUSTER_REGS_H_
#define _INCLUDED_V2_SECURE_CLUSTER_REGS_H_

#ifndef __ASSEMBLER__

#include "machine/devices/secure_cluster_regs.coolidge-v2.dev"

#define MPPA_SECURE_CLUSTER_REGS_LOCAL__ADDR  0xCC2000
__attribute__ ((__unused__))
static volatile mppa_secure_cluster_regs_t *mppa_secure_cluster_regs_local =
    (mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_LOCAL__ADDR);

#define MPPA_SECURE_CLUSTER_REGS_0__ADDR  0x1CC2000
#define MPPA_SECURE_CLUSTER_REGS_1__ADDR  0x2CC2000
#define MPPA_SECURE_CLUSTER_REGS_2__ADDR  0x3CC2000
#define MPPA_SECURE_CLUSTER_REGS_3__ADDR  0x4CC2000
#define MPPA_SECURE_CLUSTER_REGS_4__ADDR  0x5CC2000
#define MPPA_SECURE_CLUSTER_REGS_COUNT  5

static volatile mppa_secure_cluster_regs_t *const mppa_secure_cluster_regs[MPPA_SECURE_CLUSTER_REGS_COUNT] = {
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_0__ADDR),
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_1__ADDR),
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_2__ADDR),
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_3__ADDR),
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_4__ADDR),
};

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V2_SECURE_CLUSTER_REGS_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
