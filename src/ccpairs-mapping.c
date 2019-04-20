/*
  Part of: CCPairs
  Contents: mapping functions
  Date: Tue Nov  7, 2017

  Abstract



  Copyright (C) 2017-2019 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Mapping functions.
 ** ----------------------------------------------------------------- */

ccpairs_t
ccpairs_map_1_forward (cce_location_t * upper_L, ccpairs_map_fun_t * fun, ccpairs_t volatile P)
{
  ccpairs_t	R = NULL, Q = NULL;

  if (P) {
    cce_location_t			L[1];
    ccpairs_list_error_handler_t	R_H[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_raise(L, upper_L);
    } else {
      /* We perform the  first application outside of the  loop, so that
	 we can initialise the handler for R. */
      R = Q = ccpairs_cons(L, fun(ccpairs_car(P)), NULL);
      P = ccpairs_cdr(P);
      ccpairs_init_and_register_list_error_handler(L, R_H, R);

      for (; P; P = ccpairs_cdr(P)) {
	ccpairs_t	T = ccpairs_cons(L, fun(ccpairs_car(P)), NULL);
	/* Append  the  new  pair  to  the  tail  of  the  list  we  are
	   building. */
	Q->D = (uintptr_t) T;
	/* The new pair is the new tail. */
	Q    = T;
      }

      cce_run_body_handlers(L);
    }
  }
  /* Return the head of the new list. */
  return R;
}

ccpairs_t
ccpairs_map_2_forward (cce_location_t * L, ccpairs_map_2_fun_t * fun, ccpairs_t P1, ccpairs_t P2)
{
  ccpairs_t	R = NULL,  Q = NULL;

  for (; P1 && P2; P1 = ccpairs_cdr(P1), P2 = ccpairs_cdr(P2)) {
    ccpairs_t	T = ccpairs_cons(L, fun(ccpairs_car(P1), ccpairs_car(P2)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpairs_t
ccpairs_map_3_forward (cce_location_t * L, ccpairs_map_3_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3)
{
  ccpairs_t	R = NULL,  Q = NULL;

  for (; P1 && P2 && P3; P1 = ccpairs_cdr(P1), P2 = ccpairs_cdr(P2), P3 = ccpairs_cdr(P3)) {
    ccpairs_t	T = ccpairs_cons(L, fun(ccpairs_car(P1), ccpairs_car(P2), ccpairs_car(P3)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpairs_t
ccpairs_map_4_forward (cce_location_t * L, ccpairs_map_4_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4)
{
  ccpairs_t	R = NULL,  Q = NULL;

  for (; P1 && P2 && P3 && P4; P1 = ccpairs_cdr(P1), P2 = ccpairs_cdr(P2), P3 = ccpairs_cdr(P3), P4 = ccpairs_cdr(P4)) {
    ccpairs_t	T = ccpairs_cons(L, fun(ccpairs_car(P1), ccpairs_car(P2), ccpairs_car(P3), ccpairs_car(P4)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpairs_t
ccpairs_map_5_forward (cce_location_t * L, ccpairs_map_5_fun_t * fun, ccpairs_t P1, ccpairs_t P2, ccpairs_t P3, ccpairs_t P4, ccpairs_t P5)
{
  ccpairs_t	R = NULL,  Q = NULL;

  for (;
       P1 && P2 && P3 && P4 && P5;
       P1 = ccpairs_cdr(P1), P2 = ccpairs_cdr(P2), P3 = ccpairs_cdr(P3), P4 = ccpairs_cdr(P4), P5 = ccpairs_cdr(P5)) {
    ccpairs_t	T = ccpairs_cons(L, fun(ccpairs_car(P1), ccpairs_car(P2), ccpairs_car(P3), ccpairs_car(P4), ccpairs_car(P5)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

/* end of file */
