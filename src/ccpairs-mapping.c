/*
  Part of: CCPairs
  Contents: mapping functions
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
 ** Mapping functions.
 ** ----------------------------------------------------------------- */

ccpair_t
ccpair_map_1_forward (cce_location_t * upper_L, ccpair_map_fun_t * fun, ccpair_t volatile P)
{
  ccpair_t	R = NULL, Q = NULL;

  if (P) {
    cce_location_t		L[1];
    ccpair_list_error_handler_t	R_H[1];

    if (cce_location(L)) {
      cce_run_catch_handlers_raise(L, upper_L);
    } else {
      /* We perform the  first application outside of the  loop, so that
	 we can initialise the handler for R. */
      R = Q = ccpair_cons(L, fun(ccpair_car(P)), NULL);
      P = ccpair_cdr(P);
      ccpair_list_error_handler_init(L, R_H, R);

      for (; P; P = ccpair_cdr(P)) {
	ccpair_t	T = ccpair_cons(L, fun(ccpair_car(P)), NULL);
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

ccpair_t
ccpair_map_2_forward (cce_location_t * L, ccpair_map_2_fun_t * fun, ccpair_t P1, ccpair_t P2)
{
  ccpair_t	R = NULL,  Q = NULL;

  for (; P1 && P2; P1 = ccpair_cdr(P1), P2 = ccpair_cdr(P2)) {
    ccpair_t	T = ccpair_cons(L, fun(ccpair_car(P1), ccpair_car(P2)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpair_t
ccpair_map_3_forward (cce_location_t * L, ccpair_map_3_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3)
{
  ccpair_t	R = NULL,  Q = NULL;

  for (; P1 && P2 && P3; P1 = ccpair_cdr(P1), P2 = ccpair_cdr(P2), P3 = ccpair_cdr(P3)) {
    ccpair_t	T = ccpair_cons(L, fun(ccpair_car(P1), ccpair_car(P2), ccpair_car(P3)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpair_t
ccpair_map_4_forward (cce_location_t * L, ccpair_map_4_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3, ccpair_t P4)
{
  ccpair_t	R = NULL,  Q = NULL;

  for (; P1 && P2 && P3 && P4; P1 = ccpair_cdr(P1), P2 = ccpair_cdr(P2), P3 = ccpair_cdr(P3), P4 = ccpair_cdr(P4)) {
    ccpair_t	T = ccpair_cons(L, fun(ccpair_car(P1), ccpair_car(P2), ccpair_car(P3), ccpair_car(P4)), NULL);
    if (Q) {
      Q->D = (uintptr_t) T;
      Q    = T;
    } else {
      R = Q = T;
    }
  }
  return R;
}

ccpair_t
ccpair_map_5_forward (cce_location_t * L, ccpair_map_5_fun_t * fun, ccpair_t P1, ccpair_t P2, ccpair_t P3, ccpair_t P4, ccpair_t P5)
{
  ccpair_t	R = NULL,  Q = NULL;

  for (;
       P1 && P2 && P3 && P4 && P5;
       P1 = ccpair_cdr(P1), P2 = ccpair_cdr(P2), P3 = ccpair_cdr(P3), P4 = ccpair_cdr(P4), P5 = ccpair_cdr(P5)) {
    ccpair_t	T = ccpair_cons(L, fun(ccpair_car(P1), ccpair_car(P2), ccpair_car(P3), ccpair_car(P4), ccpair_car(P5)), NULL);
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
