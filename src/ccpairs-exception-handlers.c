/*
  Part of: CCPairs
  Contents: exception handler functions
  Date: Nov  7, 2017

  Abstract



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


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_pair_handler_function (cce_condition_t const * C CCPAIR_UNUSED, cce_handler_t * H)
{
  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)H->pointer); }
  ccpair_free(H->pointer);
}

void
ccpair_pair_clean_handler_init (cce_location_t * L, ccpair_pair_clean_handler_t * H, ccpair_t P)
{
  H->handler.handler.function	= ccpair_pair_handler_function;
  H->handler.handler.pointer	= P;
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpair_pair_error_handler_init (cce_location_t * L, ccpair_pair_error_handler_t * H, ccpair_t P)
{
  H->handler.handler.function	= ccpair_pair_handler_function;
  H->handler.handler.pointer	= P;
  cce_register_error_handler(L, &(H->handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_list_handler_function (cce_condition_t const * C CCPAIR_UNUSED, cce_handler_t * H)
{
  if (0) { fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)H->pointer); }
  ccpair_free(H->pointer);
}

void
ccpair_list_clean_handler_init (cce_location_t * L, ccpair_list_clean_handler_t * H, ccpair_t P)
{
  H->handler.handler.function	= ccpair_list_handler_function;
  H->handler.handler.pointer	= P;
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpair_list_error_handler_init (cce_location_t * L, ccpair_list_error_handler_t * H, ccpair_t P)
{
  H->handler.handler.function	= ccpair_list_handler_function;
  H->handler.handler.pointer	= P;
  cce_register_error_handler(L, &(H->handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_pair_item_handler_function (cce_condition_t const * C CCPAIR_UNUSED, cce_handler_t * _H)
{
  CCPAIR_PC(ccpair_pair_item_clean_handler_t, H, _H);
  ccpair_t	P = (ccpair_t) (H->handler.handler.handler.pointer);

  if (0) { fprintf(stderr, "%s: releasing pair %p with item destructor\n", __func__, (void *)P); }
  H->item_destructor(ccpair_car(P));
  ccpair_free(P);
}

void
ccpair_pair_item_clean_handler_init (cce_location_t * L, ccpair_pair_item_clean_handler_t * H, ccpair_t P, ccpair_item_destructor_t * D)
{
  H->handler.handler.handler.function	= ccpair_pair_item_handler_function;
  H->handler.handler.handler.pointer	= P;
  H->item_destructor			= D;
  cce_register_clean_handler(L, &(H->handler.handler));
}

void
ccpair_pair_item_error_handler_init (cce_location_t * L, ccpair_pair_item_error_handler_t * H, ccpair_t P, ccpair_item_destructor_t * D)
{
  H->handler.handler.handler.function	= ccpair_pair_item_handler_function;
  H->handler.handler.handler.pointer	= P;
  H->item_destructor			= D;
  cce_register_error_handler(L, &(H->handler.handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release with item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_list_item_handler_function (cce_condition_t const * C CCPAIR_UNUSED, cce_handler_t * _H)
{
  CCPAIR_PC(ccpair_list_item_clean_handler_t, H, _H);
  ccpair_t	P = (ccpair_t) (H->handler.handler.handler.pointer);

  if (0) { fprintf(stderr, "%s: releasing list %p with item destructor\n", __func__, (void *)P); }

  /* Notice that  this function is  *unable* to correctly  free circular
     lists. */
  while (P) {
    ccpair_t	Q = P;
    P = ccpair_cdr(P);
    H->item_destructor(ccpair_car(Q));
    ccpair_free(Q);
  }
}

void
ccpair_list_item_clean_handler_init (cce_location_t * L, ccpair_list_item_clean_handler_t * H, ccpair_t P, ccpair_item_destructor_t * D)
{
  H->handler.handler.handler.function	= ccpair_list_item_handler_function;
  H->handler.handler.handler.pointer	= P;
  H->item_destructor			= D;
  cce_register_clean_handler(L, &(H->handler.handler));
}

void
ccpair_list_item_error_handler_init (cce_location_t * L, ccpair_list_item_error_handler_t * H, ccpair_t P, ccpair_item_destructor_t * D)
{
  H->handler.handler.handler.function	= ccpair_list_item_handler_function;
  H->handler.handler.handler.pointer	= P;
  H->item_destructor			= D;
  cce_register_error_handler(L, &(H->handler.handler));
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: item destructor.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_item_handler_function (cce_condition_t const * C CCPAIR_UNUSED, cce_handler_t * _H)
{
  CCPAIR_PC(ccpair_item_clean_handler_t, H, _H);
  uintptr_t	item = (uintptr_t) (H->handler.handler.pointer);

  if (0) {
    fprintf(stderr, "%s: releasing list %p\n", __func__, (void *)(H->handler.handler.pointer));
  }
  H->item_destructor(item);
}

void
ccpair_item_clean_handler_init (cce_location_t * L, ccpair_item_clean_handler_t * H, uintptr_t item, ccpair_item_destructor_t * D)
{
  H->handler.handler.function	= ccpair_item_handler_function;
  H->handler.handler.pointer	= (void *) item;
  H->item_destructor		= D;
  cce_register_clean_handler(L, &(H->handler));
}

void
ccpair_item_error_handler_init (cce_location_t * L, ccpair_item_error_handler_t * H, uintptr_t item, ccpair_item_destructor_t * D)
{
  H->handler.handler.function	= ccpair_item_handler_function;
  H->handler.handler.pointer	= (void *) item;
  H->item_destructor		= D;
  cce_register_error_handler(L, &(H->handler));
}

/* end of file */
