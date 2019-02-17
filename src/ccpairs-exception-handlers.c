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

__attribute__((__nonnull__(1,2)))
static void
ccpairs_pair_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_handler_t * H)
{
  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)H->pointer); }
  ccpairs_free(H->pointer);
}

void
ccpairs_init_pair_clean_handler (cce_location_t * L, ccpairs_pair_clean_handler_t * H, ccpairs_t P)
{
  cce_clean_handler_set(&(H->handler), P, ccpairs_pair_handler_function);
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpairs_init_pair_error_handler (cce_location_t * L, ccpairs_pair_error_handler_t * H, ccpairs_t P)
{
  cce_error_handler_set(&(H->handler), P, ccpairs_pair_handler_function);
  cce_register_error_handler(L, &(H->handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_list_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_handler_t * H)
{
  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)H->pointer); }
  ccpairs_free(H->pointer);
}

void
ccpairs_init_list_clean_handler (cce_location_t * L, ccpairs_list_clean_handler_t * H, ccpairs_t P)
{
  cce_clean_handler_set(&(H->handler), P, ccpairs_list_handler_function);
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpairs_init_list_error_handler (cce_location_t * L, ccpairs_list_error_handler_t * H, ccpairs_t P)
{
  cce_error_handler_set(&(H->handler), P, ccpairs_list_handler_function);
  cce_register_error_handler(L, &(H->handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_pair_item_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_handler_t * _H)
{
  CCPAIRS_PC(ccpairs_pair_item_clean_handler_t, H, _H);
  ccpairs_t	P = (ccpairs_t) (H->handler.handler.handler.pointer);

  if (0) { fprintf(stderr, "%s: releasing pair %p with item destructor\n", __func__, (void *)P); }
  H->item_destructor(ccpairs_car(P));
  ccpairs_free(P);
}

void
ccpairs_init_pair_item_clean_handler (cce_location_t * L, ccpairs_pair_item_clean_handler_t * H, ccpairs_t P, ccpairs_item_destructor_t * D)
{
  cce_clean_handler_set(&(H->handler.handler), P, ccpairs_pair_item_handler_function);
  H->item_destructor			= D;
  cce_register_clean_handler(L, &(H->handler.handler));
}

void
ccpairs_init_pair_item_error_handler (cce_location_t * L, ccpairs_pair_item_error_handler_t * H, ccpairs_t P, ccpairs_item_destructor_t * D)
{
  cce_error_handler_set(&(H->handler.handler), P, ccpairs_pair_item_handler_function);
  H->item_destructor			= D;
  cce_register_error_handler(L, &(H->handler.handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_list_item_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_handler_t * _H)
{
  CCPAIRS_PC(ccpairs_list_item_clean_handler_t, H, _H);
  ccpairs_t	P = (ccpairs_t) (H->handler.handler.handler.pointer);

  if (0) { fprintf(stderr, "%s: releasing list %p with item destructor\n", __func__, (void *)P); }

  /* Notice that  this function is  *unable* to correctly  free circular
     lists. */
  while (P) {
    ccpairs_t	Q = P;
    P = ccpairs_cdr(P);
    H->item_destructor(ccpairs_car(Q));
    ccpairs_free(Q);
  }
}

void
ccpairs_init_list_item_clean_handler (cce_location_t * L, ccpairs_list_item_clean_handler_t * H, ccpairs_t P, ccpairs_item_destructor_t * D)
{
  cce_clean_handler_set(&(H->handler.handler), P, ccpairs_list_item_handler_function);
  H->item_destructor			= D;
  cce_register_clean_handler(L, &(H->handler.handler));
}

void
ccpairs_init_list_item_error_handler (cce_location_t * L, ccpairs_list_item_error_handler_t * H, ccpairs_t P, ccpairs_item_destructor_t * D)
{
  cce_error_handler_set(&(H->handler.handler), P, ccpairs_list_item_handler_function);
  H->item_destructor			= D;
  cce_register_error_handler(L, &(H->handler.handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((__nonnull__(1,2)))
static void
ccpairs_item_handler_function (cce_condition_t const * C CCPAIRS_UNUSED, cce_handler_t * _H)
{
  CCPAIRS_PC(ccpairs_item_clean_handler_t, H, _H);
  uintptr_t	item = (uintptr_t) (H->handler.handler.pointer);

  if (0) {
    fprintf(stderr, "%s: releasing list %p\n", __func__, (void *)(H->handler.handler.pointer));
  }
  H->item_destructor(item);
}

void
ccpairs_init_item_clean_handler (cce_location_t * L, ccpairs_item_clean_handler_t * H, uintptr_t item, ccpairs_item_destructor_t * D)
{
  cce_clean_handler_set(&(H->handler), (void *)item, ccpairs_item_handler_function);
  H->item_destructor		= D;
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpairs_init_item_error_handler (cce_location_t * L, ccpairs_item_error_handler_t * H, uintptr_t item, ccpairs_item_destructor_t * D)
{
  cce_error_handler_set(&(H->handler), (void *)item, ccpairs_item_handler_function);
  H->item_destructor		= D;
  cce_register_error_handler(L, &(H->handler));
}

/* end of file */
