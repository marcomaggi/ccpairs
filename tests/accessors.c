/*
  Part of: CCPairs
  Contents: tests for accessor functions
  Date: Nov  9, 2017

  Abstract

	Test file for accessors functions.

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
 ** Helpers.
 ** ----------------------------------------------------------------- */

ccpairs_t
make_list_len (cce_location_t * upper_L, size_t len)
{
  if (len) {
    cce_location_t		L[1];
    ccpairs_t			P[1+len];
    ccpairs_pair_error_handler_t	P_H[len];

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      cce_run_catch_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (size_t i = len-1; i > 0; --i) {
	if (0) { fprintf(stderr, "%s: i=%lu len=%lu\n", __func__, i, len); }
	P[i] = ccpairs_cons_guarded(L, &(P_H[i]), 1+i, P[1+i]);
	if (0) { fprintf(stderr, "%s: P[%lu]=%p\n", __func__, i, (void *)(P[i])); }
      }
      P[0] = ccpairs_cons(L, 1, P[1]);
      if (0) { fprintf(stderr, "%s: P[%u]=%p\n", __func__, 0, (void *)(P[0])); }
      cce_run_body_handlers(L);
      if (0) { fprintf(stderr, "%s: returning P[0]=%p\n", __func__, (void *)(P[0])); }
      return P[0];
    }
  } else {
    return NULL;
  }
}

void
print_list (ccpairs_t P)
{
  fprintf(stderr, "(");
  for (; P; P = ccpairs_cdr(P)) {
    fprintf(stderr, "%lu", ccpairs_car(P));
    if (! ccpairs_is_last(P)) {
      fprintf(stderr, " ");
    }
  }
  fprintf(stderr, ")\n");
}


/** --------------------------------------------------------------------
 ** Ref-pair function.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_ref_pair(L, P, 1);
    cctests_raise_unreachable(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons_guarded(L, P_H, 1, NULL);
    cctests_assert(L, P == ccpairs_ref_pair(L, P, 0));
    cce_run_body_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 5);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 4 == ccpairs_car(ccpairs_ref_pair(L, P, 3)));
    cce_run_body_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 1024);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 1000 == ccpairs_car(ccpairs_ref_pair(L, P, 999)));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Ref function.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_ref(L, P, 1);
    cctests_raise_unreachable(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons_guarded(L, P_H, 1, NULL);
    cctests_assert(L, 1 == ccpairs_ref(L, P, 0));
    cce_run_body_handlers(L);
  }
}

void
test_2_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 5);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 4 == ccpairs_ref(L, P, 3));
    cce_run_body_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 1024);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 1000 == ccpairs_ref(L, P, 999));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Last-pair function.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_last_pair(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t		L[1];
  ccpairs_pair_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons_guarded(L, P_H, 1, NULL);
    cctests_assert(L, P == ccpairs_last_pair(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_3_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 5);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 5 == ccpairs_car(ccpairs_last_pair(L, P)));
    cce_run_body_handlers(L);
  }
}

void
test_3_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 1024);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 1024 == ccpairs_car(ccpairs_last_pair(L, P)));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Last function.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_last(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  ccpairs_pair_clean_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_cons_guarded(L, P_H, 1, NULL);
    cctests_assert(L, 1 == ccpairs_last(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_4_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 5);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 5 == ccpairs_last(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_4_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 1024);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 1024 == ccpairs_last(L, P));
    cce_run_body_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** First function.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 1 == ccpairs_first(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_5_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_first(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Second function.
 ** ----------------------------------------------------------------- */

