/*
  Part of: CCPairs
  Contents: tests for constructor functions
  Date: Nov 24, 2017

  Abstract

	Test file for constructor functions.

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
void print_list (FILE * stream, ccpair_t P);

__attribute__((__nonnull__(1)))
void print_list_len (FILE * stream, ccpair_t P, ccpair_idx_t idx);

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
  for (; NULL != P; P = ccpair_cdr(P)) {
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
simple_item_constructor__break_immediately (cce_destination_t L, ccpair_idx_t idx CCPAIR_UNUSED)
{
  cce_raise(L, cce_condition_new_break());
}

uintptr_t
simple_item_constructor__one_integer_item (cce_destination_t L, ccpair_idx_t idx)
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
    assert(0);
  }
}

uintptr_t
simple_item_constructor__three_integer_items (cce_destination_t L, ccpair_idx_t idx)
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
    assert(0);
  }
}

/* ------------------------------------------------------------------ */

uintptr_t
simple_item_constructor__exception_at_0 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
simple_item_constructor__exception_at_1 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 1:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
simple_item_constructor__exception_at_2 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 2:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
simple_item_constructor__exception_at_3 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return idx;
  case 3:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
simple_item_constructor__exception_at_4 (cce_destination_t L, ccpair_idx_t idx)
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
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}


/** --------------------------------------------------------------------
 ** Async item constructors and destructors.
 ** ----------------------------------------------------------------- */

typedef struct async_item_t {
  uintptr_t	N;
} async_item_t;

uintptr_t
async_item_ref (uintptr_t _item)
{
  async_item_t *	item = (async_item_t *) _item;
  return item->N;
}

/* ------------------------------------------------------------------ */

void
async_item_destructor__noop (uintptr_t _item)
/* This is  to be used when  building lists of integers  stored directly
   into "uintptr_t" values. */
{
  async_item_t *	item = (async_item_t *)_item;
  if (0) { fprintf(stderr, "%s: item destructed %lu\n", __func__, item->N); }
  item_state_set_destructed(item->N);
}

/* ------------------------------------------------------------------ */

uintptr_t
async_item_constructor__break_immediately (cce_destination_t L, ccpair_idx_t idx CCPAIR_UNUSED)
{
  cce_raise(L, cce_condition_new_break());
}

uintptr_t
async_item_constructor__one_integer_item (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 1:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    assert(0);
  }
}

uintptr_t
async_item_constructor__three_integer_items (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 3:
    cce_raise(L, cce_condition_new_break());
    break;
  default:
    assert(0);
  }
}

/* ------------------------------------------------------------------ */

uintptr_t
async_item_constructor__exception_at_0 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
async_item_constructor__exception_at_1 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 1:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
async_item_constructor__exception_at_2 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 2:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
async_item_constructor__exception_at_3 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 3:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}

uintptr_t
async_item_constructor__exception_at_4 (cce_destination_t L, ccpair_idx_t idx)
{
  switch (idx) {
  case 0:
  case 1:
  case 2:
  case 3: {
    async_item_t *	item = malloc(sizeof(async_item_t));
    item->N = idx;
    if (0) { fprintf(stderr, "%s: item constructed %lu\n", __func__, idx); }
    item_state_set_constructed(idx);
    return (uintptr_t)item;
  }
  case 4:
    cce_raise(L, cce_condition_new_error());
  default:
    assert(0);
  }
}


/** --------------------------------------------------------------------
 ** List function: lists of simple items.
 ** ----------------------------------------------------------------- */

void
test_1_1 (void)
/* Use "ccpair_list()"  to build  an empty  list.  The  item constructor
   function must raise  a break exception immediately.  There  is a noop
   item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = ccpair_list(L, simple_item_constructor__break_immediately, simple_item_destructor__noop);
    assert(0 == ccpair_length(L, P));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_2 (void)
/* Use "ccpair_list()" to  build a list of integers with  one item.  The
   item constructor function must raise a break exception when the index
   operand is 1.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    item_state_init();
    P = ccpair_list(L, simple_item_constructor__one_integer_item, simple_item_destructor__noop);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(1 == ccpair_length(L, P));
    assert(0 == ccpair_car(P));
    assert(true  == item_state_is_constructed(0));
    assert(false == item_state_is_constructed(1));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_3 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The item constructor  function must raise a break  exception when the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    item_state_init();
    P = ccpair_list(L, simple_item_constructor__three_integer_items, simple_item_destructor__noop);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(3 == ccpair_length(L, P));
    assert(0 == ccpair_car(P));
    assert(1 == ccpair_ref(L, P, 1));
    assert(2 == ccpair_ref(L, P, 2));
    assert(true  == item_state_is_constructed(0));
    assert(true  == item_state_is_constructed(1));
    assert(true  == item_state_is_constructed(2));
    assert(false == item_state_is_constructed(3));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_1_4 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 0.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, simple_item_constructor__exception_at_0, simple_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
}

void
test_1_5 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 1.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, simple_item_constructor__exception_at_1, simple_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
}

void
test_1_6 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 2.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, simple_item_constructor__exception_at_2, simple_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
  assert(true == item_state_is_destructed(1));
}

void
test_1_7 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, simple_item_constructor__exception_at_3, simple_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
  assert(true == item_state_is_destructed(1));
  assert(true == item_state_is_destructed(2));
}


/** --------------------------------------------------------------------
 ** List function: lists of async items.
 ** ----------------------------------------------------------------- */

