/*
 * secure_cluster_regs.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2022.
 */

#ifndef _INCLUDED_V1_SECURE_CLUSTER_REGS_H_
#define _INCLUDED_V1_SECURE_CLUSTER_REGS_H_

#ifndef __ASSEMBLER__

#include "machine/devices/secure_cluster_regs.coolidge-v1.dev"

enum {
	MPPA_SECURE_CLUSTER_REGS_0__ADDR = 0xCC2000,
};

#define MPPA_SECURE_CLUSTER_REGS_COUNT  1

static volatile mppa_secure_cluster_regs_t *const mppa_secure_cluster_regs[MPPA_SECURE_CLUSTER_REGS_COUNT] = {
	(mppa_secure_cluster_regs_t *) (MPPA_SECURE_CLUSTER_REGS_0__ADDR),
};

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V1_SECURE_CLUSTER_REGS_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
