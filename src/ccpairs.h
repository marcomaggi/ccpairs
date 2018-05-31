/*
  Part of: CCPairs
  Contents: public header file
  Date: Thu Mar  1, 2012

  Abstract

	This is the public header file for CCPairs.  It must be included
	in all the source files using the library's facilities.

  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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

/* The macro CCPAIRS_UNUSED indicates that a function, function argument
   or variable may potentially be unused. Usage examples:

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

#include <ccexceptions.h>
#include <ccmemory.h>
#include <stdint.h>
#include <stdbool.h>


/** --------------------------------------------------------------------
 ** Macros.
 ** ----------------------------------------------------------------- */

/* Pointer cast macro helper. */
#define CCPAIRS_PC(TYPE,X,Y)		TYPE * X = (TYPE *) (Y)


/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef size_t				ccpairs_idx_t;
typedef size_t				ccpairs_len_t;

typedef uintptr_t ccpairs_item_constructor_t (cce_location_t * L, ccpairs_idx_t idx);
typedef void      ccpairs_item_destructor_t  (uintptr_t item);


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccpairs_decl char const *ccpairs_version_string			(void);
ccpairs_decl int	ccpairs_version_interface_current	(void);
ccpairs_decl int	ccpairs_version_interface_revision	(void);
ccpairs_decl int	ccpairs_version_interface_age		(void);


/** --------------------------------------------------------------------
 ** Initialisation functions.
 ** ----------------------------------------------------------------- */

ccpairs_decl void ccpairs_library_init (void)
  __attribute__((__constructor__));


/** --------------------------------------------------------------------
 ** Exceptional-condition object-types.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_descriptor_base_t	ccpairs_descriptor_base_t;
typedef struct ccpairs_condition_base_t		ccpairs_condition_base_t;

struct ccpairs_descriptor_base_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_base_t {
  cce_condition_t	condition;
};

ccpairs_decl const ccpairs_descriptor_base_t * const ccpairs_descriptor_base;

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpairs_condition_is_base (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpairs_descriptor_base->descriptor));
}

/* ------------------------------------------------------------------ */

typedef struct ccpairs_descriptor_not_enough_items_t	ccpairs_descriptor_not_enough_items_t;
typedef struct ccpairs_condition_not_enough_items_t	ccpairs_condition_not_enough_items_t;

struct ccpairs_descriptor_not_enough_items_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_not_enough_items_t {
  ccpairs_condition_base_t	base;
};

ccpairs_decl const ccpairs_descriptor_not_enough_items_t * const ccpairs_descriptor_not_enough_items;

ccpairs_decl cce_condition_t const * ccpairs_condition_new_not_enough_items (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpairs_condition_is_not_enough_items (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpairs_descriptor_not_enough_items->descriptor));
}

/* ------------------------------------------------------------------ */

typedef struct ccpairs_descriptor_empty_list_t		ccpairs_descriptor_empty_list_t;
typedef struct ccpairs_condition_empty_list_t		ccpairs_condition_empty_list_t;

struct ccpairs_descriptor_empty_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_empty_list_t {
  ccpairs_condition_base_t	base;
};

ccpairs_decl const ccpairs_descriptor_empty_list_t * const ccpairs_descriptor_empty_list;

ccpairs_decl cce_condition_t const * ccpairs_condition_new_empty_list (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpairs_condition_is_empty_list (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpairs_descriptor_empty_list->descriptor));
}

/* ------------------------------------------------------------------ */

typedef struct ccpairs_descriptor_circular_list_t	ccpairs_descriptor_circular_list_t;
typedef struct ccpairs_condition_circular_list_t	ccpairs_condition_circular_list_t;

struct ccpairs_descriptor_circular_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_circular_list_t {
  ccpairs_condition_base_t	base;
};

ccpairs_decl const ccpairs_descriptor_circular_list_t * const ccpairs_descriptor_circular_list;

ccpairs_decl cce_condition_t const * ccpairs_condition_new_circular_list (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpairs_condition_is_circular_list (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpairs_descriptor_circular_list->descriptor));
}


/** --------------------------------------------------------------------
 ** Pair structure.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_stru_t		ccpairs_stru_t;
typedef ccpairs_stru_t *		ccpairs_t;

struct ccpairs_stru_t {
  uintptr_t	A;
  uintptr_t 	D;
};

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline uintptr_t
ccpairs_car (ccpairs_t P)
{
  return P->A;
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_cdr (ccpairs_t P)
{
  return (ccpairs_t)(P->D);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_car_pair (ccpairs_t P)
{
  return (ccpairs_t)(P->A);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline uintptr_t
ccpairs_cdr_value (ccpairs_t P)
{
  return P->D;
}


/** --------------------------------------------------------------------
 ** Memory allocation.
 ** ----------------------------------------------------------------- */

