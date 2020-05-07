/*
 * trace.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2020.
 */

#ifndef _INCLUDED_CLUSTER_TRACE_H_
#define _INCLUDED_CLUSTER_TRACE_H_

#ifndef __ASSEMBLER__

#include "machine/devices/trace.coolidge.dev"

enum {
MPPA_TRACE_0__ADDR = 0x10100000,
};

#define MPPA_TRACE_COUNT  1

static volatile mppa_trace_t *const mppa_trace[MPPA_TRACE_COUNT] = {
(mppa_trace_t *)(MPPA_TRACE_0__ADDR),
};



#endif /* __ASSEMBLER__ */

#endif // _INCLUDED_CLUSTER_TRACE_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
