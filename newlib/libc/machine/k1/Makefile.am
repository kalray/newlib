## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = foreign

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

# /*  _____________________ */
# /* < removed optimized memcpy > */
# /*  --------------------- */
# /*         \   ^__^ */
# /*          \  (oo)\_______ */
# /*             (__)\       )\/\ */
# /*                 ||----w | */
# /*                 ||     || */
# /*  ____  _     _____    _    ____  _____  //\    _____ _____  __ */
# /* |  _ \| |   | ____|  / \  / ___|| ____||/_\|  |  ___|_ _\ \/ / */
# /* | |_) | |   |  _|   / _ \ \___ \|  _|   /_\   | |_   | | \  /  */
# /* |  __/| |___| |___ / ___ \ ___) | |___ / _ \  |  _|  | | /  \  */
# /* |_|   |_____|_____/_/   \_\____/|_____/_/ \_\ |_|   |___/_/\_\ */

lib_a_SOURCES = setjmp.S memset.c
lib_a_CCASFLAGS=$(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS) -fstack-check=no

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
