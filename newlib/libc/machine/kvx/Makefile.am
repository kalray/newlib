## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = foreign

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS) -I$(newlib_basedir)/libc/search

AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = setjmp.S memset.S memcpy.S rpmatch.c arc4random.c arc4random_uniform.c hash_page.c
lib_a_CCASFLAGS=$(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
