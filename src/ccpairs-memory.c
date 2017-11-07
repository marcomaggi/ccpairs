/*
  Part of: CCPairs
  Contents: memory functions
  Date: Tue Nov  7, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


ccpair_t
ccpair_memory_default_malloc (void)
{
  ccpair_t	P = malloc(sizeof(ccpair_stru_t));
  if (NULL != P) {
    return P;
  } else {
    exit(EXIT_FAILURE);
  }
}

void
ccpair_memory_default_free (ccpair_t P)
{
  free(P);
}

static ccpair_malloc_fun_t *	malloc_fun = ccpair_memory_default_malloc;
static ccpair_free_fun_t *	free_fun   = ccpair_memory_default_free;

void
ccpair_memory_set_malloc_fun (ccpair_malloc_fun_t * f)
{
  malloc_fun = f;
}

void
ccpair_memory_set_free_fun (ccpair_free_fun_t * f)
{
  free_fun = f;
}

ccpair_t
ccpair_malloc (void)
{
  return malloc_fun();
}

void
ccpair_free (ccpair_t P)
{
  free_fun(P);
}

/* end of file */
