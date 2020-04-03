/*
  Part of: CCPairs
  Contents: public header file
  Date: Thu Mar  1, 2012

  Abstract

	This is the public  header file for CCPairs.  It must be  included in all the
	source files using the library's facilities.

  Copyright (C) 2017-2020 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Lesser Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CCPAIRS_H
#define CCPAIRS_H 1

#ifdef __cplusplus
extern "C" {
#endif


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <ccexceptions.h>
#include <ccmemory.h>
#include <ccstructs.h>
#include <stdint.h>
#include <stdbool.h>


/** --------------------------------------------------------------------
 ** Macros.
 ** ----------------------------------------------------------------- */


/** --------------------------------------------------------------------
 ** Forward declarations.
 ** ----------------------------------------------------------------- */

typedef size_t		ccpairs_idx_t;
typedef size_t		ccpairs_len_t;

typedef uintptr_t ccpairs_item_constructor_t (cce_destination_t L, ccpairs_idx_t idx);
typedef void      ccpairs_item_destructor_t  (uintptr_t item);


/** --------------------------------------------------------------------
 ** Version functions.
 ** ----------------------------------------------------------------- */

cclib_decl char const *ccpairs_version_string		(void);
cclib_decl int	ccpairs_version_interface_current	(void);
cclib_decl int	ccpairs_version_interface_revision	(void);
cclib_decl int	ccpairs_version_interface_age		(void);


/** --------------------------------------------------------------------
 ** Initialisation functions.
 ** ----------------------------------------------------------------- */

cclib_decl void ccpairs_library_init (void)
  CCLIB_FUNC_ATTRIBUTE_CONSTRUCTOR;


/** --------------------------------------------------------------------
 ** Exceptional-condition objects: not enough items.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_descriptor_not_enough_items_t	ccpairs_descriptor_not_enough_items_t;
typedef struct ccpairs_condition_not_enough_items_t	ccpairs_condition_not_enough_items_t;

struct ccpairs_descriptor_not_enough_items_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_not_enough_items_t {
  cce_condition_logic_error_t	logic_error;
};

extern void cce_descriptor_set_parent_to(ccpairs_descriptor_not_enough_items_t) (cce_descriptor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl void ccpairs_condition_init_not_enough_items (cce_destination_t L, ccpairs_condition_not_enough_items_t * C)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl cce_condition_t const * ccpairs_condition_new_not_enough_items (void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl bool ccpairs_condition_is_not_enough_items (cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Exceptional-condition objects: empty list.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_descriptor_empty_list_t	ccpairs_descriptor_empty_list_t;
typedef struct ccpairs_condition_empty_list_t	ccpairs_condition_empty_list_t;

struct ccpairs_descriptor_empty_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_empty_list_t {
  ccpairs_condition_not_enough_items_t	not_enough_items;
};

extern void cce_descriptor_set_parent_to(ccpairs_descriptor_empty_list_t) (cce_descriptor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl void ccpairs_condition_init_empty_list (cce_destination_t L, ccpairs_condition_empty_list_t * C)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl cce_condition_t const * ccpairs_condition_new_empty_list (void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl bool ccpairs_condition_is_empty_list (cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Exceptional-condition objects: circular list.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_descriptor_circular_list_t	ccpairs_descriptor_circular_list_t;
typedef struct ccpairs_condition_circular_list_t	ccpairs_condition_circular_list_t;

struct ccpairs_descriptor_circular_list_t {
  cce_descriptor_t	descriptor;
};

struct ccpairs_condition_circular_list_t {
  cce_condition_logic_error_t	logic_error;
};

extern void cce_descriptor_set_parent_to(ccpairs_descriptor_circular_list_t) (cce_descriptor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

/* ------------------------------------------------------------------ */

cclib_decl void ccpairs_condition_init_circular_list (cce_destination_t L, ccpairs_condition_circular_list_t * C)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

cclib_decl cce_condition_t const * ccpairs_condition_new_circular_list (void)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl bool ccpairs_condition_is_circular_list (cce_condition_t const * C)
  CCLIB_FUNC_ATTRIBUTE_PURE
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);


