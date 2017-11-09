/*
  Part of: CCPairs
  Contents: test for inspection functions
  Date: Nov  9, 2017

  Abstract

	Test file for inspection functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ccpair_t
make_list_5 (cce_location_t * upper_L)
{
  cce_location_t	L[1];
  ccpair_t		P[5];
  cce_handler_t		P_H[5];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    P[4] = ccpair_cons(L, 5, NULL); ccpair_error_handler_pair_init(L, &(P_H[4]), P[4]);
    P[3] = ccpair_cons(L, 4, P[4]); ccpair_error_handler_pair_init(L, &(P_H[3]), P[3]);
    P[2] = ccpair_cons(L, 3, P[3]); ccpair_error_handler_pair_init(L, &(P_H[2]), P[2]);
    P[1] = ccpair_cons(L, 2, P[2]); ccpair_error_handler_pair_init(L, &(P_H[1]), P[1]);
    P[0] = ccpair_cons(L, 1, P[1]);
    cce_run_cleanup_handlers(L);
  }
  return P[0];
}


/** --------------------------------------------------------------------
 ** Length function.
 ** ----------------------------------------------------------------- */

void
test_1_1 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    assert(0 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}
void
test_1_2 (void)
/* One item list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(1 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}
void
test_1_3 (void)
/* Five items list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_5(L);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_length(L, P)); }
    assert(5 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-null function.
 ** ----------------------------------------------------------------- */

void
test_2_1 (void)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  assert(true == ccpair_is_null(P));
}
void
test_2_2 (void)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(false == ccpair_is_null(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-empty function.
 ** ----------------------------------------------------------------- */

void
test_3_1 (void)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  assert(true == ccpair_is_empty(P));
}
void
test_3_2 (void)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(false == ccpair_is_empty(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-last-pair function.
 ** ----------------------------------------------------------------- */

void
test_4_1 (void)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  assert(false == ccpair_is_last(P));
}
void
test_4_2 (void)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(true == ccpair_is_last(P));
    cce_run_cleanup_handlers(L);
  }
}


int
main (void)
{
  ccpair_init();

  /* Length function */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_1_3(); }

  /* Is-null function */
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }

  /* Is-empty function */
  if (1) { test_3_1(); }
  if (1) { test_3_2(); }

  /* Is-last function */
  if (1) { test_4_1(); }
  if (1) { test_4_2(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
