/*
 * device_inttype.h
 * Automatically generated from registers definition files. Do not edit
 * Copyright (c) Kalray 2020.
 */

#ifndef _INCLUDED_DEVICES_DEVICE_INTTYPE_H_
#define _INCLUDED_DEVICES_DEVICE_INTTYPE_H_

/*
 * Map __u?int.* types to either typedef(s) or hal core types
 */
#ifdef _KVX_COMMON_TYPE
#define mppa_int8    __kvx_int8_t
#define mppa_uint8   __kvx_uint8_t
#define mppa_int16   __kvx_int16_t
#define mppa_uint16  __kvx_uint16_t
#define mppa_int32   __kvx_int32_t
#define mppa_uint32  __kvx_uint32_t
#define mppa_intptr  __kvx_intptr_t
#define mppa_uintptr __kvx_uintptr_t
#define mppa_int64   __kvx_int64_t
#define mppa_uint64  __kvx_uint64_t
#else
#ifndef __DEVICE_INTTYPE
#define __DEVICE_INTTYPE
typedef signed char        mppa_int8;
typedef unsigned char      mppa_uint8;
typedef signed short       mppa_int16;
typedef unsigned short     mppa_uint16;
typedef signed int         mppa_int32;
typedef unsigned int       mppa_uint32;
typedef signed int         mppa_intptr;
typedef unsigned int       mppa_uintptr;
typedef signed long long   mppa_int64;
typedef unsigned long long mppa_uint64;
#endif
#endif

#endif // _INCLUDED_DEVICES_DEVICE_INTTYPE_H_

/* -*- Mode: C; c-basic-offset: 2 -*- */
/* vim:set ft=c sw=2 cindent: */
