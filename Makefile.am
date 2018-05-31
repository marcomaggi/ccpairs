## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS		= -I meta/autotools
AUTOMAKE_OPTIONS	= foreign
EXTRA_DIST		= INSTALL			\
			  meta/slackstuff/config.in	\
			  meta/slackware/slack-desc.in
dist_doc_DATA		= README COPYING
AM_CFLAGS		= -I$(srcdir)/src $(AX_CFLAGS)

## --------------------------------------------------------------------

EXTRA_DIST		+= meta/scripts/ccpairs.pc.in
pkgconfigdir		= $(libdir)/pkgconfig
nodist_pkgconfig_DATA	= meta/scripts/ccpairs.pc

## --------------------------------------------------------------------

AM_MAKEINFOFLAGS	= --no-split

info_TEXINFOS		= doc/ccpairs.texi
doc_ccpairs_TEXINFOS	= \
	doc/macros.texi		\
	doc/lgpl-3.0.texi	\
	doc/fdl-1.3.texi

#page
#### libraries

ccpairs_CURRENT		= @ccpairs_VERSION_INTERFACE_CURRENT@
ccpairs_REVISION	= @ccpairs_VERSION_INTERFACE_REVISION@
ccpairs_AGE		= @ccpairs_VERSION_INTERFACE_AGE@

include_HEADERS		= src/ccpairs.h

lib_LTLIBRARIES		= libccpairs.la
libccpairs_la_CPPFLAGS	= $(CCEXCEPTIONS_CFLAGS) $(CCMEMORY_CFLAGS)
libccpairs_la_LDFLAGS	= -version-info $(ccpairs_CURRENT):$(ccpairs_REVISION):$(ccpairs_AGE) \
			  $(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS)
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

#page
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

ccpairs_tests_cppflags		= -I$(srcdir)/src \
	$(CCEXCEPTIONS_FLAGS) $(CCMEMORY_CFLAGS) $(CCTESTS_CFLAGS)
ccpairs_tests_ldadd		= libccpairs.la \
	$(CCEXCEPTIONS_LIBS) $(CCMEMORY_LIBS) $(CCTESTS_LIBS)

## --------------------------------------------------------------------

tests_version_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_version_LDADD		= $(ccpairs_tests_ldadd)

tests_cons_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_cons_LDADD		= $(ccpairs_tests_ldadd)

tests_inspection_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_inspection_LDADD		= $(ccpairs_tests_ldadd)

tests_accessors_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_accessors_LDADD		= $(ccpairs_tests_ldadd)

tests_constructors_CPPFLAGS	= $(ccpairs_tests_cppflags)
tests_constructors_LDADD	= $(ccpairs_tests_ldadd)

tests_mapping_CPPFLAGS		= $(ccpairs_tests_cppflags)
tests_mapping_LDADD		= $(ccpairs_tests_ldadd)

## --------------------------------------------------------------------

installcheck-local: $(TESTS)
	@for f in $(TESTS); do $(builddir)/$$f; done

#page
#### testing under GDB

$(builddir)/.gdbinit:
	ln -sv "$(top_srcdir)/gdbinit" "$(builddir)/.gdbinit"

# This rule is meant to be used as:
#
#   $ make all gdb-test FILE=tests/inspection CFLAGS='-g'
#
# after having created an appropriate file "$(top_srcdir)/.gdbinit".
#
gdb-test: $(builddir)/.gdbinit
	libtool --mode=execute gdb $$FILE

#page
#### Static analysis with Clang's Static Analyzer
#
# See the documentation for the command line tool at:
#
#    <http://clang-analyzer.llvm.org/scan-build.html>
#
# To run the tool we must do:
#
#    $ make clean
#    $ make clang-static-analysis
#
# The  program  "scan-build"  works  by  overriding  the  CC  and  CXX
# environment variables.  Automake defines CXX as:
#
#    CXX = g++ -std=c++11
#
# so we override CXXFLAGS to include the language specification.
#

.PHONY: clang-static-analysis

clang-static-analysis:
	scan-build make CXXFLAGS='-std=c++11'

### end of file
