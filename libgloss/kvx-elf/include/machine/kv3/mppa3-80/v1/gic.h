/*
 * gic.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2022.
 */

#ifndef _INCLUDED_V1_GIC_H_
#define _INCLUDED_V1_GIC_H_

#ifndef __ASSEMBLER__

#include "machine/devices/gic.coolidge-v1.dev"

#define MPPA_GIC_LOCAL__ADDR  0xA20000
__attribute__ ((__unused__))
static volatile mppa_gic_t *mppa_gic_local = (mppa_gic_t *) (MPPA_GIC_LOCAL__ADDR);

#define MPPA_SECURE_APIC_GIC_0__ADDR  0xD60000
#define MPPA_SECURE_APIC_GIC_COUNT  1

static volatile mppa_gic_t *const mppa_secure_apic_gic[MPPA_SECURE_APIC_GIC_COUNT] = {
	(mppa_gic_t *) (MPPA_SECURE_APIC_GIC_0__ADDR),
};

#define MPPA_GIC_0__ADDR  0x1A20000
#define MPPA_GIC_1__ADDR  0x2A20000
#define MPPA_GIC_2__ADDR  0x3A20000
#define MPPA_GIC_3__ADDR  0x4A20000
#define MPPA_GIC_4__ADDR  0x5A20000
#define MPPA_GIC_COUNT  5

static volatile mppa_gic_t *const mppa_gic[MPPA_GIC_COUNT] = {
	(mppa_gic_t *) (MPPA_GIC_0__ADDR),
	(mppa_gic_t *) (MPPA_GIC_1__ADDR),
	(mppa_gic_t *) (MPPA_GIC_2__ADDR),
	(mppa_gic_t *) (MPPA_GIC_3__ADDR),
	(mppa_gic_t *) (MPPA_GIC_4__ADDR),
};

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V1_GIC_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
