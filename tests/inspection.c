/*
  Part of: CCPairs
  Contents: test for inspection functions
  Date: Nov  9, 2017

  Abstract

  Test file for inspection functions.

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

__attribute__((__nonnull__(1)))
static void print_list (FILE * stream, ccpair_t P);

__attribute__((__nonnull__(1)))
static void print_list_len (FILE * stream, ccpair_t P, ccpair_idx_t idx);

ccpair_t
make_list_len (cce_destination_t upper_L, size_t len)
{
  if (len) {
    cce_location_t		L[1];
    ccpair_t			P[1+len];
    cce_handler_t		P_H[len];

    for (size_t i=0; i<1+len; ++i) {
      P[i] = NULL;
    }

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      cce_run_error_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (size_t i = len-1; i > 0; --i) {
	if (0) { fprintf(stderr, "%s: i=%lu len=%lu\n", __func__, i, len); }
	P[i] = ccpair_cons(L, 1+i, P[1+i]);
	if (0) {
	  fprintf(stderr, "%s: P[%lu]=%p, car(P[%lu])=%lu, cdr(P[%lu])=%p\n", __func__,
		  i, (void *)(P[i]),
		  i, ccpair_car(P[i]),
		  i, (void *)ccpair_cdr(P[i]) );
	}
	ccpair_error_handler_pair_init(L, &(P_H[i]), P[i]);
      }
      P[0] = ccpair_cons(L, 1, P[1]);
      if (0) {
	fprintf(stderr, "%s: P[0]=%p, car(P[0])=%lu, cdr(P[0])=%p\n", __func__,
		(void *)(P[0]), ccpair_car(P[0]), (void *)ccpair_cdr(P[0]));
      }
      cce_run_cleanup_handlers(L);
      if (0) { fprintf(stderr, "%s: returning P[0]=%p)\n", __func__, (void *)(P[0])); }
      if (0) { print_list(stderr, P[0]); }
      return P[0];
    }
  } else {
    return NULL;
  }
}

void
print_list (FILE * stream, ccpair_t P)
{
  fprintf(stream, "(");
  for (; P; P = ccpair_cdr(P)) {
    fprintf(stream, "%lu", ccpair_car(P));
    if (! ccpair_is_last(P)) {
      fprintf(stream, " ");
    }
  }
  fprintf(stream, ")\n");
}

void
print_list_len (FILE * stream, ccpair_t P, ccpair_idx_t idx)
{
  fprintf(stream, "(");
  for (ccpair_idx_t i = 0; P && (i < idx); P = ccpair_cdr(P), ++i) {
    fprintf(stream, "%lu", ccpair_car(P));
    if (! ccpair_is_last(P)) {
      fprintf(stream, " ");
    }
  }
  fprintf(stream, " ...)\n");
}

void
print_spine_len (FILE * stream, ccpair_t P, ccpair_idx_t idx)
{
  for (ccpair_idx_t i = 0; (i < idx) && P; ++i, P = ccpair_cdr(P)) {
    fprintf(stream, "P[%lu]=%p, car(P[%lu])=%lu, cdr(P[%lu])=%p\n",
	    i, (void *)(P),
	    i, ccpair_car(P),
	    i, (void *)ccpair_cdr(P));
  }
}


/** --------------------------------------------------------------------
 ** Length function.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Empty list. */
{
  ccpair_t	P = NULL;
  cctests_assert(0 == ccpair_length(upper_L, P));
}

void
test_1_2 (cce_destination_t upper_L)
/* One item list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, 1 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Five items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_list(stderr, P); }
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_length(L, P)); }
    cctests_assert(L, 5 == ccpair_length(L, P));
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
    if (0) { print_list(stderr, P); }
    if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_length(L, P)); }
    cctests_assert(L, 1024 == ccpair_length(L, P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_5 (cce_destination_t upper_L)
/* Circular list with one item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_circular_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    /* Close the loop making the list  circular.  The cdr of the pair is
       the pair itself. */
    {
      P->D = (uintptr_t)P;
    }
    ccpair_length(L, P);
    /* If  we are  still  here: "ccpair_length()"  failed  to deted  the
       circular list, this is an error. */
    cctests_raise_unreachable(L);
  }
}