void
test_2_1 (void)
/* Use "ccpair_list()"  to build  an empty  list.  The  item constructor
   function must raise  a break exception immediately.  There  is a noop
   item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    P = ccpair_list(L, async_item_constructor__break_immediately, async_item_destructor__noop);
    assert(0 == ccpair_length(L, P));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_2 (void)
/* Use "ccpair_list()" to  build a list of integers with  one item.  The
   item constructor function must raise a break exception when the index
   operand is 1.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    item_state_init();
    P = ccpair_list(L, async_item_constructor__one_integer_item, async_item_destructor__noop);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(1 == ccpair_length(L, P));
    assert(0 == async_item_ref(ccpair_car(P)));
    assert(true  == item_state_is_constructed(0));
    assert(false == item_state_is_constructed(1));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_3 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The item constructor  function must raise a break  exception when the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  ccpair_t		P;
  cce_handler_t		P_H[1];

  if (cce_location(L)) {
    fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L)));
    cce_run_error_handlers_final(L);
    exit(EXIT_FAILURE);
  } else {
    item_state_init();
    P = ccpair_list(L, async_item_constructor__three_integer_items, async_item_destructor__noop);
    ccpair_cleanup_handler_pair_init(L, P_H, P);
    assert(3 == ccpair_length(L, P));
    assert(0 == async_item_ref(ccpair_car(P)));
    assert(1 == async_item_ref(ccpair_ref(L, P, 1)));
    assert(2 == async_item_ref(ccpair_ref(L, P, 2)));
    assert(true  == item_state_is_constructed(0));
    assert(true  == item_state_is_constructed(1));
    assert(true  == item_state_is_constructed(2));
    assert(false == item_state_is_constructed(3));
    if (0) { print_list(stderr, P); }
    cce_run_cleanup_handlers(L);
  }
}

void
test_2_4 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 0.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, async_item_constructor__exception_at_0, async_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
}

void
test_2_5 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 1.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, async_item_constructor__exception_at_1, async_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
}

void
test_2_6 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 2.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, async_item_constructor__exception_at_2, async_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
  assert(true == item_state_is_destructed(1));
}

void
test_2_7 (void)
/* Use "ccpair_list()"  to build  a list of  integers with  three items.
   The  item constructor  function raises  an error  exception when  the
   index operand is 3.  There is a noop item destructor function. */
{
  cce_location_t	L[1];
  bool volatile		flag = false;

  if (cce_location(L)) {
    if (0) { fprintf(stderr, "%s: %s\n", __func__, cce_condition_static_message(cce_condition(L))); }
    assert(cce_condition_is_error(cce_condition(L)));
    cce_run_error_handlers_final(L);
    flag = true;
  } else {
    item_state_init();
    ccpair_list(L, async_item_constructor__exception_at_3, async_item_destructor__noop);
    flag = false;
    cce_run_cleanup_handlers(L);
  }
  assert(true == flag);
  assert(true == item_state_is_destructed(0));
  assert(true == item_state_is_destructed(1));
  assert(true == item_state_is_destructed(2));
}


int
main (void)
{
  ccpair_init();

  /* List function */
  if (1) { test_1_1(); }
  if (1) { test_1_2(); }
  if (1) { test_1_3(); }
  if (1) { test_1_4(); }
  if (1) { test_1_5(); }
  if (1) { test_1_6(); }
  if (1) { test_1_7(); }
  if (1) { test_2_1(); }
  if (1) { test_2_2(); }
  if (1) { test_2_3(); }
  if (1) { test_2_4(); }
  if (1) { test_2_5(); }
  if (1) { test_2_6(); }
  if (1) { test_2_7(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
