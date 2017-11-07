/*
  Part of: CCPairs
  Contents: public header file
  Date: Thu Mar  1, 2012

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have received  a copy  of the  GNU General  Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCPAIRS_H
#define CCPAIRS_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCPAIRS_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCPAIRS_UNUSED;
   int foo (char unused_argument CCPAIRS_UNUSED);
   int unused_variable CCPAIRS_UNUSED;
*/
#ifdef __GNUC__
#  define CCPAIRS_UNUSED		__attribute__((unused))
#else
#  define CCPAIRS_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccpairs_decl		__attribute__((dllexport)) extern
#    else
#      define ccpairs_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define ccpairs_decl		__attribute__((dllimport)) extern
#    else
#      define ccpairs_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define ccpairs_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccpairs_decl		__attribute__((visibility ("default"))) extern
#    define ccpairs_private_decl	__attribute__((visibility ("hidden")))  extern
#  else
#    define ccpairs_decl		extern
#    define ccpairs_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#if 0

/* Enable everything GNU. */
#define _GNU_SOURCE		1

/* Enable latest POSIX features. */
#define _POSIX_C_SOURCE		200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> /* for offsetof() */
#include <setjmp.h>
#include <errno.h>
#include <unistd.h>

#endif


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccpairs_decl const char *	ccpairs_version_string		(void);
ccpairs_decl int		ccpairs_version_interface_current	(void);
ccpairs_decl int		ccpairs_version_interface_revision	(void);
ccpairs_decl int		ccpairs_version_interface_age	(void);


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCPAIRS_H */

/* end of file */
