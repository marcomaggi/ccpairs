/*
  Part of: CCPairs
  Contents: test for basic construction functions
  Date: Nov  7, 2017

  Abstract

	Test file for basic construction functions.

  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include <cctests.h>
#include <ccpairs.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Single pair allocation.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t L)
/* Single pair allocation and release. */
{
  ccpairs_t	P;

  P = ccpairs_cons(L, 1, NULL);
  {
    cctests_assert(L, NULL != P);
    cctests_assert(L, 1    == ccpairs_car(P));
    cctests_assert(L, NULL == ccpairs_cdr(P));
    cctests_assert(L, 0    == ccpairs_cdr_value(P));
  }
  ccpairs_free(P);
}

void
test_1_2 (cce_destination_t upper_L)
/* Single pair allocation and release using the exception handler. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons(L, 1, NULL);
    ccpairs_pair_clean_handler_init(L, P_H, P);
    {
      cctests_assert(L, NULL != P);
      cctests_assert(L, 1    == ccpairs_car(P));
      cctests_assert(L, NULL == ccpairs_cdr(P));
      cctests_assert(L, 0    == ccpairs_cdr_value(P));
    }
    cce_run_body_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Single pair allocation and release using the guarded constructor. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons_guarded(L, P_H, 1, NULL);
    {
      cctests_assert(L, NULL != P);
      cctests_assert(L, 1    == ccpairs_car(P));
      cctests_assert(L, NULL == ccpairs_cdr(P));
      cctests_assert(L, 0    == ccpairs_cdr_value(P));
    }
    cce_run_body_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* Single pair allocation and release using the guarded constructor. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    cce_location_t		inner_L[1];
    ccpairs_pair_error_handler_t	inner_P_H[1];
    ccpairs_t			P;

    if (cce_location(inner_L)) {
      cce_run_catch_handlers_raise(inner_L, L);
    } else {
      P = ccpairs_cons_guarded(L, inner_P_H, 1, NULL);
      {
	cctests_assert(L, NULL != P);
	cctests_assert(L, 1    == ccpairs_car(P));
	cctests_assert(L, NULL == ccpairs_cdr(P));
	cctests_assert(L, 0    == ccpairs_cdr_value(P));
      }
      cce_run_body_handlers(L);
    }

    ccpairs_pair_clean_handler_init(L, P_H, P);
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Chain of pairs.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Chain  of  pairs.   The list:  1,  2,  3,  4,  5, NULL  allocated  in
   reverse. */
{
  cce_location_t		L[1];
  ccpairs_t			P[5];
  ccpairs_pair_clean_handler_t	P_H[5];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    P[4] = ccpairs_cons(L, 5, NULL); ccpairs_pair_clean_handler_init(L, &(P_H[4]), P[4]);
    P[3] = ccpairs_cons(L, 4, P[4]); ccpairs_pair_clean_handler_init(L, &(P_H[3]), P[3]);
    P[2] = ccpairs_cons(L, 3, P[3]); ccpairs_pair_clean_handler_init(L, &(P_H[2]), P[2]);
    P[1] = ccpairs_cons(L, 2, P[2]); ccpairs_pair_clean_handler_init(L, &(P_H[1]), P[1]);
    P[0] = ccpairs_cons(L, 1, P[1]); ccpairs_pair_clean_handler_init(L, &(P_H[0]), P[0]);

    {
      uintptr_t	i;
      ccpairs_t	Q;

      for (Q=P[0], i=1; NULL != Q; Q = ccpairs_cdr(Q), ++i) {
	if (0) {
	  fprintf(stderr, "%s: i=%lu, car(Q)=%lu\n", __func__, i, ccpairs_car(Q));
	}
	cctests_assert(L, i == ccpairs_car(Q));
      }
    }
    cce_run_body_handlers(L);
  }
}


int
main (void)
{
  ccpairs_library_init();
  cctests_init("cons");
  {
    cctests_begin_group("single pair");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
      cctests_run(test_1_4);
    }
    cctests_end_group();

    cctests_begin_group("chain of pairs");
    {
      cctests_run(test_2_1);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
