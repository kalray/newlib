/*
 * l2_cache.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2021.
 */

#ifndef _INCLUDED_V1_L2_CACHE_H_
#define _INCLUDED_V1_L2_CACHE_H_

#ifndef __ASSEMBLER__

#include "machine/devices/l2_cache.coolidge-v1.dev"

enum {
	MPPA_L2_LOCAL__ADDR = 0x400000,
	MPPA_L2_CACHE_0__ADDR = 0x1400000,
	MPPA_L2_CACHE_1__ADDR = 0x2400000,
	MPPA_L2_CACHE_2__ADDR = 0x3400000,
	MPPA_L2_CACHE_3__ADDR = 0x4400000,
	MPPA_L2_CACHE_4__ADDR = 0x5400000,
};

#define MPPA_L2_CACHE_COUNT  5

static volatile mppa_l2_cache_t *const mppa_l2_cache[MPPA_L2_CACHE_COUNT] = {
	(mppa_l2_cache_t *) (MPPA_L2_CACHE_0__ADDR),
	(mppa_l2_cache_t *) (MPPA_L2_CACHE_1__ADDR),
	(mppa_l2_cache_t *) (MPPA_L2_CACHE_2__ADDR),
	(mppa_l2_cache_t *) (MPPA_L2_CACHE_3__ADDR),
	(mppa_l2_cache_t *) (MPPA_L2_CACHE_4__ADDR),
};

__attribute__ ((__unused__))
static volatile mppa_l2_cache_t *mppa_l2_local = (mppa_l2_cache_t *) (MPPA_L2_LOCAL__ADDR);

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V1_L2_CACHE_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
