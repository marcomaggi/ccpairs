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

#ifndef CCPAIR_H
#define CCPAIR_H 1


/** --------------------------------------------------------------------
 ** Preliminary definitions.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* The  macro  CCPAIR_UNUSED  indicates  that a  function,  function
   argument or variable may potentially be unused. Usage examples:

   static int unused_function (char arg) CCPAIR_UNUSED;
   int foo (char unused_argument CCPAIR_UNUSED);
   int unused_variable CCPAIR_UNUSED;
*/
#ifdef __GNUC__
#  define CCPAIR_UNUSED		__attribute__((unused))
#else
#  define CCPAIR_UNUSED		/* empty */
#endif

#ifndef __GNUC__
#  define __attribute__(...)	/* empty */
#endif

/* I found  the following chunk on  the Net.  (Marco Maggi;  Sun Feb 26,
   2012) */
#if defined _WIN32 || defined __CYGWIN__
#  ifdef BUILDING_DLL
#    ifdef __GNUC__
#      define ccpair_decl		__attribute__((dllexport)) extern
#    else
#      define ccpair_decl		__declspec(dllexport) extern
#    endif
#  else
#    ifdef __GNUC__
#      define ccpair_decl		__attribute__((dllimport)) extern
#    else
#      define ccpair_decl		__declspec(dllimport) extern
#    endif
#  endif
#  define ccpair_private_decl	extern
#else
#  if __GNUC__ >= 4
#    define ccpair_decl		__attribute__((visibility ("default"))) extern
#    define ccpair_private_decl	__attribute__((visibility ("hidden")))  extern
#  else
#    define ccpair_decl		extern
#    define ccpair_private_decl	extern
#  endif
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <stdint.h>
#include <stdbool.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccpair_decl char const *ccpair_version_string			(void);
ccpair_decl int		ccpair_version_interface_current	(void);
ccpair_decl int		ccpair_version_interface_revision	(void);
ccpair_decl int		ccpair_version_interface_age		(void);


/** --------------------------------------------------------------------
 ** Pair structure.
 ** ----------------------------------------------------------------- */

typedef struct ccpair_stru_t	ccpair_stru_t;
typedef ccpair_stru_t *		ccpair_t;

struct ccpair_stru_t {
  uintptr_t	A;
  uintptr_t 	D;
};

__attribute__((always_inline,const))
static inline uintptr_t
ccpair_car (ccpair_t P)
{
  return P->A;
}

__attribute__((always_inline,const))
static inline ccpair_t
ccpair_cdr (ccpair_t P)
{
  return (ccpair_t)(P->D);
}

__attribute__((always_inline,const))
static inline uintptr_t
ccpair_cdr_value (ccpair_t P)
{
  return P->D;
}


/** --------------------------------------------------------------------
 ** Memory allocation.
 ** ----------------------------------------------------------------- */

typedef ccpair_t ccpair_malloc_fun_t (void);
typedef void     ccpair_free_fun_t   (ccpair_t P);

ccpair_decl void ccpair_memory_set_malloc_fun	(ccpair_malloc_fun_t * f);
ccpair_decl void ccpair_memory_set_free_fun	(ccpair_free_fun_t * f);

ccpair_decl ccpair_t ccpair_malloc (void);
ccpair_decl void     ccpair_free   (ccpair_t P);

__attribute__((always_inline,const))
static inline ccpair_t
ccpair_cons (uintptr_t A, ccpair_t D)
{
  ccpair_t	P = ccpair_malloc();
  P->A = A;
  P->D = (uintptr_t)D;
  return P;
}


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCPAIR_H */

/* end of file */
