## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = -I$(srcdir)/include $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = lock.c secure_getenv.c setgethostname.c getrusage.c basedirname.c timespec_get.c
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

# crt0.o come from libgloss

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/arpa; \
	for i in $(srcdir)/include/arpa/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/arpa/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/net; \
	for i in $(srcdir)/include/net/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/net/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/netinet; \
	for i in $(srcdir)/include/netinet/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/netinet/`basename $$i`; \
	done; \
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/netinet6; \
	for i in $(srcdir)/include/netinet6/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/netinet6/`basename $$i`; \
	done
	$(mkinstalldirs) $(DESTDIR)$(tooldir)/include/netpacket; \
	for i in $(srcdir)/include/netpacket/*.h; do \
	  $(INSTALL_DATA) $$i $(DESTDIR)$(tooldir)/include/netpacket/`basename $$i`; \
	done