/** --------------------------------------------------------------------
 ** Pair structure.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_stru_t		ccpairs_stru_t;
typedef ccpairs_stru_t *		ccpairs_t;
typedef ccpairs_t			ccpair_t;

struct ccpairs_stru_t {
  uintptr_t	A;
  uintptr_t 	D;
};

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_car (ccpairs_t P)
{
  return P->A;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_cdr (ccpairs_t P)
{
  return (ccpairs_t)(P->D);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_car_pair (ccpairs_t P)
{
  return (ccpairs_t)(P->A);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_cdr_value (ccpairs_t P)
{
  return P->D;
}


/** --------------------------------------------------------------------
 ** Memory allocation.
 ** ----------------------------------------------------------------- */

cclib_decl ccmem_allocator_t const * ccpairs_register_allocator (ccmem_allocator_t const * allocator)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t	ccpairs_alloc (cce_destination_t L)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl void	ccpairs_free   (ccpairs_t P);

cclib_decl void	ccpairs_free_list (ccpairs_t P);


/** --------------------------------------------------------------------
 ** Constructors.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL
static inline ccpairs_t
ccpairs_cons (cce_destination_t L, uintptr_t A, ccpairs_t D)
{
  ccpairs_t	P = ccpairs_alloc(L);
  P->A = A;
  P->D = (uintptr_t)D;
  return P;
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_cons_improper (cce_destination_t L, uintptr_t A, uintptr_t D)
{
  return ccpairs_cons(L, A, (ccpairs_t)D);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_cons_node (cce_destination_t L, ccpairs_t A, ccpairs_t D)
{
  return ccpairs_cons(L, (uintptr_t)A, D);
}

/* ------------------------------------------------------------------ */

cclib_decl ccpairs_t ccpairs_list (cce_destination_t L,
				     ccpairs_item_constructor_t * item_constructor,
				     ccpairs_item_destructor_t  * item_destructor)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);


/** --------------------------------------------------------------------
 ** Inspection.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_CONST
static inline bool
ccpairs_is_empty (ccpairs_t P)
{
  return (NULL == P);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_CONST
static inline bool
ccpairs_is_null (ccpairs_t P)
{
  return (NULL == P);
}

cclib_decl ccpairs_len_t ccpairs_length (cce_destination_t L, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1);

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_PURE
static inline bool
ccpairs_is_last (ccpairs_t P)
{
  return (P && (NULL == ccpairs_cdr(P)));
}

cclib_decl bool ccpairs_is_circular (ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_LEAF
  CCLIB_FUNC_ATTRIBUTE_PURE;


/** --------------------------------------------------------------------
 ** Pair accessors.
 ** ----------------------------------------------------------------- */

cclib_decl ccpairs_t ccpairs_ref_pair (cce_destination_t L, ccpairs_t P, ccpairs_idx_t idx)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t ccpairs_last_pair (cce_destination_t L, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_first_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 0);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_second_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 1);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_third_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 2);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_fourth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 3);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_fifth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 4);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_sixth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 5);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_seventh_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 6);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_eighth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 7);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_nineth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 8);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_tenth_pair (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref_pair(L, P, 9);
}


