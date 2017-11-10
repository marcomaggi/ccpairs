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
make_list_len (cce_location_t * upper_L, size_t len)
{
  if (len) {
    cce_location_t	L[1];
    ccpair_t		P[1+len];
    cce_handler_t	P_H[len];

    if (cce_location(L)) {
      cce_run_error_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (size_t i = len-1; i > 0; --i) {
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
    if (0) { print_list(P); }
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_length(L, P)); }
    assert(5 == ccpair_length(L, P));
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
    if (0) { print_list(P); }
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_length(L, P)); }
    assert(1024 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_5 (void)
/* Circular list with one item. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];
  bool			circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    /* Close the loop making the list  circular.  The cdr of the pair is
       the pair itself. */
    {
      P->D = (uintptr_t)P;
    }
    ccpair_length(L, P);
    circular = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == circular);
}

void
test_1_6 (void)
/* Circular list with 10 items, loop closing at the 5th item. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];
  bool			circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 10);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 5);
      P_last->D = (uintptr_t) P_loop_end;
    }
    ccpair_length(L, P);
    circular = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == circular);
}

void
test_1_7 (void)
/* Circular list with 10 items, loop closing at the 6th item. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];
  bool			circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 10);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 6);
      P_last->D = (uintptr_t) P_loop_end;
    }
    ccpair_length(L, P);
    circular = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == circular);
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
  if (1) { test_1_4(); }
  if (1) { test_1_5(); }
  if (1) { test_1_6(); }
  if (1) { test_1_7(); }

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
