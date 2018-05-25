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

ccmem_allocator_t const * ccpair_current_allocator;

ccmem_allocator_t const *
ccpair_register_allocator (ccmem_allocator_t const * new_allocator)
{
  ccmem_allocator_t const *	old_allocator = ccpair_current_allocator;

  ccpair_current_allocator = new_allocator;
  return old_allocator;
}


/** --------------------------------------------------------------------
 ** Memory functions.
 ** ----------------------------------------------------------------- */

ccpair_t
ccpair_alloc (cce_location_t * L)
{
  return ccmem_malloc(L, ccpair_current_allocator, sizeof(ccpair_t));
}

void
ccpair_free (ccpair_t P)
{
  if (P) {
    cce_location_t	L[1];

    if (cce_location(L)) {
      /* Absorb the exception. */
      cce_run_catch_handlers_final(L);
    } else {
      ccmem_free(L, ccpair_current_allocator, P);
      cce_run_body_handlers(L);
    }
  }
}

void
ccpair_free_list (ccpair_t volatile P)
/* Notice  that this  function is  *unable* to  correctly free  circular
   lists. */
{
  while (P) {
    cce_location_t	L[1];
    ccpair_t		Q = P;

    P = ccpair_cdr(P);
    if (cce_location(L)) {
      /* Absorb the exception. */
      cce_run_catch_handlers_final(L);
    } else {
      ccmem_free(L, ccpair_current_allocator, Q);
      cce_run_body_handlers(L);
    }
  }
}

/* end of file */