/** --------------------------------------------------------------------
 ** Item accessors.
 ** ----------------------------------------------------------------- */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_ref (cce_destination_t L, ccpairs_t P, ccpairs_idx_t const idx)
{
  return ccpairs_car(ccpairs_ref_pair(L, P, idx));
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
static inline uintptr_t
ccpairs_last (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_car(ccpairs_last_pair(L, P));
}

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_first (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 0);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_second (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 1);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_third (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 2);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_fourth (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 3);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_fifth (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 4);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_sixth (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 5);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_seventh (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 6);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_eighth (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 7);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_nineth (cce_destination_t L, ccpairs_t P)
{
  return ccpairs_ref(L, P, 8);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline uintptr_t
ccpairs_tenth (cce_destination_t L, ccpairs_t P)
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

cclib_decl ccpairs_t ccpairs_map_1_forward (cce_destination_t L, ccpairs_map_1_fun_t * fun, ccpairs_t P1)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl ccpairs_t ccpairs_map_2_forward (cce_destination_t L, ccpairs_map_2_fun_t * fun, ccpairs_t P1, ccpairs_t P2)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl ccpairs_t ccpairs_map_3_forward (cce_destination_t L, ccpairs_map_3_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl ccpairs_t ccpairs_map_4_forward (cce_destination_t L, ccpairs_map_4_fun_t * fun,
					    ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

cclib_decl ccpairs_t ccpairs_map_5_forward (cce_destination_t L, ccpairs_map_5_fun_t * fun,
					    ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4, ccpairs_t P5)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2);

/* ------------------------------------------------------------------ */

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
static inline ccpairs_t
ccpairs_map (cce_destination_t L, ccpairs_map_fun_t * fun, ccpairs_t P)
{
  return ccpairs_map_1_forward(L, fun, P);
}

CCLIB_FUNC_ATTRIBUTE_ALWAYS_INLINE
CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
static inline ccpairs_t
ccpairs_map_forward (cce_destination_t L, ccpairs_map_fun_t * fun, ccpairs_t P)
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

cclib_decl void ccpairs_init_and_register_pair_clean_handler (cce_destination_t L, ccpairs_pair_clean_handler_t * H, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void ccpairs_init_and_register_pair_error_handler (cce_destination_t L, ccpairs_pair_error_handler_t * H, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

#define ccpairs_init_and_register_pair_handler(L,P_H,P)			\
  _Generic((P_H),							\
	   ccpairs_pair_clean_handler_t *: ccpairs_init_and_register_pair_clean_handler, \
	   ccpairs_pair_error_handler_t *: ccpairs_init_and_register_pair_error_handler)((L),(P_H),(P))


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

cclib_decl void ccpairs_init_and_register_list_clean_handler (cce_destination_t L, ccpairs_list_clean_handler_t * H, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

cclib_decl void ccpairs_init_and_register_list_error_handler (cce_destination_t L, ccpairs_list_error_handler_t * H, ccpairs_t P)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3);

#define ccpairs_init_and_register_list_handler(L,P_H,P)			\
  _Generic((P_H),							\
	   ccpairs_list_clean_handler_t *: ccpairs_init_and_register_list_clean_handler, \
	   ccpairs_list_error_handler_t *: ccpairs_init_and_register_list_error_handler)((L),(P_H),(P))


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

typedef struct ccpairs_item_clean_handler_t	ccpairs_item_clean_handler_t;
typedef struct ccpairs_item_error_handler_t	ccpairs_item_error_handler_t;

struct ccpairs_item_clean_handler_t {
  cce_clean_handler_t		handler;
  ccpairs_item_destructor_t	*item_destructor;
};

struct ccpairs_item_error_handler_t {
  cce_error_handler_t		handler;
  ccpairs_item_destructor_t	*item_destructor;
};

cclib_decl void ccpairs_init_and_register_item_clean_handler (cce_destination_t L, ccpairs_item_clean_handler_t * H,
								uintptr_t item, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,4);

cclib_decl void ccpairs_init_and_register_item_error_handler (cce_destination_t L, ccpairs_item_error_handler_t * H,
								uintptr_t item, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,4);

#define ccpairs_init_and_register_item_handler(L,P_H,ITEM,ITEM_DESTRUCTOR) \
  _Generic((P_H),							\
	   ccpairs_item_clean_handler_t *: ccpairs_init_and_register_item_clean_handler, \
	   ccpairs_item_error_handler_t *: ccpairs_init_and_register_item_error_handler)((L),(P_H),(ITEM),(ITEM_DESTRUCTOR))


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

cclib_decl void ccpairs_init_and_register_pair_item_clean_handler (cce_destination_t L, ccpairs_pair_item_clean_handler_t * H,
								     ccpairs_t P, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4);

cclib_decl void ccpairs_init_and_register_pair_item_error_handler (cce_destination_t L, ccpairs_pair_item_error_handler_t * H,
								     ccpairs_t P, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4);

#define ccpairs_init_and_register_pair_item_handler(L,P_H,P,ITEM_DESTRUCTOR) \
  _Generic((P_H),							\
	   ccpairs_pair_item_clean_handler_t *: ccpairs_init_and_register_pair_item_clean_handler, \
	   ccpairs_pair_item_error_handler_t *: ccpairs_init_and_register_pair_item_error_handler)((L),(P_H),(P),(ITEM_DESTRUCTOR))


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

cclib_decl void ccpairs_init_and_register_list_item_clean_handler (cce_destination_t L, ccpairs_list_item_clean_handler_t * H,
								     ccpairs_t P, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4);

cclib_decl void ccpairs_init_and_register_list_item_error_handler (cce_destination_t L, ccpairs_list_item_error_handler_t * H,
								     ccpairs_t P, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4);

#define ccpairs_init_and_register_list_item_handler(L,P_H,P,ITEM_DESTRUCTOR) \
  _Generic((P_H),							\
	   ccpairs_list_item_clean_handler_t *: ccpairs_init_and_register_list_item_clean_handler, \
	   ccpairs_list_item_error_handler_t *: ccpairs_init_and_register_list_item_error_handler)((L),(P_H),(P),(ITEM_DESTRUCTOR))


/** --------------------------------------------------------------------
 ** Guarded constructors.
 ** ----------------------------------------------------------------- */

cclib_decl ccpairs_t ccpairs_cons_guarded_error (cce_destination_t L, ccpairs_pair_error_handler_t * H, uintptr_t A, ccpairs_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t ccpairs_cons_guarded_clean (cce_destination_t L, ccpairs_pair_clean_handler_t * H, uintptr_t A, ccpairs_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

#define ccpairs_cons_guarded(L,H,A,D)					\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_guarded_error,	\
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

cclib_decl ccpairs_t ccpairs_cons_improper_guarded_error (cce_destination_t L, ccpairs_pair_error_handler_t * H, uintptr_t A, uintptr_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t ccpairs_cons_improper_guarded_clean (cce_destination_t L, ccpairs_pair_clean_handler_t * H, uintptr_t A, uintptr_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

#define ccpairs_cons_improper_guarded(L,H,A,D)				\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_improper_guarded_error, \
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_improper_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

cclib_decl ccpairs_t ccpairs_cons_node_guarded_error (cce_destination_t L, ccpairs_pair_error_handler_t * H, ccpairs_t A, ccpairs_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t ccpairs_cons_node_guarded_clean (cce_destination_t L, ccpairs_pair_clean_handler_t * H, ccpairs_t A, ccpairs_t D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

#define ccpairs_cons_node_guarded(L,H,A,D)				\
  _Generic((H),								\
	   ccpairs_pair_error_handler_t *: ccpairs_cons_node_guarded_error, \
	   ccpairs_pair_clean_handler_t *: ccpairs_cons_node_guarded_clean)((L),(H),(A),(D))

/* ------------------------------------------------------------------ */

cclib_decl ccpairs_t ccpairs_list_guarded_error (cce_destination_t L, ccpairs_list_item_error_handler_t * H,
						   ccpairs_item_constructor_t * C, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

cclib_decl ccpairs_t ccpairs_list_guarded_clean (cce_destination_t L, ccpairs_list_item_clean_handler_t * H,
						   ccpairs_item_constructor_t * C, ccpairs_item_destructor_t * D)
  CCLIB_FUNC_ATTRIBUTE_NONNULL(1,2,3,4)
  CCLIB_FUNC_ATTRIBUTE_RETURNS_NONNULL;

#define ccpairs_list_guarded(L,H,item_constructor,item_destructor)	\
  _Generic((H),								\
	   ccpairs_list_item_error_handler_t *: ccpairs_list_guarded_error, \
	   ccpairs_list_item_clean_handler_t *: ccpairs_list_guarded_clean)((L),(H),(item_constructor),(item_destructor))


/** --------------------------------------------------------------------
 ** Done.
 ** ----------------------------------------------------------------- */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* CCPAIRS_H */

/* end of file */
