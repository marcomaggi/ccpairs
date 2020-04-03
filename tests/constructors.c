/*
  Part of: CCPairs
  Contents: tests for constructor functions
  Date: Nov 24, 2017

  Abstract

	Test file for constructor functions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <marco.maggi-ipsu@poste.it>

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

CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
void print_list (FILE * stream, ccpairs_t P);

CCLIB_FUNC_ATTRIBUTE_NONNULL(1)
void print_list_len (FILE * stream, ccpairs_t P, ccpairs_idx_t idx);

ccpairs_t
make_list_len (cce_destination_t upper_L, size_t len)
{
  if (len) {
    cce_location_t		L[1];
    ccpairs_t			P[1+len];
    ccpairs_pair_error_handler_t	P_H[len];

    for (size_t i=0; i<1+len; ++i) {
      P[i] = NULL;
    }

    if (cce_location(L)) {
      fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
      cce_run_catch_handlers_raise(L, upper_L);
    } else {
      P[len] = NULL;
      for (size_t i = len-1; i > 0; --i) {
	if (0) { fprintf(stderr, "%s: i=%lu len=%lu\n", __func__, i, len); }
	P[i] = ccpairs_cons_guarded(L, &(P_H[i]), 1+i, P[1+i]);
	if (0) {
	  fprintf(stderr, "%s: P[%lu]=%p, car(P[%lu])=%lu, cdr(P[%lu])=%p\n", __func__,
		  i, (void *)(P[i]),
		  i, ccpairs_car(P[i]),
		  i, (void *)ccpairs_cdr(P[i]) );
	}
      }
      P[0] = ccpairs_cons(L, 1, P[1]);
      if (0) {
	fprintf(stderr, "%s: P[0]=%p, car(P[0])=%lu, cdr(P[0])=%p\n", __func__,
		(void *)(P[0]), ccpairs_car(P[0]), (void *)ccpairs_cdr(P[0]));
      }
      cce_run_body_handlers(L);
      if (0) { fprintf(stderr, "%s: returning P[0]=%p)\n", __func__, (void *)(P[0])); }
      if (0) { print_list(stderr, P[0]); }
      return P[0];
    }
  } else {
    return NULL;
  }
}

void
print_list (FILE * stream, ccpairs_t P)
{
  fprintf(stream, "(");
  for (; NULL != P; P = ccpairs_cdr(P)) {
    fprintf(stream, "%lu", ccpairs_car(P));
    if (! ccpairs_is_last(P)) {
      fprintf(stream, " ");
    }
  }
  fprintf(stream, ")\n");
}

void
print_list_len (FILE * stream, ccpairs_t P, ccpairs_idx_t idx)
{
  fprintf(stream, "(");
  for (ccpairs_idx_t i = 0; P && (i < idx); P = ccpairs_cdr(P), ++i) {
    fprintf(stream, "%lu", ccpairs_car(P));
    if (! ccpairs_is_last(P)) {
      fprintf(stream, " ");
    }
  }
  fprintf(stream, " ...)\n");
}

void
print_spine_len (FILE * stream, ccpairs_t P, ccpairs_idx_t idx)
{
  for (ccpairs_idx_t i = 0; (i < idx) && P; ++i, P = ccpairs_cdr(P)) {
    fprintf(stream, "P[%lu]=%p, car(P[%lu])=%lu, cdr(P[%lu])=%p\n",
	    i, (void *)(P),
	    i, ccpairs_car(P),
	    i, (void *)ccpairs_cdr(P));
  }
}


/** --------------------------------------------------------------------
 ** Constructor and destructor flags.
 ** ----------------------------------------------------------------- */

typedef enum item_state_t {
  TEST_VOID,
  TEST_CONSTRUCTED,
  TEST_DESTRUCTED,
} item_state_t;

#define ITEM_STATE_NUMBER		9
static item_state_t item_state[ITEM_STATE_NUMBER];

