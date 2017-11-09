/*
  Part of: CCPairs
  Contents: accessor functions
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


uintptr_t
ccpair_ref (cce_location_t * L, ccpair_t P, unsigned idx)
{
  for (unsigned i=0; i<idx; ++i) {
    if (P) {
      P = ccpair_cdr(P);
    } else {
      cce_raise(L, ccpair_condition_new_not_enough_items());
    }
  }
  return ccpair_car(P);
}

ccpair_t
ccpair_pair_ref (cce_location_t * L, ccpair_t P, unsigned idx)
{
  for (unsigned i=0; i<idx; ++i) {
    if (P) {
      P = ccpair_cdr(P);
    } else {
      cce_raise(L, ccpair_condition_new_not_enough_items());
    }
  }
  return P;
}

/* end of file */