void
test_6_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 2 == ccpairs_second(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_6_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_second(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_6_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_second(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Third function.
 ** ----------------------------------------------------------------- */

void
test_7_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 3 == ccpairs_third(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_7_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_third(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_7_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_third(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_7_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 2);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_third(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Fourth function.
 ** ----------------------------------------------------------------- */

void
test_8_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 4 == ccpairs_fourth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_8_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_fourth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_8_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_fourth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_8_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 3);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_fourth(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Fifth function.
 ** ----------------------------------------------------------------- */

void
test_9_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 5 == ccpairs_fifth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_9_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_fifth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_9_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_fifth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_9_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 4);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_fifth(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Sixth function.
 ** ----------------------------------------------------------------- */

void
test_10_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 6 == ccpairs_sixth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_10_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_sixth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_10_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_sixth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_10_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 5);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_sixth(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Seventh function.
 ** ----------------------------------------------------------------- */

void
test_11_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 7 == ccpairs_seventh(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_11_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_seventh(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_11_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_seventh(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_11_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 6);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_seventh(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Eighth function.
 ** ----------------------------------------------------------------- */

void
test_12_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 8 == ccpairs_eighth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_12_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_eighth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_12_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_eighth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_12_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 7);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_eighth(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Nineth function.
 ** ----------------------------------------------------------------- */

void
test_13_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 9 == ccpairs_nineth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_13_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_nineth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_13_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_nineth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_13_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 8);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_nineth(L, P);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Tenth function.
 ** ----------------------------------------------------------------- */

void
test_14_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = make_list_len(L, 19);
    ccpairs_list_clean_handler_init(L, P_H, P);
    cctests_assert(L, 10 == ccpairs_tenth(L, P));
    cce_run_body_handlers(L);
  }
}

void
test_14_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_empty_list(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = NULL;
    ccpairs_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_14_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 1);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_14_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t		L[1];
  ccpairs_list_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (ccpairs_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    ccpairs_t	P = make_list_len(L, 9);
    ccpairs_list_clean_handler_init(L, P_H, P);
    ccpairs_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}


int
main (void)
{
  ccpairs_library_init();

  cctests_init("accessors");
  {
    cctests_begin_group("ref-pair function");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
      cctests_run(test_1_4);
    }
    cctests_end_group();

    cctests_begin_group("ref function");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
      cctests_run(test_2_4);
    }
    cctests_end_group();

    cctests_begin_group("last-pair function");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
      cctests_run(test_3_3);
      cctests_run(test_3_4);
    }
    cctests_end_group();

    cctests_begin_group("last function");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
      cctests_run(test_4_3);
      cctests_run(test_4_4);
    }
    cctests_end_group();

    cctests_begin_group("first function");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
    }
    cctests_end_group();

    cctests_begin_group("second function");
    {
      cctests_run(test_6_1);
      cctests_run(test_6_2);
      cctests_run(test_6_3);
    }
    cctests_end_group();

    cctests_begin_group("third function");
    {
      cctests_run(test_7_1);
      cctests_run(test_7_2);
      cctests_run(test_7_3);
      cctests_run(test_7_4);
    }
    cctests_end_group();

    cctests_begin_group("fourth function");
    {
      cctests_run(test_8_1);
      cctests_run(test_8_2);
      cctests_run(test_8_3);
      cctests_run(test_8_4);
    }
    cctests_end_group();

    cctests_begin_group("fifth function");
    {
      cctests_run(test_9_1);
      cctests_run(test_9_2);
      cctests_run(test_9_3);
      cctests_run(test_9_4);
    }
    cctests_end_group();

    cctests_begin_group("sixth function");
    {
      cctests_run(test_10_1);
      cctests_run(test_10_2);
      cctests_run(test_10_3);
      cctests_run(test_10_4);
    }
    cctests_end_group();

    cctests_begin_group("seventh function");
    {
      cctests_run(test_11_1);
      cctests_run(test_11_2);
      cctests_run(test_11_3);
      cctests_run(test_11_4);
    }
    cctests_end_group();

    cctests_begin_group("eighth function");
    {
      cctests_run(test_12_1);
      cctests_run(test_12_2);
      cctests_run(test_12_3);
      cctests_run(test_12_4);
    }
    cctests_end_group();

    cctests_begin_group("nineth function");
    {
      cctests_run(test_13_1);
      cctests_run(test_13_2);
      cctests_run(test_13_3);
      cctests_run(test_13_4);
    }
    cctests_end_group();

    cctests_begin_group("tenth function");
    {
      cctests_run(test_14_1);
      cctests_run(test_14_2);
      cctests_run(test_14_3);
      cctests_run(test_14_4);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
