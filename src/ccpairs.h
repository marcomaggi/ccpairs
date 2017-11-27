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

#include <ccexceptions.h>
#include <stdint.h>
#include <stdbool.h>


/** --------------------------------------------------------------------
 ** Constants.
 ** ----------------------------------------------------------------- */




/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef struct ccpair_stru_t		ccpair_stru_t;
typedef ccpair_stru_t *			ccpair_t;

typedef struct ccpair_allocator_t	ccpair_allocator_t;

typedef ccpair_t ccpair_alloc_fun_t	(cce_location_t *L, ccpair_allocator_t const * allocator);
typedef void     ccpair_free_fun_t	(ccpair_allocator_t const * allocator, ccpair_t P);

typedef size_t				ccpair_idx_t;
typedef size_t				ccpair_len_t;

typedef struct ccpair_item_handler_t		ccpair_item_handler_t;
typedef struct ccpair_pair_item_handler_t	ccpair_pair_item_handler_t;
typedef struct ccpair_list_item_handler_t	ccpair_list_item_handler_t;

/* ------------------------------------------------------------------ */

typedef struct ccpair_descriptor_base_t			ccpair_descriptor_base_t;
typedef struct ccpair_descriptor_not_enough_items_t	ccpair_descriptor_not_enough_items_t;
typedef struct ccpair_descriptor_empty_list_t		ccpair_descriptor_empty_list_t;
typedef struct ccpair_descriptor_circular_list_t	ccpair_descriptor_circular_list_t;

typedef struct ccpair_condition_base_t			ccpair_condition_base_t;
typedef struct ccpair_condition_not_enough_items_t	ccpair_condition_not_enough_items_t;
typedef struct ccpair_condition_empty_list_t		ccpair_condition_empty_list_t;
typedef struct ccpair_condition_circular_list_t		ccpair_condition_circular_list_t;


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

ccpair_decl char const *ccpair_version_string			(void);
ccpair_decl int		ccpair_version_interface_current	(void);
ccpair_decl int		ccpair_version_interface_revision	(void);
ccpair_decl int		ccpair_version_interface_age		(void);


/** --------------------------------------------------------------------
 ** Initialisation functions.
 ** ----------------------------------------------------------------- */

ccpair_decl void	ccpair_init (void)
  __attribute__((__constructor__));


/** --------------------------------------------------------------------
 ** Exceptional conditions.
 ** ----------------------------------------------------------------- */

struct ccpair_descriptor_base_t {
  cce_descriptor_t	descriptor;
};

struct ccpair_condition_base_t {
  cce_condition_t	condition;
};

ccpair_decl const ccpair_descriptor_base_t * const ccpair_descriptor_base;

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpair_condition_is_base (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpair_descriptor_base->descriptor));
}

/* ------------------------------------------------------------------ */

struct ccpair_descriptor_not_enough_items_t {
  cce_descriptor_t	descriptor;
};

struct ccpair_condition_not_enough_items_t {
  ccpair_condition_base_t	base;
};

ccpair_decl const ccpair_descriptor_not_enough_items_t * const ccpair_descriptor_not_enough_items;

ccpair_decl cce_condition_t const * ccpair_condition_new_not_enough_items (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpair_condition_is_not_enough_items (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpair_descriptor_not_enough_items->descriptor));
}

/* ------------------------------------------------------------------ */

struct ccpair_descriptor_empty_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpair_condition_empty_list_t {
  ccpair_condition_base_t	base;
};

ccpair_decl const ccpair_descriptor_empty_list_t * const ccpair_descriptor_empty_list;

ccpair_decl cce_condition_t const * ccpair_condition_new_empty_list (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpair_condition_is_empty_list (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpair_descriptor_empty_list->descriptor));
}

/* ------------------------------------------------------------------ */

struct ccpair_descriptor_circular_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpair_condition_circular_list_t {
  ccpair_condition_base_t	base;
};

ccpair_decl const ccpair_descriptor_circular_list_t * const ccpair_descriptor_circular_list;

ccpair_decl cce_condition_t const * ccpair_condition_new_circular_list (void)
  __attribute__((__leaf__,__pure__));

__attribute__((__pure__,__nonnull__(1),__always_inline__))
static inline bool
ccpair_condition_is_circular_list (cce_condition_t const * C)
{
  return cce_is_condition(C, &(ccpair_descriptor_circular_list->descriptor));
}


/** --------------------------------------------------------------------
 ** Pair structure.
 ** ----------------------------------------------------------------- */