ccpairs_decl ccmem_allocator_t const * ccpairs_register_allocator (ccmem_allocator_t const * allocator)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccpairs_decl ccpairs_t	ccpairs_alloc (cce_location_t * L)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccpairs_decl void	ccpairs_free   (ccpairs_t P);

ccpairs_decl void	ccpairs_free_list (ccpairs_t P);


/** --------------------------------------------------------------------
 ** Constructors.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline ccpairs_t
ccpairs_cons (cce_location_t * L, uintptr_t A, ccpairs_t D)
{
  ccpairs_t	P = ccpairs_alloc(L);
  P->A = A;
  P->D = (uintptr_t)D;
  return P;
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_cons_improper (cce_location_t * L, uintptr_t A, uintptr_t D)
{
  return ccpairs_cons(L, A, (ccpairs_t)D);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_cons_node (cce_location_t * L, ccpairs_t A, ccpairs_t D)
{
  return ccpairs_cons(L, (uintptr_t)A, D);
}

/* ------------------------------------------------------------------ */

ccpairs_decl ccpairs_t ccpairs_list (cce_location_t * L, ccpairs_item_constructor_t * C, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Inspection.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__const__))
static inline bool
ccpairs_is_empty (ccpairs_t P)
{
  return (NULL == P)? true : false;
}

__attribute__((__always_inline__,__const__))
static inline bool
ccpairs_is_null (ccpairs_t P)
{
  return (NULL == P)? true : false;
}

ccpairs_decl ccpairs_len_t ccpairs_length (cce_location_t * L, ccpairs_t P)
  __attribute__((__nonnull__(1)));

__attribute__((__always_inline__,__pure__))
static inline bool
ccpairs_is_last (ccpairs_t P)
{
  return (P && (NULL == ccpairs_cdr(P)))? true : false;
}

ccpairs_decl bool ccpairs_is_circular (ccpairs_t P)
  __attribute__((__leaf__,__pure__));


/** --------------------------------------------------------------------
 ** Pair accessors.
 ** ----------------------------------------------------------------- */

ccpairs_decl ccpairs_t ccpairs_ref_pair (cce_location_t * L, ccpairs_t P, ccpairs_idx_t idx)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccpairs_decl ccpairs_t ccpairs_last_pair (cce_location_t * L, ccpairs_t P)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_first_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 0);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_second_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 1);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_third_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 2);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_fourth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 3);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_fifth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 4);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_sixth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 5);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_seventh_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 6);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_eighth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 7);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_nineth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 8);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_tenth_pair (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 9);
}


/** --------------------------------------------------------------------
 ** Item accessors.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_ref (cce_location_t * L, ccpairs_t P, ccpairs_idx_t const idx)
{
  return ccpairs_car(ccpairs_ref_pair(L, P, idx));
}

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline uintptr_t
ccpairs_last (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_car(ccpairs_last_pair(L, P));
}

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_first (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 0);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_second (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 1);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_third (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 2);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_fourth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 3);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_fifth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 4);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_sixth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 5);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_seventh (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 6);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_eighth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 7);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_nineth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 8);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpairs_tenth (cce_location_t * L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 9);
}


/** --------------------------------------------------------------------
 ** Mapping and folding functions.
 ** ----------------------------------------------------------------- */

typedef uintptr_t ccpairs_map_fun_t   (uintptr_t item);
typedef uintptr_t ccpairs_map_1_fun_t (uintptr_t item);
typedef uintptr_t ccpairs_map_2_fun_t (uintptr_t item1, uintptr_t item2);
typedef uintptr_t ccpairs_map_3_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3);
typedef uintptr_t ccpairs_map_4_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3, uintptr_t item4);
typedef uintptr_t ccpairs_map_5_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3, uintptr_t item4, uintptr_t item5);

/* ------------------------------------------------------------------ */

ccpairs_decl ccpairs_t ccpairs_map_1_forward (cce_location_t * L, ccpairs_map_1_fun_t * fun, ccpairs_t P1)
  __attribute__((__nonnull__(1)));

