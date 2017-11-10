/*
  Part of: CCPairs
  Contents: tests for accessor functions
  Date: Nov  9, 2017

  Abstract

	Test file for accessors functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


/** --------------------------------------------------------------------
 ** Helpers.
 ** ----------------------------------------------------------------- */

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

ccpair_t
make_list_len (cce_location_t * upper_L, ccpair_len_t len)
{
  if (len) {
    cce_location_t	L[1];
    ccpair_t		P[1+len];
    cce_handler_t	P_H[len];

    if (cce_location(L)) {
      cce_run_error_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (ccpair_idx_t i = len-1; i > 0; --i) {
	if (0) { fprintf(stderr, "%s: i=%lu len=%lu\n", __func__, i, len); }
	P[i] = ccpair_cons(L, 1+i, P[1+i]);
	ccpair_error_handler_pair_init(L, &(P_H[i]), P[i]);
      }
      P[0] = ccpair_cons(L, 1, P[1]);
      cce_run_cleanup_handlers(L);
    }
    return P[0];
  } else {
    return NULL;
  }
}

void
print_list (ccpair_t P)
{
  fprintf(stderr, "(");
  for (; P; P = ccpair_cdr(P)) {
    fprintf(stderr, "%lu", ccpair_car(P));
    if (! ccpair_is_last(P)) {
      fprintf(stderr, " ");
    }
  }
  fprintf(stderr, ")\n");
}


/** --------------------------------------------------------------------
 ** Pair-ref function.
 ** ----------------------------------------------------------------- */

void
test_1_1 (void)
/* Empty list, "not enough items" exception. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_ref_pair(L, P, 1);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_1_2 (void)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(P == ccpair_ref_pair(L, P, 0));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_3 (void)
/* Five items list, success. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    //P = make_list_5(L);
    P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_list(P); }
    if (0) { fprintf(stderr, "%s: len=%lu\n", __func__, ccpair_length(L, P)); }
    if (0) { fprintf(stderr, "%s: item=%lu\n", __func__, ccpair_car(ccpair_ref_pair(L, P, 3))); }
    assert(4 == ccpair_car(ccpair_ref_pair(L, P, 3)));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_4 (void)
/* 1024 items list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(1000 == ccpair_car(ccpair_ref_pair(L, P, 999)));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Ref function.
 ** ----------------------------------------------------------------- */

void
test_2_1 (void)
/* Empty list, "not enough items" exception. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_ref(L, P, 1);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_2_2 (void)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(1 == ccpair_ref(L, P, 0));
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_3 (void)
/* Five items list, success. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    //P = make_list_5(L);
    P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_list(P); }
    if (0) { fprintf(stderr, "%s: len=%lu\n", __func__, ccpair_length(L, P)); }
    if (0) { fprintf(stderr, "%s: item=%lu\n", __func__, ccpair_car(ccpair_ref_pair(L, P, 3))); }
    assert(4 == ccpair_ref(L, P, 3));
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_4 (void)
/* 1024 items list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(1000 == ccpair_ref(L, P, 999));
    cce_run_cleanup_handlers(L);
  }
}


int
main (void)
{
  ccpair_init();

  /* pair-ref function */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_1_3(); }
  if (1) { test_1_4(); }

  /* ref function */
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }
  if (1) { test_2_3(); }
  if (1) { test_2_4(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