struct ccpair_stru_t {
  uintptr_t	A;
  uintptr_t 	D;
};

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline uintptr_t
ccpair_car (ccpair_t P)
{
  return P->A;
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline ccpair_t
ccpair_cdr (ccpair_t P)
{
  return (ccpair_t)(P->D);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline ccpair_t
ccpair_car_pair (ccpair_t P)
{
  return (ccpair_t)(P->A);
}

__attribute__((__always_inline__,__pure__,__nonnull__(1)))
static inline uintptr_t
ccpair_cdr_value (ccpair_t P)
{
  return P->D;
}


/** --------------------------------------------------------------------
 ** Memory allocation.
 ** ----------------------------------------------------------------- */

struct ccpair_allocator_t {
  ccpair_alloc_fun_t *		alloc;
  ccpair_free_fun_t *		free;
};

ccpair_decl ccpair_allocator_t const * ccpair_register_allocator (ccpair_allocator_t const * allocator)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccpair_decl ccpair_t	ccpair_alloc (cce_location_t * L)
  __attribute__((__nonnull__(1),__returns_nonnull__));
ccpair_decl void	ccpair_free   (ccpair_t P);
ccpair_decl void	ccpair_free_list (ccpair_t P);


/** --------------------------------------------------------------------
 ** Constructors.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1),__returns_nonnull__))
static inline ccpair_t
ccpair_cons (cce_location_t * L, uintptr_t A, ccpair_t D)
{
  ccpair_t	P = ccpair_alloc(L);
  P->A = A;
  P->D = (uintptr_t)D;
  return P;
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_cons_improper (cce_location_t * L, uintptr_t A, uintptr_t D)
{
  return ccpair_cons(L, A, (ccpair_t)D);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_cons_node (cce_location_t * L, ccpair_t A, ccpair_t D)
{
  return ccpair_cons(L, (uintptr_t)A, D);
}

/* ------------------------------------------------------------------ */

typedef uintptr_t ccpair_item_constructor_t (cce_location_t * L, ccpair_idx_t idx);
typedef void      ccpair_item_destructor_t  (uintptr_t item);

ccpair_decl ccpair_t ccpair_list (cce_location_t * L, ccpair_item_constructor_t * C, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Inspection.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__const__))
static inline bool
ccpair_is_empty (ccpair_t P)
{
  return (NULL == P)? true : false;
}

__attribute__((__always_inline__,__const__))
static inline bool
ccpair_is_null (ccpair_t P)
{
  return (NULL == P)? true : false;
}

ccpair_decl ccpair_len_t ccpair_length (cce_location_t * L, ccpair_t P)
  __attribute__((__nonnull__(1)));

__attribute__((__always_inline__,__pure__))
static inline bool
ccpair_is_last (ccpair_t P)
{
  return (P && (NULL == ccpair_cdr(P)))? true : false;
}

ccpair_decl bool ccpair_is_circular (ccpair_t P)
  __attribute__((__leaf__,__pure__));


/** --------------------------------------------------------------------
 ** Pair accessors.
 ** ----------------------------------------------------------------- */

ccpair_decl ccpair_t ccpair_ref_pair (cce_location_t * L, ccpair_t P, ccpair_idx_t idx)
  __attribute__((__nonnull__(1),__returns_nonnull__));

ccpair_decl ccpair_t ccpair_last_pair (cce_location_t * L, ccpair_t P)
  __attribute__((__nonnull__(1),__returns_nonnull__));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_first_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 0);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_second_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 1);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_third_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 2);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_fourth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 3);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_fifth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 4);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_sixth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 5);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_seventh_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 6);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_eighth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 7);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_nineth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 8);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_tenth_pair (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref_pair(L, P, 9);
}


/** --------------------------------------------------------------------
 ** Item accessors.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_ref (cce_location_t * L, ccpair_t P, ccpair_idx_t const idx)
{
  return ccpair_car(ccpair_ref_pair(L, P, idx));
}

__attribute__((__always_inline__,__nonnull__(1,2)))
static inline uintptr_t
ccpair_last (cce_location_t * L, ccpair_t P)
{
  return ccpair_car(ccpair_last_pair(L, P));
}

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_first (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 0);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_second (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 1);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_third (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 2);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_fourth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 3);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_fifth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 4);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_sixth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 5);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_seventh (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 6);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_eighth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 7);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_nineth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 8);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline uintptr_t
ccpair_tenth (cce_location_t * L, ccpair_t P)
{
  return ccpair_ref(L, P, 9);
}


/** --------------------------------------------------------------------
 ** Mapping and folding functions.
 ** ----------------------------------------------------------------- */

typedef uintptr_t ccpair_map_fun_t   (uintptr_t item);
typedef uintptr_t ccpair_map_1_fun_t (uintptr_t item);
typedef uintptr_t ccpair_map_2_fun_t (uintptr_t item1, uintptr_t item2);
typedef uintptr_t ccpair_map_3_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3);
typedef uintptr_t ccpair_map_4_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3, uintptr_t item4);
typedef uintptr_t ccpair_map_5_fun_t (uintptr_t item1, uintptr_t item2, uintptr_t item3, uintptr_t item4, uintptr_t item5);

/* ------------------------------------------------------------------ */