ccpairs_decl ccpairs_t ccpairs_map_2_forward (cce_location_t * L, ccpairs_map_2_fun_t * fun, ccpairs_t P1, ccpairs_t P2)
  __attribute__((__nonnull__(1)));

ccpairs_decl ccpairs_t ccpairs_map_3_forward (cce_location_t * L, ccpairs_map_3_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3)
  __attribute__((__nonnull__(1)));

ccpairs_decl ccpairs_t ccpairs_map_4_forward (cce_location_t * L, ccpairs_map_4_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4)
  __attribute__((__nonnull__(1)));

ccpairs_decl ccpairs_t ccpairs_map_5_forward (cce_location_t * L, ccpairs_map_5_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4, ccpairs_t P5)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_map (cce_location_t * L, ccpairs_map_fun_t * fun, ccpairs_t P)
{
  return ccpairs_map_1_forward(L, fun, P);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpairs_t
ccpairs_map_forward (cce_location_t * L, ccpairs_map_fun_t * fun, ccpairs_t P)
{
  return ccpairs_map_1_forward(L, fun, P);
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_pair_clean_handler_t	ccpairs_pair_clean_handler_t;
typedef struct ccpairs_pair_error_handler_t	ccpairs_pair_error_handler_t;

struct ccpairs_pair_clean_handler_t {
  cce_clean_handler_t	handler;
};

struct ccpairs_pair_error_handler_t {
  cce_error_handler_t	handler;
};

ccpairs_decl void ccpairs_init_pair_clean_handler (cce_location_t * L, ccpairs_pair_clean_handler_t * H, ccpairs_t P)
  __attribute__((__nonnull__(1,2,3)));

ccpairs_decl void ccpairs_init_pair_error_handler (cce_location_t * L, ccpairs_pair_error_handler_t * H, ccpairs_t P)
  __attribute__((__nonnull__(1,2,3)));

#define ccpairs_pair_handler_init(L,P_H,P)				\
  _Generic((P_H),							\
	   ccpairs_pair_error_handler_t *: ccpairs_init_pair_error_handler, \
	   ccpairs_pair_clean_handler_t *: ccpairs_init_pair_clean_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_list_clean_handler_t	ccpairs_list_clean_handler_t;
typedef struct ccpairs_list_error_handler_t	ccpairs_list_error_handler_t;

struct ccpairs_list_clean_handler_t {
  cce_clean_handler_t	handler;
};

struct ccpairs_list_error_handler_t {
  cce_error_handler_t	handler;
};

ccpairs_decl void ccpairs_init_list_clean_handler (cce_location_t * L, ccpairs_list_clean_handler_t * H, ccpairs_t P)
  __attribute__((__nonnull__(1,2,3)));

ccpairs_decl void ccpairs_init_list_error_handler (cce_location_t * L, ccpairs_list_error_handler_t * H, ccpairs_t P)
  __attribute__((__nonnull__(1,2,3)));

#define ccpairs_list_handler_init(L,P_H,P)				\
  _Generic((P_H),							\
	   ccpairs_list_error_handler_t *: ccpairs_init_list_error_handler, \
	   ccpairs_list_clean_handler_t *: ccpairs_init_list_clean_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release with item destructor.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_pair_item_clean_handler_t	ccpairs_pair_item_clean_handler_t;
typedef struct ccpairs_pair_item_error_handler_t	ccpairs_pair_item_error_handler_t;

struct ccpairs_pair_item_clean_handler_t {
  ccpairs_pair_clean_handler_t	handler;
  ccpairs_item_destructor_t *	item_destructor;
};

struct ccpairs_pair_item_error_handler_t {
  ccpairs_pair_error_handler_t	handler;
  ccpairs_item_destructor_t *	item_destructor;
};

ccpairs_decl void ccpairs_init_pair_item_clean_handler (cce_location_t * L, ccpairs_pair_item_clean_handler_t * H,
							ccpairs_t P, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

ccpairs_decl void ccpairs_init_pair_item_error_handler (cce_location_t * L, ccpairs_pair_item_error_handler_t * H,
							ccpairs_t P, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

#define ccpairs_pair_item_handler_init(L,P_H,P)				\
  _Generic((P_H),							\
	   ccpairs_pair_item_error_handler_t *: ccpairs_init_pair_item_error_handler, \
	   ccpairs_pair_item_clean_handler_t *: ccpairs_inite_pair_item_clean_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release with item destructor.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_list_item_clean_handler_t	ccpairs_list_item_clean_handler_t;
typedef struct ccpairs_list_item_error_handler_t	ccpairs_list_item_error_handler_t;

struct ccpairs_list_item_clean_handler_t {
  ccpairs_list_clean_handler_t	handler;
  ccpairs_item_destructor_t *	item_destructor;
};

struct ccpairs_list_item_error_handler_t {
  ccpairs_list_error_handler_t	handler;
  ccpairs_item_destructor_t *	item_destructor;
};

ccpairs_decl void ccpairs_init_list_item_clean_handler (cce_location_t * L, ccpairs_list_item_clean_handler_t * H,
						      ccpairs_t P, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

ccpairs_decl void ccpairs_init_list_item_error_handler (cce_location_t * L, ccpairs_list_item_error_handler_t * H,
						      ccpairs_t P, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

#define ccpairs_list_item_handler_init(L,P_H,P)				\
  _Generic((P_H),							\
	   ccpairs_list_item_error_handler_t *: ccpairs_init_list_item_error_handler, \
	   ccpairs_list_item_clean_handler_t *: ccpairs_init_list_item_clean_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_item_clean_handler_t	ccpairs_item_clean_handler_t;
typedef struct ccpairs_item_error_handler_t	ccpairs_item_error_handler_t;

struct ccpairs_item_clean_handler_t {
  cce_clean_handler_t		handler;
  ccpairs_item_destructor_t *	item_destructor;
};

struct ccpairs_item_error_handler_t {
  cce_error_handler_t		handler;
  ccpairs_item_destructor_t *	item_destructor;
};

ccpairs_decl void ccpairs_init_item_clean_handler (cce_location_t * L, ccpairs_item_clean_handler_t * H,
						   uintptr_t item, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,4)));

ccpairs_decl void ccpairs_init_item_error_handler (cce_location_t * L, ccpairs_item_error_handler_t * H,
						   uintptr_t item, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,4)));

#define ccpairs_item_handler_init(L,P_H,P)				\
  _Generic((P_H),							\
	   ccpairs_item_error_handler_t *: ccpairs_init_item_error_handler, \
	   ccpairs_item_clean_handler_t *: ccpairs_init_item_clean_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

ccpairs_decl ccpairs_t ccpairs_cons_guarded_error (cce_location_t * L, ccpairs_pair_error_handler_t * H, uintptr_t A, ccpairs_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

ccpairs_decl ccpairs_t ccpairs_cons_guarded_clean (cce_location_t * L, ccpairs_pair_clean_handler_t * H, uintptr_t A, ccpairs_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define ccpairs_cons_guarded(L,H,A,D)					\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_guarded_error,	\
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

ccpairs_decl ccpairs_t ccpairs_cons_improper_guarded_error (cce_location_t * L, ccpairs_pair_error_handler_t * H, uintptr_t A, uintptr_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

ccpairs_decl ccpairs_t ccpairs_cons_improper_guarded_clean (cce_location_t * L, ccpairs_pair_clean_handler_t * H, uintptr_t A, uintptr_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define ccpairs_cons_improper_guarded(L,H,A,D)				\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_improper_guarded_error, \
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_improper_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

ccpairs_decl ccpairs_t ccpairs_cons_node_guarded_error (cce_location_t * L, ccpairs_pair_error_handler_t * H, ccpairs_t A, ccpairs_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

ccpairs_decl ccpairs_t ccpairs_cons_node_guarded_clean (cce_location_t * L, ccpairs_pair_clean_handler_t * H, ccpairs_t A, ccpairs_t D)
  __attribute__((__nonnull__(1,2),__returns_nonnull__));

#define ccpairs_cons_node_guarded(L,H,A,D)				\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_node_guarded_error, \
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_node_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

ccpairs_decl ccpairs_t ccpairs_list_guarded_error (cce_location_t * L, ccpairs_list_item_error_handler_t * H,
						ccpairs_item_constructor_t * C, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4),__returns_nonnull__));

ccpairs_decl ccpairs_t ccpairs_list_guarded_clean (cce_location_t * L, ccpairs_list_item_clean_handler_t * H,
						ccpairs_item_constructor_t * C, ccpairs_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4),__returns_nonnull__));

#define ccpairs_list_guarded(L,H,item_constructor,item_destructor)	\
  _Generic((H),								\
	   ccpairs_list_item_error_handler_t *: ccpairs_list_guarded_error,	\
	   ccpairs_list_item_clean_handler_t *: ccpairs_list_guarded_clean)((L),(H),(item_constructor),(item_destructor))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCPAIRS_H */

/* end of file */