void
item_state_init (void)
{
  for (int i=0; i<ITEM_STATE_NUMBER; ++i) {
    item_state[i] = TEST_VOID;
  }
}

/* ------------------------------------------------------------------ */

void
item_state_set_constructed (int i)
{
  item_state[i] = TEST_CONSTRUCTED;
}

void
item_state_set_destructed (int i)
{
  item_state[i] = TEST_DESTRUCTED;
}

/* ------------------------------------------------------------------ */

bool
item_state_is_constructed (int i)
{
  return ((TEST_CONSTRUCTED == item_state[i])? true : false);
}

bool
item_state_is_destructed (int i)
{
  return ((TEST_DESTRUCTED == item_state[i])? true : false);
}


/** --------------------------------------------------------------------
 ** Simple item constructors and destructors.
 ** ----------------------------------------------------------------- */

void
simple_item_destructor__noop (uintptr_t item)
/* This is  to be used when  building lists of integers  stored directly
   into "uintptr_t" values. */
{
  if (0) { fprintf(stderr, "%s: item destructed %lu\n", __func__, item); }
  item_state_set_destructed(item);
}

/* ------------------------------------------------------------------ */

uintptr_t
simple_item_constructor__break_immediately (cce_destination_t L, ccpairs_idx_t idx CCLIB_UNUSED)
{
  cce_raise(L, cce_condition_new_break());
}

uintptr_t
simple_item_constructor__one_integer_item (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 1:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
simple_item_constructor__three_integer_items (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 3:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

/* ------------------------------------------------------------------ */

uintptr_t
simple_item_constructor__exception_at_0 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
simple_item_constructor__exception_at_1 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 1:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
simple_item_constructor__exception_at_2 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 2:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
simple_item_constructor__exception_at_3 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 3:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
simple_item_constructor__exception_at_4 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
  case 3:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 4:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}


/** --------------------------------------------------------------------
 ** Async item constructors and destructors.
 ** ----------------------------------------------------------------- */

/* An async item is an asynchronous  resource that must be allocated and
   released. */
typedef struct data_t {
  uintptr_t	N;
} data_t;

data_t *
data_constructor (cce_destination_t L, uintptr_t N)
{
  data_t *	data = cce_sys_malloc(L, sizeof(data_t));
  data->N = N;
  if (0) { fprintf(stderr, "%s: item constructed %p, N=%lu\n", __func__, (void *)data, data->N); }
  return data;
}

void
data_destructor (data_t * data)
{
  if (0) { fprintf(stderr, "%s: item destructed %p, N=%lu\n", __func__, (void *)data, data->N); }
  item_state_set_destructed(data->N);
  free(data);
}

/* ------------------------------------------------------------------ */

uintptr_t
async_item_constructor (cce_destination_t L, uintptr_t N)
{
  uintptr_t	item = (uintptr_t)data_constructor(L, N);
  return item;
}

void
async_item_destructor (uintptr_t item)
{
  data_t *	data = (data_t *)item;
  data_destructor(data);
}

uintptr_t
async_item_ref (uintptr_t item)
{
  data_t *	data = (data_t *) item;
  return data->N;
}

void
print_data_list (FILE * stream, ccpairs_t P)
{
  fprintf(stream, "(");
  for (; NULL != P; P = ccpairs_cdr(P)) {
    fprintf(stream, "%lu", async_item_ref(ccpairs_car(P)));
    if (! ccpairs_is_last(P)) {
      fprintf(stream, " ");
    }
  }
  fprintf(stream, ")\n");
}

/* ------------------------------------------------------------------ */

uintptr_t
async_item_constructor__break_immediately (cce_destination_t L, ccpairs_idx_t idx CCLIB_UNUSED)
{
  cce_raise(L, cce_condition_new_break());
}

uintptr_t
async_item_constructor__one_integer_item (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 1:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
async_item_constructor__three_integer_items (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 3:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

/* ------------------------------------------------------------------ */

uintptr_t
async_item_constructor__exception_at_0 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
async_item_constructor__exception_at_1 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 1:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
async_item_constructor__exception_at_2 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 2:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
async_item_constructor__exception_at_3 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 3:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}

uintptr_t
async_item_constructor__exception_at_4 (cce_destination_t L, ccpairs_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
  case 3: {
    uintptr_t	item = async_item_constructor(L, idx);
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return item;
  }
  case 4:
    cce_raise(L, cctests_condition_new_signal_1());
  default:
    cce_raise(L, cce_condition_new_logic_error());
  }
}


/** --------------------------------------------------------------------
 ** List function: lists of simple items.
 ** ----------------------------------------------------------------- */

void
test_1_1 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  an empty  list.  The  item constructor
   function must raise  a break exception immediately.  There  is a noop
   item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_list(L, simple_item_constructor__break_immediately, simple_item_destructor__noop);
    cctests_assert(L, 0 == ccpairs_length(L, P));
    if (0) { print_list(stderr, P); }
    cce_run_body_handlers(L);
  }
}