void
test_1_6 (cce_destination_t upper_L)
/* Circular list with 10 items, loop closing at the 5th item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_circular_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 5);
      P_last->D = (uintptr_t) P_loop_end;
    }
    ccpair_length(L, P);
    /* If  we are  still  here: "ccpair_length()"  failed  to deted  the
       circular list, this is an error. */
    cctests_raise_unreachable(L);
  }
}

void
test_1_7 (cce_destination_t upper_L)
/* Circular list with 10 items, loop closing at the 6th item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (ccpair_condition_is_circular_list(cce_condition(L))) {
      cce_run_error_handlers_final(L);
    } else {
      cce_run_error_handlers_raise(L, upper_L);
    }
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 6);
      P_last->D = (uintptr_t) P_loop_end;
    }
    ccpair_length(L, P);
    /* If  we are  still  here: "ccpair_length()"  failed  to deted  the
       circular list, this is an error. */
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-null function.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t L CCE_UNUSED)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  cctests_assert(true == ccpair_is_null(P));
}

void
test_2_2 (cce_destination_t upper_L)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, false == ccpair_is_null(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-empty function.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t L CCE_UNUSED)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  cctests_assert(true == ccpair_is_empty(P));
}

void
test_3_2 (cce_destination_t upper_L)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, false == ccpair_is_empty(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-last-pair function.
 ** ----------------------------------------------------------------- */

void
test_4_1 (cce_destination_t L CCE_UNUSED)
/* Empty list. */
{
  ccpair_t		P;

  P = NULL;
  cctests_assert(false == ccpair_is_last(P));
}

void
test_4_2 (cce_destination_t upper_L)
/* Single pair list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, true == ccpair_is_last(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-circular function.
 ** ----------------------------------------------------------------- */

void
test_5_1 (cce_destination_t upper_L CCE_UNUSED)
/* Empty list. */
{
  ccpair_t	P = NULL;
  cctests_assert(false == ccpair_is_circular(P));
}

void
test_5_2 (cce_destination_t upper_L)
/* Linear one item list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    cctests_assert(L, false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_3 (cce_destination_t upper_L)
/* Linear five items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_spine_len(stderr, P, 5); }
    if (0) { fprintf(stderr, "%s: length=%lu\n", __func__, ccpair_length(L, P)); }
    if (0) { print_list_len(stderr, P, 5); }
    if (0) { fprintf(stderr, "%s: %d\n", __func__, ccpair_is_circular(P)); }
    cctests_assert(L, false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_4 (cce_destination_t upper_L)
/* Linear 1024 items list. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    ccpair_t	P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    cctests_assert(L, false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_5 (cce_destination_t upper_L)
/* Circular list with one item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = ccpair_cons(L, 1, NULL);
    /* Close the loop making the list  circular.  The cdr of the pair is
       the pair itself. */
    {
      P->D = (uintptr_t)P;
    }
    cctests_assert(L, true == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_6 (cce_destination_t upper_L)
/* Circular list with 10 items, loop closing at the 5th item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 5);
      P_last->D = (uintptr_t) P_loop_end;
    }
    cctests_assert(L, true == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_7 (cce_destination_t upper_L)
/* Circular list with 10 items, loop closing at the 6th item. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_error_handlers_raise(L, upper_L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    ccpair_t	P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 6);
      P_last->D = (uintptr_t) P_loop_end;
    }
    cctests_assert(L, true == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}


int
main (void)
{
  ccpair_init();

  cctests_init("inspection");
  {
    cctests_begin_group("length function");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
      cctests_run(test_1_4);
      cctests_run(test_1_5);
      cctests_run(test_1_6);
      cctests_run(test_1_7);
    }
    cctests_end_group();

    cctests_begin_group("is-null function");
    {
      cctests_run(test_2_1);
      cctests_run(test_2_2);
    }
    cctests_end_group();

    cctests_begin_group("is-empty function");
    {
      cctests_run(test_3_1);
      cctests_run(test_3_2);
    }
    cctests_end_group();

    cctests_begin_group("is-last function");
    {
      cctests_run(test_4_1);
      cctests_run(test_4_2);
    }
    cctests_end_group();

    cctests_begin_group("is-circular function");
    {
      cctests_run(test_5_1);
      cctests_run(test_5_2);
      cctests_run(test_5_3);
      cctests_run(test_5_4);
      cctests_run(test_5_5);
      cctests_run(test_5_6);
      cctests_run(test_5_7);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
