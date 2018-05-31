/*
  Part of: CCPairs
  Contents: accessor functions
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
 ** Pair accessors.
 ** ----------------------------------------------------------------- */

ccpairs_t
ccpairs_ref_pair (cce_location_t * L, ccpairs_t P, ccpairs_idx_t const idx)
{
  if (P) {
    for (ccpairs_idx_t i = 0; ; ++i) {
      if (P) {
	if (idx > i) {
	  P = ccpairs_cdr(P);
	} else {
	  return P;
	}
      } else {
	cce_raise(L, ccpairs_condition_new_not_enough_items());
      }
    }
  } else {
    cce_raise(L, ccpairs_condition_new_empty_list());
  }
}

ccpairs_t
ccpairs_last_pair (cce_location_t * L, ccpairs_t P)
{
  if (0) { fprintf(stderr, "%s: enter, P=%p\n", __func__, (void *)P); }
  for (; P; P = ccpairs_cdr(P)) {
    if (0) { fprintf(stderr, "%s: check is last P=%p\n", __func__, (void *)P); }
    if (ccpairs_is_last(P)) {
      return P;
    }
  }
  cce_raise(L, ccpairs_condition_new_empty_list());
}


/** --------------------------------------------------------------------
 ** Item accessors.
 ** ----------------------------------------------------------------- */


/* end of file */