void
test_1_2 (cce_destination_t upper_L)
/* Use "ccpairs_list()" to  build a list of integers with  one item.  The
   item constructor function must raise a break exception when the index
   operand is 1.  There is a noop item destructor function. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, simple_item_constructor__one_integer_item, simple_item_destructor__noop);
    cctests_assert(L, 1 == ccpairs_length(L, P));
    cctests_assert(L, 0 == ccpairs_car(P));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, false == item_state_is_constructed(1));
    if (0) { print_list(stderr, P); }
    cce_run_body_handlers(L);
  }
}

void
test_1_3 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item constructor  function must raise a break  exception when the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, simple_item_constructor__three_integer_items, simple_item_destructor__noop);
    cctests_assert(L, 3 == ccpairs_length(L, P));
    cctests_assert(L, 0 == ccpairs_car(P));
    cctests_assert(L, 1 == ccpairs_ref(L, P, 1));
    cctests_assert(L, 2 == ccpairs_ref(L, P, 2));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, true  == item_state_is_constructed(1));
    cctests_assert(L, true  == item_state_is_constructed(2));
    cctests_assert(L, false == item_state_is_constructed(3));
    if (0) { print_list(stderr, P); }
    cce_run_body_handlers(L);
  }
}

void
test_1_4 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item  constructor function raises  a signal_1 exception  when the
   index operand is 0.  There is a noop item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    item_state_init();
    ccpairs_list(L, simple_item_constructor__exception_at_0, simple_item_destructor__noop);
    cce_raise(L, cctests_condition_new_failure());
  }
}

void
test_1_5 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item  constructor function raises  a signal_1 exception  when the
   index operand is 1.  There is a noop item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
  } else {
    item_state_init();
    ccpairs_list(L, simple_item_constructor__exception_at_1, simple_item_destructor__noop);
    cce_raise(L, cctests_condition_new_failure());
  }
}

void
test_1_6 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item  constructor function raises  a signal_1 exception  when the
   index operand is 2.  There is a noop item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
  } else {
    item_state_init();
    ccpairs_list(L, simple_item_constructor__exception_at_2, simple_item_destructor__noop);
    cce_raise(L, cctests_condition_new_failure());
  }
}

void
test_1_7 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item  constructor function raises  a signal_1 exception  when the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
    cctests_assert(upper_L, true == item_state_is_destructed(2));
  } else {
    item_state_init();
    ccpairs_list(L, simple_item_constructor__exception_at_3, simple_item_destructor__noop);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** List function: lists of items as asynchronous resources.
 ** ----------------------------------------------------------------- */

void
test_2_1 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  an empty  list.  The  item constructor
   function must raise  a break exception immediately.  There  is a noop
   item destructor function. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_list(L, async_item_constructor__break_immediately, async_item_destructor);
    cctests_assert(L, 0 == ccpairs_length(L, P));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
}

