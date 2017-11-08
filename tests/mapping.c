/*
  Part of: CCPairs
  Contents: test for mapping functions
  Date: Nov  8, 2017

  Abstract

	Test file for mapping construction functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ccpair_t
make_list_5 (void)
{
  return ccpair_cons(1, ccpair_cons(2, ccpair_cons(3, ccpair_cons(4, ccpair_cons(5, NULL)))));
}

uintptr_t
map_fun_1 (uintptr_t item)
{
  return (item * 10);
}

/* ------------------------------------------------------------------ */

void
test_1_1 (void)
/* Single map mapping. */
{
  cce_location_t	L[1];
  cce_handler_t		P_H[1];
  cce_handler_t		Q_H[1];
  ccpair_t		P, Q;

  if (cce_location(L)) {
    // handle the exceptional condition
    cce_run_error_handlers_final(L);
  } else {
    P = make_list_5();
    ccpair_cleanup_handler_list_init(L, P_H, P);
    {
      Q = ccpair_map_forward(map_fun_1, P);
      ccpair_cleanup_handler_list_init(L, Q_H, Q);
      if (0) { fprintf(stderr, "%s: %lu\n", __func__, ccpair_ref(L, Q, 0)); }

      assert(10 == ccpair_ref(L, Q, 0));
      assert(20 == ccpair_ref(L, Q, 1));
      assert(30 == ccpair_ref(L, Q, 2));
      assert(40 == ccpair_ref(L, Q, 3));
      assert(50 == ccpair_ref(L, Q, 4));
    }
    cce_run_cleanup_handlers(L);
  }
}

int
main (void)
{
  ccpair_init();

  if (1) { test_1_1(); }

  exit(EXIT_SUCCESS);
}

/* end of file */
