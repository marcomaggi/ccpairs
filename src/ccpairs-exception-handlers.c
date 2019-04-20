/*
  Part of: CCPairs
  Contents: exception handler functions
  Date: Nov  7, 2017

  Abstract



  Copyright (C) 2017, 2018, 2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is free  software: you can redistribute it and/or  modify it under the
  terms of the  GNU Lesser General Public  License as published by  the Free Software
  Foundation, either version 3 of the License, or (at your option) any later version.

  This program  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release.
 ** ----------------------------------------------------------------- */

void
ccpairs_init_and_register_pair_clean_handler (cce_destination_t L, ccpairs_pair_clean_handler_t * H, ccpairs_t P)
{
  cce_init_and_register_handler(L, &(H->handler), cce_default_clean_handler_function,
				cce_resource_pointer(P), cce_resource_destructor(ccpairs_free));
}

void
ccpairs_init_and_register_pair_error_handler (cce_destination_t L, ccpairs_pair_error_handler_t * H, ccpairs_t P)
{
  cce_init_and_register_handler(L, &(H->handler), cce_default_error_handler_function,
				cce_resource_pointer(P), cce_resource_destructor(ccpairs_free));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

void
ccpairs_init_and_register_list_clean_handler (cce_destination_t L, ccpairs_list_clean_handler_t * H, ccpairs_t P)
{
  cce_init_and_register_handler(L, &(H->handler), cce_default_clean_handler_function,
				cce_resource_pointer(P), cce_resource_destructor(ccpairs_free_list));
}

void
ccpairs_init_and_register_list_error_handler (cce_destination_t L, ccpairs_list_error_handler_t * H, ccpairs_t P)
{
  cce_init_and_register_handler(L, &(H->handler), cce_default_error_handler_function,
				cce_resource_pointer(P), cce_resource_destructor(ccpairs_free_list));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_item_clean_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_clean_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_item_clean_handler_t const , H, _H);
  uintptr_t	item = (uintptr_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing item %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }
  H->item_destructor(item);
}

void
ccpairs_init_and_register_item_clean_handler (cce_destination_t L, ccpairs_item_clean_handler_t * H,
					      uintptr_t item, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler), ccpairs_item_clean_handler_function, cce_resource_pointer(item));
}

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_item_error_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_error_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_item_error_handler_t const , H, _H);
  uintptr_t	item = (uintptr_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing item %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }
  H->item_destructor(item);
}

void
ccpairs_init_and_register_item_error_handler (cce_destination_t L, ccpairs_item_error_handler_t * H,
					      uintptr_t item, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler), ccpairs_item_error_handler_function, cce_resource_pointer(item));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_pair_item_clean_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_clean_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_pair_item_clean_handler_t const , H, _H);
  ccpairs_t	P = (ccpairs_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }
  H->item_destructor(ccpairs_car(P));
  ccpairs_free(P);
}

void
ccpairs_init_and_register_pair_item_clean_handler (cce_destination_t L, ccpairs_pair_item_clean_handler_t * H,
						   ccpairs_t P, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler.handler), ccpairs_pair_item_clean_handler_function, cce_resource_pointer(P));
}

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_pair_item_error_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_error_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_pair_item_error_handler_t const , H, _H);
  ccpairs_t	P = (ccpairs_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }
  H->item_destructor(ccpairs_car(P));
  ccpairs_free(P);
}

void
ccpairs_init_and_register_pair_item_error_handler (cce_destination_t L, ccpairs_pair_item_error_handler_t * H,
						   ccpairs_t P, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler.handler), ccpairs_pair_item_error_handler_function, cce_resource_pointer(P));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_list_item_clean_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_clean_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_list_item_clean_handler_t const , H, _H);
  ccpairs_t	P = (ccpairs_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing list %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }

  /* Notice that this function is *unable* to correctly free circular lists. */
  while (P) {
    ccpairs_t	Q = P;
    P = ccpairs_cdr(P);
    H->item_destructor(ccpairs_car(Q));
    ccpairs_free(Q);
  }
}

void
ccpairs_init_and_register_list_item_clean_handler (cce_destination_t L, ccpairs_list_item_clean_handler_t * H,
						   ccpairs_t P, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler.handler), ccpairs_list_item_clean_handler_function, cce_resource_pointer(P));
}

/* ------------------------------------------------------------------ */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_list_item_error_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_error_handler_t const * _H)
{
  CCPAIRS_PC(ccpairs_list_item_error_handler_t const , H, _H);
  ccpairs_t	P = (ccpairs_t) cce_handler_resource_pointer(_H);

  if (0) { fprintf(stderr, "%s: releasing list %p\n", __func__, (void *)cce_handler_resource_pointer(_H)); }

  /* Notice that this function is *unable* to correctly free circular lists. */
  while (P) {
    ccpairs_t	Q = P;
    P = ccpairs_cdr(P);
    H->item_destructor(ccpairs_car(Q));
    ccpairs_free(Q);
  }
}

void
ccpairs_init_and_register_list_item_error_handler (cce_destination_t L, ccpairs_list_item_error_handler_t * H,
						   ccpairs_t P, ccpairs_item_destructor_t * D)
{
  H->item_destructor	= D;
  cce_init_and_register_handler(L, &(H->handler.handler), ccpairs_list_item_error_handler_function, cce_resource_pointer(P));
}

/* end of file */
