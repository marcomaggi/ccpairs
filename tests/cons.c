/*
  Part of: CCPairs
  Contents: test for basic construction functions
  Date: Nov  7, 2017

  Abstract

	Test file for basic construction functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ccpairs.h>

void
test_1_1 (void)
{
  ccpair_t	P;

  P = ccpair_cons(1, NULL);
  {
    assert(NULL != P);
    assert(1    == ccpair_car(P));
    assert(NULL == ccpair_cdr(P));
    assert(0    == ccpair_cdr_value(P));
  }
  ccpair_free(P);
}

int
main (void)
{
  test_1_1();
  exit(EXIT_SUCCESS);
}

/* end of file */
