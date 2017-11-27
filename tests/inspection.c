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

__attribute__((__nonnull__(1)))
static void print_list (FILE * stream, ccpair_t P);

__attribute__((__nonnull__(1)))
static void print_list_len (FILE * stream, ccpair_t P, ccpair_idx_t idx);

ccpair_t
make_list_len (cce_location_t * upper_L, size_t len)
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
test_1_1 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_list(stderr, P); }
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_list(stderr, P); }
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
  bool			circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = ccpair_cons(L, 1, NULL);
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
  if (0) { fprintf(stderr, "%s: enter\n", __func__); }
  cce_location_t	L[1];
  ccpair_t		P;
  bool volatile		circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = make_list_len(L, 10);
    if (0) { fprintf(stderr, "%s: P=%p\n", __func__, (void *)P); }
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
  bool volatile		circular = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); };
    assert(ccpair_condition_is_circular_list(cce_condition(L)));
    circular = true;
    cce_run_error_handlers_final(L);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = make_list_len(L, 10);
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
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
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(true == ccpair_is_last(P));
    cce_run_cleanup_handlers(L);
  }
}


/** --------------------------------------------------------------------
 ** Is-circular function.
 ** ----------------------------------------------------------------- */

void
test_5_1 (void)
/* Empty list. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = NULL;
    assert(false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_2 (void)
/* Linear one item list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = ccpair_cons(L, 1, NULL);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_3 (void)
/* Linear five items list. */
{
  if (0) { fprintf(stderr, "%s: enter\n", __func__); }
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = make_list_len(L, 5);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { print_spine_len(stderr, P, 5); }
    if (0) { fprintf(stderr, "%s: length=%lu\n", __func__, ccpair_length(L, P)); }
    if (0) { print_list_len(stderr, P, 5); }
    if (0) { fprintf(stderr, "%s: %d\n", __func__, ccpair_is_circular(P)); }
    assert(false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_4 (void)
/* Linear 1024 items list. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = make_list_len(L, 1024);
    ccpair_cleanup_handler_list_init(L, P_H, P);
    if (0) { fprintf(stderr, "%s: %d\n", __func__, ccpair_is_circular(P)); }
    assert(false == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_5 (void)
/* Circular list with one item. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = ccpair_cons(L, 1, NULL);
    /* Close the loop making the list  circular.  The cdr of the pair is
       the pair itself. */
    {
      P->D = (uintptr_t)P;
    }
    assert(true == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_6 (void)
/* Circular list with 10 items, loop closing at the 5th item. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 5);
      P_last->D = (uintptr_t) P_loop_end;
    }
    assert(true == ccpair_is_circular(P));
    cce_run_cleanup_handlers(L);
  }
}

void
test_5_7 (void)
/* Circular list with 10 items, loop closing at the 6th item. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    /* This is  a circular list,  so we do  not release its  memory: the
       free  function is  incapable of  correctly releasing  it.  (Marco
       Maggi; Nov 13, 2017) */
    P = make_list_len(L, 10);
    /* Close a loop making the list circular. */
    {
      ccpair_t	P_last		= ccpair_last_pair(L, P);
      ccpair_t	P_loop_end	= ccpair_ref_pair(L, P, 6);
      P_last->D = (uintptr_t) P_loop_end;
    }
    assert(true == ccpair_is_circular(P));
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

  /* Is-circular function */
  if (1) { test_5_1(); }
  if (1) { test_5_2(); }
  if (1) { test_5_3(); }
  if (1) { test_5_4(); }
  if (1) { test_5_5(); }
  if (1) { test_5_6(); }
  if (1) { test_5_7(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
