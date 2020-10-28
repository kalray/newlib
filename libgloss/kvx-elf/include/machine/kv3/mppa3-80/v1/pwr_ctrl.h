/*
 * pwr_ctrl.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2020.
 */

#ifndef _INCLUDED_V1_PWR_CTRL_H_
#define _INCLUDED_V1_PWR_CTRL_H_

#ifndef __ASSEMBLER__

#include "machine/devices/pwr_ctrl.coolidge-v1.dev"

enum {
	MPPA_PWR_CTRL_LOCAL__ADDR = 0xA40000,
	MPPA_PWR_CTRL_0__ADDR = 0x1A40000,
	MPPA_PWR_CTRL_1__ADDR = 0x2A40000,
	MPPA_PWR_CTRL_2__ADDR = 0x3A40000,
	MPPA_PWR_CTRL_3__ADDR = 0x4A40000,
	MPPA_PWR_CTRL_4__ADDR = 0x5A40000,
};

#define MPPA_PWR_CTRL_COUNT  5

static volatile mppa_pwr_ctrl_t *const mppa_pwr_ctrl[MPPA_PWR_CTRL_COUNT] = {
	(mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_0__ADDR),
	(mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_1__ADDR),
	(mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_2__ADDR),
	(mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_3__ADDR),
	(mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_4__ADDR),
};

__attribute__ ((__unused__))
static volatile mppa_pwr_ctrl_t *mppa_pwr_ctrl_local = (mppa_pwr_ctrl_t *) (MPPA_PWR_CTRL_LOCAL__ADDR);

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V1_PWR_CTRL_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
