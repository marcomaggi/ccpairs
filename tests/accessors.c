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
 ** Ref-pair function.
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
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
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


/** --------------------------------------------------------------------
 ** Last-pair function.
 ** ----------------------------------------------------------------- */

void
test_3_1 (void)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_last_pair(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_3_2 (void)
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
    assert(P == ccpair_last_pair(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_3_3 (void)
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
    if (0) { fprintf(stderr, "%s: item=%lu\n", __func__, ccpair_car(ccpair_last_pair(L, P))); }
    assert(5 == ccpair_car(ccpair_last_pair(L, P)));
    cce_run_cleanup_handlers(L);
  }
}

void
test_3_4 (void)
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
    assert(1024 == ccpair_car(ccpair_last_pair(L, P)));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Last function.
 ** ----------------------------------------------------------------- */

void
test_4_1 (void)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_last(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_4_2 (void)
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
    assert(1 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_4_3 (void)
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
    if (0) { fprintf(stderr, "%s: item=%lu\n", __func__, ccpair_last(L, P)); }
    assert(5 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_4_4 (void)
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
    assert(1024 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** First function.
 ** ----------------------------------------------------------------- */

void
test_5_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(1 == ccpair_first(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_2 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_first(L, P);
    fprintf(stderr, "%s: \n", __func__);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Second function.
 ** ----------------------------------------------------------------- */

void
test_6_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(2 == ccpair_second(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_6_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_second(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_6_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_second(L, P)); }
    ccpair_second(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Third function.
 ** ----------------------------------------------------------------- */

void
test_7_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(3 == ccpair_third(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_7_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_third(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_7_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_third(L, P)); }
    ccpair_third(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_7_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 2);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_third(L, P)); }
    ccpair_third(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Fourth function.
 ** ----------------------------------------------------------------- */

void
test_8_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(4 == ccpair_fourth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_8_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_fourth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_8_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_fourth(L, P)); }
    ccpair_fourth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_8_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 3);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_fourth(L, P)); }
    ccpair_fourth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Fifth function.
 ** ----------------------------------------------------------------- */

void
test_9_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(5 == ccpair_fifth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_9_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_fifth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_9_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_fifth(L, P)); }
    ccpair_fifth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_9_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 4);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_fifth(L, P)); }
    ccpair_fifth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Sixth function.
 ** ----------------------------------------------------------------- */

void
test_10_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(6 == ccpair_sixth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_10_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_sixth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_10_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_sixth(L, P)); }
    ccpair_sixth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_10_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_sixth(L, P)); }
    ccpair_sixth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Seventh function.
 ** ----------------------------------------------------------------- */

void
test_11_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(7 == ccpair_seventh(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_11_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_seventh(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_11_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_seventh(L, P)); }
    ccpair_seventh(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_11_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 6);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_seventh(L, P)); }
    ccpair_seventh(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Eighth function.
 ** ----------------------------------------------------------------- */

void
test_12_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(8 == ccpair_eighth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_12_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_eighth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_12_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_eighth(L, P)); }
    ccpair_eighth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_12_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 7);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_eighth(L, P)); }
    ccpair_eighth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Nineth function.
 ** ----------------------------------------------------------------- */

void
test_13_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(9 == ccpair_nineth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_13_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_nineth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_13_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_nineth(L, P)); }
    ccpair_nineth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_13_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 8);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_nineth(L, P)); }
    ccpair_nineth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


/** --------------------------------------------------------------------
 ** Tenth function.
 ** ----------------------------------------------------------------- */

void
test_14_1 (void)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    assert(10 == ccpair_tenth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_14_2 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_empty_list(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = NULL;
    ccpair_tenth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_14_3 (void)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_tenth(L, P)); }
    ccpair_tenth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}

void
test_14_4 (void)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  ccpair_t		P;
  bool			exception = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_not_enough_items(cce_condition(L)));
    exception = true;
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_len(L, 9);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    print_list(P);
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_tenth(L, P)); }
    ccpair_tenth(L, P);
    cce_run_cleanup_handlers(L);
  }
  assert(true == exception);
}


int
main (void)
{
  ccpair_init();

  /* ref-pair function */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_1_3(); }
  if (1) { test_1_4(); }

  /* ref function */
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }
  if (1) { test_2_3(); }
  if (1) { test_2_4(); }

  /* last-pair function */
  if (1) { test_3_1(); }
  if (1) { test_3_2(); }
  if (1) { test_3_3(); }
  if (1) { test_3_4(); }

  /* last function */
  if (1) { test_4_1(); }
  if (1) { test_4_2(); }
  if (1) { test_4_3(); }
  if (1) { test_4_4(); }

  /* first function */
  if (1) { test_5_1(); }
  if (1) { test_5_2(); }

  /* second function */
  if (1) { test_6_1(); }
  if (1) { test_6_2(); }
  if (1) { test_6_3(); }

  /* third function */
  if (1) { test_7_1(); }
  if (1) { test_7_2(); }
  if (1) { test_7_3(); }
  if (1) { test_7_4(); }

  /* fourth function */
  if (1) { test_8_1(); }
  if (1) { test_8_2(); }
  if (1) { test_8_3(); }
  if (1) { test_8_4(); }

  /* fifth function */
  if (1) { test_9_1(); }
  if (1) { test_9_2(); }
  if (1) { test_9_3(); }
  if (1) { test_9_4(); }

  /* sixth function */
  if (1) { test_10_1(); }
  if (1) { test_10_2(); }
  if (1) { test_10_3(); }
  if (1) { test_10_4(); }

  /* seventh function */
  if (1) { test_11_1(); }
  if (1) { test_11_2(); }
  if (1) { test_11_3(); }
  if (1) { test_11_4(); }

  /* eighth function */
  if (1) { test_12_1(); }
  if (1) { test_12_2(); }
  if (1) { test_12_3(); }
  if (1) { test_12_4(); }

  /* nineth function */
  if (1) { test_13_1(); }
  if (1) { test_13_2(); }
  if (1) { test_13_3(); }
  if (1) { test_13_4(); }

  /* tenth function */
  if (1) { test_14_1(); }
  if (1) { test_14_2(); }
  if (1) { test_14_3(); }
  if (1) { test_14_4(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
