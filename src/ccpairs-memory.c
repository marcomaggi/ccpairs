/*
  Part of: CCPairs
  Contents: memory functions
  Date: Tue Nov  7, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Predefined memory allocator.
 ** ----------------------------------------------------------------- */

static ccpair_t
default_alloc (cce_location_t * L, ccpair_allocator_t const * allocator CCPAIR_UNUSED)
{
  ccpair_t	P = malloc(sizeof(ccpair_stru_t));
  if (NULL != P) {
    return P;
  } else {
    cce_raise(L, cce_condition_new_errno_clear());
  }
}

static void
default_free (ccpair_allocator_t const * allocator CCPAIR_UNUSED, ccpair_t P)
{
  free(P);
}

static ccpair_allocator_t const default_allocator = {
  .alloc	= default_alloc,
  .free		= default_free
};

static ccpair_allocator_t const * current_allocator = &default_allocator;

ccpair_allocator_t const *
ccpair_register_allocator (ccpair_allocator_t const * new_allocator)
{
  ccpair_allocator_t const *	old_allocator = current_allocator;
  assert(new_allocator);
  current_allocator = new_allocator;
  return old_allocator;
}


/** --------------------------------------------------------------------
 ** Memory functions.
 ** ----------------------------------------------------------------- */

ccpair_t
ccpair_alloc (cce_location_t * L)
{
  return current_allocator->alloc(L, current_allocator);
}

void
ccpair_free (ccpair_t P)
{
  if (P) {
    current_allocator->free(current_allocator, P);
  }
}

void
ccpair_free_list (ccpair_t P)
/* Notice  that this  function is  *unable* to  correctly free  circular
   lists. */
{
  ccpair_t	Q;

  while (P) {
    Q = P;
    P = ccpair_cdr(P);
    current_allocator->free(current_allocator, Q);
  }
}

/* end of file */
