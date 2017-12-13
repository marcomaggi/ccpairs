/*
  Part of: CCPairs
  Contents: tests for accessor functions
  Date: Nov  9, 2017

  Abstract

	Test file for accessors functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

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

ccpair_t
make_list_len (cce_location_t * upper_L, size_t len)
{
  if (len) {
    cce_location_t		L[1];
    ccpair_t			P[1+len];
    cce_handler_t		P_H[len];

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      cce_run_error_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (size_t i = len-1; i > 0; --i) {
	if (0) { fprintf(stderr, "%s: i=%lu len=%lu\n", __func__, i, len); }
	P[i] = ccpair_cons(L, 1+i, P[1+i]);
	if (0) { fprintf(stderr, "%s: P[%lu]=%p\n", __func__, i, (void *)(P[i])); }
	ccpair_error_handler_pair_init(L, &(P_H[i]), P[i]);
      }
      P[0] = ccpair_cons(L, 1, P[1]);
      if (0) { fprintf(stderr, "%s: P[%u]=%p\n", __func__, 0, (void *)(P[0])); }
      cce_run_cleanup_handlers(L);
      if (0) { fprintf(stderr, "%s: returning P[0]=%p\n", __func__, (void *)(P[0])); }
      return P[0];
    }
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
test_1_1 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_ref_pair(L, P, 1);
    cctests_raise_unreachable(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, P == ccpair_ref_pair(L, P, 0));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 4 == ccpair_car(ccpair_ref_pair(L, P, 3)));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 1000 == ccpair_car(ccpair_ref_pair(L, P, 999)));
    cce_run_cleanup_handlers(L);
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
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_ref(L, P, 1);
    cctests_raise_unreachable(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, 1 == ccpair_ref(L, P, 0));
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 4 == ccpair_ref(L, P, 3));
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 1000 == ccpair_ref(L, P, 999));
    cce_run_cleanup_handlers(L);
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
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_last_pair(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, P == ccpair_last_pair(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_3_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 5 == ccpair_car(ccpair_last_pair(L, P)));
    cce_run_cleanup_handlers(L);
  }
}

void
test_3_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 1024 == ccpair_car(ccpair_last_pair(L, P)));
    cce_run_cleanup_handlers(L);
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
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_last(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_4_2 (cce_destination_t upper_L)
/* One item list, ref pair 0. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, 1 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_4_3 (cce_destination_t upper_L)
/* Five items list, success. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 5 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_4_4 (cce_destination_t upper_L)
/* 1024 items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 1024 == ccpair_last(L, P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** First function.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L)
/* Successful retrieval. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 1 == ccpair_first(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_first(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 2 == ccpair_second(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_6_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_second(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_6_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_second(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 3 == ccpair_third(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_7_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_third(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_7_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_third(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_7_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 2);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_third(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 4 == ccpair_fourth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_8_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_fourth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_8_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_fourth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_8_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 3);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_fourth(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 5 == ccpair_fifth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_9_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_fifth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_9_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_fifth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_9_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 4);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_fifth(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 6 == ccpair_sixth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_10_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_sixth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_10_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_sixth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_10_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_sixth(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 7 == ccpair_seventh(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_11_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_seventh(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_11_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_seventh(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_11_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 6);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_seventh(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 8 == ccpair_eighth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_12_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_eighth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_12_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_eighth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_12_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 7);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_eighth(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 9 == ccpair_nineth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_13_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_nineth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_13_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_nineth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_13_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 8);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_nineth(L, P);
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
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 19);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, 10 == ccpair_tenth(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_14_2 (cce_destination_t upper_L)
/* Empty list, "empty list" exception. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_empty_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = NULL;
    ccpair_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_14_3 (cce_destination_t upper_L)
/* Not enough items in list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 1);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}

void
test_14_4 (cce_destination_t upper_L)
/* Not enough items in list: one item short. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_not_enough_items(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    ccpair_t	P = make_list_len(L, 9);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    ccpair_tenth(L, P);
    cctests_raise_unreachable(L);
  }
}


int
main (void)
{
  ccpair_init();

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