void
test_2_2 (cce_destination_t upper_L)
/* Use "ccpairs_list()" to  build a list of integers with  one item.  The
   item constructor function must raise a break exception when the index
   operand is 1. */
{
  cce_location_t		L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, async_item_constructor__one_integer_item, async_item_destructor);
    cctests_assert(L, 1 == ccpairs_length(L, P));
    cctests_assert(L, 0 == async_item_ref(ccpairs_car(P)));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, false == item_state_is_constructed(1));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
  cctests_assert(upper_L, true  == item_state_is_destructed(0));
}

void
test_2_3 (cce_destination_t upper_L)
/* Use "ccpairs_list()"  to build  a list of  integers with  three items.
   The item constructor  function must raise a break  exception when the
   index operand is 3. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, async_item_constructor__three_integer_items, async_item_destructor);
    cctests_assert(L, 3 == ccpairs_length(L, P));
    cctests_assert(L, 0 == async_item_ref(ccpairs_car(P)));
    cctests_assert(L, 1 == async_item_ref(ccpairs_ref(L, P, 1)));
    cctests_assert(L, 2 == async_item_ref(ccpairs_ref(L, P, 2)));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, true  == item_state_is_constructed(1));
    cctests_assert(L, true  == item_state_is_constructed(2));
    cctests_assert(L, false == item_state_is_constructed(3));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
  cctests_assert(upper_L, true  == item_state_is_destructed(0));
  cctests_assert(upper_L, true  == item_state_is_destructed(1));
  cctests_assert(upper_L, true  == item_state_is_destructed(2));
}

void
test_2_4 (cce_destination_t upper_L)
/* Use  "ccpairs_list()"  to   build  a  list  of   integers.   The  item
   constructor  function  raises a  signal_1  exception  when the  index
   operand is 0. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    item_state_init();
    ccpairs_list(L, async_item_constructor__exception_at_0, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_2_5 (cce_destination_t upper_L)
/* Use  "ccpairs_list()"  to   build  a  list  of   integers.   The  item
   constructor  function  raises a  signal_1  exception  when the  index
   operand is 1. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
  } else {
    item_state_init();
    ccpairs_list(L, async_item_constructor__exception_at_1, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_2_6 (cce_destination_t upper_L)
/* Use  "ccpairs_list()"  to   build  a  list  of   integers.   The  item
   constructor  function  raises a  signal_1  exception  when the  index
   operand is 2. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
  } else {
    item_state_init();
    ccpairs_list(L, async_item_constructor__exception_at_2, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_2_7 (cce_destination_t upper_L)
/* Use  "ccpairs_list()"  to   build  a  list  of   integers.   The  item
   constructor  function  raises a  signal_1  exception  when the  index
   operand is 3. */
{
  cce_location_t	L[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
    cctests_assert(upper_L, true == item_state_is_destructed(2));
  } else {
    item_state_init();
    ccpairs_list(L, async_item_constructor__exception_at_3, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}


/** --------------------------------------------------------------------
 ** List function: lists of items as asynchronous resources, clean handler.
 ** ----------------------------------------------------------------- */

void
test_3_1 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()" to build an empty list.  The item
   constructor function must raise a break exception immediately.  There
   is a noop item destructor function. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    ccpairs_t	P = ccpairs_list_guarded_clean(L, P_H, async_item_constructor__break_immediately, async_item_destructor);
    cctests_assert(L, 0 == ccpairs_length(L, P));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
}

void
test_3_2 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()"  to build  a list of  "data_t" with
   one item.  The item constructor function must raise a break exception
   when the index operand is 1. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, async_item_constructor__one_integer_item, async_item_destructor);
    cctests_assert(L, 1 == ccpairs_length(L, P));
    cctests_assert(L, 0 == async_item_ref(ccpairs_car(P)));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, false == item_state_is_constructed(1));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
  cctests_assert(upper_L, true  == item_state_is_destructed(0));
}

