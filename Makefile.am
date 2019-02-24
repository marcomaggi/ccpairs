## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CPPFLAGS		= -I$(srcdir)/src
AM_CFLAGS		= $(MMUX_CFLAGS)

## --------------------------------------------------------------------

nodist_pkgconfig_DATA	= meta/scripts/ccpairs.pc


#### documentation

AM_MAKEINFOFLAGS	= --no-split
AM_MAKEINFOHTMLFLAGS	= --split=node -c WORDS_IN_PAGE=0 \
	-c PRE_BODY_CLOSE="<p>This document describes version <tt>$(PACKAGE_VERSION)</tt> of <em>$(PACKAGE_NAME)</em>.</p>"

info_TEXINFOS		= doc/ccpairs.texi
doc_ccpairs_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi


#### libraries

ccpairs_CURRENT		= @ccpairs_VERSION_INTERFACE_CURRENT@
ccpairs_REVISION	= @ccpairs_VERSION_INTERFACE_REVISION@
ccpairs_AGE		= @ccpairs_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccpairs.h

lib_LTLIBRARIES		= libccpairs.la
libccpairs_la_CPPFLAGS	= $(AM_CPPFLAGS)
libccpairs_la_CFLAGS	= $(AM_CPPFLAGS) $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS)
libccpairs_la_LDFLAGS	= -version-info $(ccpairs_CURRENT):$(ccpairs_REVISION):$(ccpairs_AGE) \
			  $(AM_LDFLAGS) $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCSTRUCTS_LIBS)
libccpairs_la_SOURCES	= \
	src/ccpairs.h				\
	src/ccpairs-internals.h			\
	src/ccpairs-version.c			\
	src/ccpairs-init.c			\
	src/ccpairs-conditions.c		\
	src/ccpairs-exception-handlers.c	\
	src/ccpairs-memory.c			\
	src/ccpairs-constructors.c		\
	src/ccpairs-inspection.c		\
	src/ccpairs-accessors.c			\
	src/ccpairs-mapping.c


#### tests

check_PROGRAMS	= \
	tests/version		\
	tests/cons		\
	tests/inspection	\
	tests/accessors		\
	tests/constructors	\
	tests/mapping

if MMUX_TESTING_ENABLED
TESTS				= $(check_PROGRAMS)
endif

ccpairs_tests_cppflags		= $(AM_CPPFLAGS)
ccpairs_tests_cflags		= $(AM_CFLAGS) $(CCEXCEPTIONS_FLAGS) $(CCMEMORY_CFLAGS) $(CCSTRUCTS_CFLAGS) $(CCTESTS_CFLAGS)
ccpairs_tests_ldadd		= $(AM_LDFLAGS) libccpairs.la $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_version_CFLAGS		= $(ccpairs_tests_cflags)
tests_version_LDADD		= $(ccpairs_tests_ldadd)

tests_cons_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_cons_CFLAGS		= $(ccpairs_tests_cflags)
tests_cons_LDADD		= $(ccpairs_tests_ldadd)

tests_inspection_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_inspection_CFLAGS		= $(ccpairs_tests_cflags)
tests_inspection_LDADD		= $(ccpairs_tests_ldadd)

tests_accessors_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_accessors_CFLAGS		= $(ccpairs_tests_cflags)
tests_accessors_LDADD		= $(ccpairs_tests_ldadd)

tests_constructors_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_constructors_CFLAGS	= $(ccpairs_tests_cflags)
tests_constructors_LDADD	= $(ccpairs_tests_ldadd)

tests_mapping_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_mapping_CFLAGS		= $(ccpairs_tests_cflags)
tests_mapping_LDADD		= $(ccpairs_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done


#### common rules

include $(top_srcdir)/meta/automake/mmux-makefile-rules

### end of file
