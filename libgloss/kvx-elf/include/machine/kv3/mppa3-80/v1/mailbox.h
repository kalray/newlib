/*
 * mailbox.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2024.
 */

#ifndef _INCLUDED_V1_MAILBOX_H_
#define _INCLUDED_V1_MAILBOX_H_

#ifndef __ASSEMBLER__

#include "machine/devices/mailbox.coolidge-v1.dev"

#define MPPA_MAILBOX_LOCAL__ADDR  0xA00000
__attribute__ ((__unused__))
static volatile mppa_mailbox_t *mppa_mailbox_local = (mppa_mailbox_t *) (MPPA_MAILBOX_LOCAL__ADDR);

#define MPPA_SECURE_APIC_MAILBOX_0__ADDR  0xD40000
#define MPPA_SECURE_APIC_MAILBOX_COUNT  1

static volatile mppa_mailbox_t *const mppa_secure_apic_mailbox[MPPA_SECURE_APIC_MAILBOX_COUNT] = {
	(mppa_mailbox_t *) (MPPA_SECURE_APIC_MAILBOX_0__ADDR),
};

#define MPPA_MAILBOX_0__ADDR  0x1A00000
#define MPPA_MAILBOX_1__ADDR  0x2A00000
#define MPPA_MAILBOX_2__ADDR  0x3A00000
#define MPPA_MAILBOX_3__ADDR  0x4A00000
#define MPPA_MAILBOX_4__ADDR  0x5A00000
#define MPPA_MAILBOX_COUNT  5

static volatile mppa_mailbox_t *const mppa_mailbox[MPPA_MAILBOX_COUNT] = {
	(mppa_mailbox_t *) (MPPA_MAILBOX_0__ADDR),
	(mppa_mailbox_t *) (MPPA_MAILBOX_1__ADDR),
	(mppa_mailbox_t *) (MPPA_MAILBOX_2__ADDR),
	(mppa_mailbox_t *) (MPPA_MAILBOX_3__ADDR),
	(mppa_mailbox_t *) (MPPA_MAILBOX_4__ADDR),
};

#endif				/* __ASSEMBLER__ */

#endif				// _INCLUDED_V1_MAILBOX_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
