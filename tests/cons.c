/*
  Part of: CCPairs
  Contents: test for basic construction functions
  Date: Nov  7, 2017

  Abstract

	Test file for basic construction functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void
test_1_1 (void)
/* Single pair allocation and release. */
{
  ccpair_t	P;

  P = ccpair_cons(1, NULL);
  {
    assert(NULL != P);
    assert(1    == ccpair_car(P));
    assert(NULL == ccpair_cdr(P));
    assert(0    == ccpair_cdr_value(P));
  }
  ccpair_free(P);
}

void
test_1_2 (void)
/* Single pair allocation and release using the exception handler. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    {
      assert(NULL != P);
      assert(1    == ccpair_car(P));
      assert(NULL == ccpair_cdr(P));
      assert(0    == ccpair_cdr_value(P));
    }
    cce_run_cleanup_handlers(L);
  }
}

/* ------------------------------------------------------------------ */

void
test_2_1 (void)
/* Chain  of  pairs.   The list:  1,  2,  3,  4,  5, NULL  allocated  in
   reverse. */
{
  ccpair_t	P[5];

  P[4] = ccpair_cons(5, NULL);
  P[3] = ccpair_cons(4, P[4]);
  P[2] = ccpair_cons(3, P[3]);
  P[1] = ccpair_cons(2, P[2]);
  P[0] = ccpair_cons(1, P[1]);

  {
    uintptr_t	i;
    ccpair_t	Q;

    for (Q=P[0], i=1; NULL != Q; Q = ccpair_cdr(Q), ++i) {
      if (0) {
	fprintf(stderr, "%s: i=%lu, car(Q)=%lu\n", __func__, i, ccpair_car(Q));
      }
      assert(i == ccpair_car(Q));
    }
  }

  for (int i=0; i<5; ++i) {
    ccpair_free(P[i]);
  }
}

int
main (void)
{
  ccpair_init();

  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_2_1(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