void
test_3_3 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()"  to build  a list of  "data_t" with
   three  items.   The item  constructor  function  must raise  a  break
   exception when the index operand is 3. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    cce_run_catch_handlers_raise(L, upper_L);
  } else {
    item_state_init();
    ccpairs_t	P = ccpairs_list_guarded(L, P_H, async_item_constructor__three_integer_items, async_item_destructor);
    cctests_assert(L, 3 == ccpairs_length(L, P));
    cctests_assert(L, 0 == async_item_ref(ccpairs_car(P)));
    cctests_assert(L, 1 == async_item_ref(ccpairs_ref(L, P, 1)));
    cctests_assert(L, 2 == async_item_ref(ccpairs_ref(L, P, 2)));
    cctests_assert(L, true  == item_state_is_constructed(0));
    cctests_assert(L, true  == item_state_is_constructed(1));
    cctests_assert(L, true  == item_state_is_constructed(2));
    cctests_assert(L, false == item_state_is_constructed(3));
    if (0) { print_data_list(stderr, P); }
    cce_run_body_handlers(L);
  }
  cctests_assert(upper_L, true  == item_state_is_destructed(0));
  cctests_assert(upper_L, true  == item_state_is_destructed(1));
  cctests_assert(upper_L, true  == item_state_is_destructed(2));
}

void
test_3_4 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean_()" to build  a list of "data_t".  The
   item constructor function raises a  signal_1 exception when the index
   operand is 0. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
  } else {
    item_state_init();
    ccpairs_list_guarded(L, P_H, async_item_constructor__exception_at_0, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_3_5 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()"  to build a list  of "data_t".  The
   item constructor function raises a  signal_1 exception when the index
   operand is 1. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
  } else {
    item_state_init();
    ccpairs_list_guarded(L, P_H, async_item_constructor__exception_at_1, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_3_6 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()"  to build a list  of "data_t".  The
   item constructor function raises a  signal_1 exception when the index
   operand is 2. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
  } else {
    item_state_init();
    ccpairs_list_guarded(L, P_H, async_item_constructor__exception_at_2, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}

void
test_3_7 (cce_destination_t upper_L)
/* Use "ccpairs_list_guarded_clean()"  to build a list  of "data_t".  The
   item constructor function raises a  signal_1 exception when the index
   operand is 3. */
{
  cce_location_t			L[1];
  ccpairs_list_item_clean_handler_t	P_H[1];

  if (cce_location(L)) {
    if (cctests_condition_is_signal_1(cce_condition(L))) {
      cce_run_catch_handlers_final(L);
    } else {
      cce_run_catch_handlers_raise(L, upper_L);
    }
    cctests_assert(upper_L, true == item_state_is_destructed(0));
    cctests_assert(upper_L, true == item_state_is_destructed(1));
    cctests_assert(upper_L, true == item_state_is_destructed(2));
  } else {
    item_state_init();
    ccpairs_list_guarded(L, P_H, async_item_constructor__exception_at_3, async_item_destructor);
    cctests_raise_unreachable(L);
  }
}


int
main (void)
{
  ccpairs_library_init();

  cctests_init("constructors");
  {
    cctests_begin_group("list");
    {
      cctests_run(test_1_1);
      cctests_run(test_1_2);
      cctests_run(test_1_3);
      cctests_run(test_1_4);
      cctests_run(test_1_5);
      cctests_run(test_1_6);
      cctests_run(test_1_7);

      cctests_run(test_2_1);
      cctests_run(test_2_2);
      cctests_run(test_2_3);
      cctests_run(test_2_4);
      cctests_run(test_2_5);
      cctests_run(test_2_6);
      cctests_run(test_2_7);

      cctests_run(test_3_1);
      cctests_run(test_3_2);
      cctests_run(test_3_3);
      cctests_run(test_3_4);
      cctests_run(test_3_5);
      cctests_run(test_3_6);
      cctests_run(test_3_7);
    }
    cctests_end_group();
  }
  cctests_final();
}

/* end of file */