ccpair_decl ccpair_t ccpair_map_1_forward (cce_location_t * L, ccpair_map_1_fun_t * fun, ccpair_t P1)
  __attribute__((__nonnull__(1)));

ccpair_decl ccpair_t ccpair_map_2_forward (cce_location_t * L, ccpair_map_2_fun_t * fun, ccpair_t P1, ccpair_t P2)
  __attribute__((__nonnull__(1)));

ccpair_decl ccpair_t ccpair_map_3_forward (cce_location_t * L, ccpair_map_3_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3)
  __attribute__((__nonnull__(1)));

ccpair_decl ccpair_t ccpair_map_4_forward (cce_location_t * L, ccpair_map_4_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3, ccpair_t P4)
  __attribute__((__nonnull__(1)));

ccpair_decl ccpair_t ccpair_map_5_forward (cce_location_t * L, ccpair_map_5_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3, ccpair_t P4, ccpair_t P5)
  __attribute__((__nonnull__(1)));

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_map (cce_location_t * L, ccpair_map_fun_t * fun, ccpair_t P)
{
  return ccpair_map_1_forward(L, fun, P);
}

__attribute__((__always_inline__,__nonnull__(1)))
static inline ccpair_t
ccpair_map_forward (cce_location_t * L, ccpair_map_fun_t * fun, ccpair_t P)
{
  return ccpair_map_1_forward(L, fun, P);
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release.
 ** ----------------------------------------------------------------- */

cce_decl void ccpair_cleanup_handler_pair_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void ccpair_error_handler_pair_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

cce_decl void ccpair_cleanup_handler_list_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
  __attribute__((__nonnull__(1,2,3)));

cce_decl void ccpair_error_handler_list_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
  __attribute__((__nonnull__(1,2,3)));


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release with item destructor.
 ** ----------------------------------------------------------------- */

struct ccpair_pair_item_handler_t {
  cce_handler_t			handler;
  ccpair_item_destructor_t *	item_destructor;
};

ccpair_decl void ccpair_cleanup_handler_pair_item_init (cce_location_t * L, ccpair_pair_item_handler_t * H,
							ccpair_t P, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

ccpair_decl void ccpair_error_handler_pair_item_init (cce_location_t * L, ccpair_pair_item_handler_t * H,
						      ccpair_t P, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release with item destructor.
 ** ----------------------------------------------------------------- */

struct ccpair_list_item_handler_t {
  cce_handler_t			handler;
  ccpair_item_destructor_t *	item_destructor;
};

ccpair_decl void ccpair_cleanup_handler_list_item_init (cce_location_t * L, ccpair_list_item_handler_t * H,
							ccpair_t P, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));

ccpair_decl void ccpair_error_handler_list_item_init (cce_location_t * L, ccpair_list_item_handler_t * H,
						      ccpair_t P, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,3,4)));


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

struct ccpair_item_handler_t {
  cce_handler_t			handler;
  ccpair_item_destructor_t *	item_destructor;
};

ccpair_decl void ccpair_cleanup_handler_item_init (cce_location_t * L, ccpair_item_handler_t * H,
						   uintptr_t item, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,4)));

ccpair_decl void ccpair_error_handler_item_init (cce_location_t * L, ccpair_item_handler_t * H,
						 uintptr_t item, ccpair_item_destructor_t * D)
  __attribute__((__nonnull__(1,2,4)));



/** --------------------------------------------------------------------
 ** Constructors with exception handlers initialisation.
 ** ----------------------------------------------------------------- */

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_error_handler (cce_location_t * L, uintptr_t A, ccpair_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons(L, A, D);
  ccpair_error_handler_pair_init(L, H, P);
  return P;
}

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_cleanup_handler (cce_location_t * L, uintptr_t A, ccpair_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons(L, A, D);
  ccpair_cleanup_handler_pair_init(L, H, P);
  return P;
}

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_improper_error_handler (cce_location_t * L, uintptr_t A, uintptr_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons_improper(L, A, D);
  ccpair_error_handler_pair_init(L, H, P);
  return P;
}

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_improper_cleanup_handler (cce_location_t * L, uintptr_t A, uintptr_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons_improper(L, A, D);
  ccpair_cleanup_handler_pair_init(L, H, P);
  return P;
}

/* ------------------------------------------------------------------ */

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_node_error_handler (cce_location_t * L, ccpair_t A, ccpair_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons_node(L, A, D);
  ccpair_error_handler_pair_init(L, H, P);
  return P;
}

__attribute__((__always_inline__,__nonnull__(1,4),__returns_nonnull__))
static inline ccpair_t
ccpair_cons_node_cleanup_handler (cce_location_t * L, ccpair_t A, ccpair_t D, cce_handler_t * H)
{
  ccpair_t	P = ccpair_cons_node(L, A, D);
  ccpair_cleanup_handler_pair_init(L, H, P);
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
