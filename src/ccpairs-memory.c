/*
  Part of: CCPairs
  Contents: memory functions
  Date: Tue Nov  7, 2017

  Abstract



  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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

ccmem_allocator_t const * ccpairs_current_allocator;

ccmem_allocator_t const *
ccpairs_register_allocator (ccmem_allocator_t const * new_allocator)
{
  ccmem_allocator_t const *	old_allocator = ccpairs_current_allocator;

  ccpairs_current_allocator = new_allocator;
  return old_allocator;
}


/** --------------------------------------------------------------------
 ** Memory functions.
 ** ----------------------------------------------------------------- */

ccpairs_t
ccpairs_alloc (cce_location_t * L)
{
  return ccmem_malloc(L, ccpairs_current_allocator, sizeof(ccpairs_t));
}

void
ccpairs_free (ccpairs_t P)
{
  if (P) {
    ccmem_free(ccpairs_current_allocator, P);
  }
}

void
ccpairs_free_list (ccpairs_t volatile P)
/* Notice  that this  function is  *unable* to  correctly free  circular
   lists. */
{
  while (P) {
    ccpairs_t	Q = P;

    P = ccpairs_cdr(P);
    ccmem_free(ccpairs_current_allocator, Q);
  }
}

/* end of file */
