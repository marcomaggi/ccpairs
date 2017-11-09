/*
  Part of: CCPairs
  Contents: list inspection functions
  Date: Thu Nov  9, 2017

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


size_t
ccpair_length (cce_location_t * L, ccpair_t hare)
{
  ccpair_t	turtle = hare;
  size_t	len = 0;

  if (hare) {
    /* Hare only step. */
    {
      if (0) { fprintf(stderr, "%s: hare=%p, turtle=%p\n", __func__, (void *)hare, (void *)turtle); }
      hare = ccpair_cdr(hare);
      ++len;
    }
    while (hare) {
      if (0) { fprintf(stderr, "%s: hare=%p, turtle=%p\n", __func__, (void *)hare, (void *)turtle); }
      /* Hare and turtle step. */
      {
	if (hare != turtle) {
	  turtle = ccpair_cdr(turtle);
	  hare   = ccpair_cdr(hare);
	  ++len;
	} else {
	  /* This is a circular list. */
	  cce_raise(L, ccpair_condition_new_circular_list());
	}
      }
      if (0) { fprintf(stderr, "%s: hare=%p, turtle=%p\n", __func__, (void *)hare, (void *)turtle); }
      /* Hare only step. */
      if (hare) {
	if (hare != turtle) {
	  hare = ccpair_cdr(hare);
	  ++len;
	} else {
	  /* This is a circular list. */
	  cce_raise(L, ccpair_condition_new_circular_list());
	}
      }
    }
  }
  return len;
}

/* end of file */
