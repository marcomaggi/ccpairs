/*
  Part of: CCPairs
  Contents: exception handler functions
  Date: Nov  7, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This program is  free software: you can redistribute  it and/or modify
  it  under the  terms  of  the GNU  Lesser  General  Public License  as
  published by  the Free  Software Foundation, either  version 3  of the
  License, or (at your option) any later version.

  This program  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  General Public License for more details.

  You  should have received  a copy  of the  GNU General  Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Predefined exception handler: pair memory release.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_handler_pair_function (const cce_condition_t * C CCPAIR_UNUSED, cce_handler_t * H)
{
  if (0) {
    fprintf(stderr, "%s: releasing pair %p\n", __func__, (void *)H->pointer);
  }
  ccpair_free(H->pointer);
}

void
ccpair_cleanup_handler_pair_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
{
  H->function	= ccpair_handler_pair_function;
  H->pointer	= P;
  cce_register_cleanup_handler(L, H);
}

void
ccpair_error_handler_pair_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
{
  H->function	= ccpair_handler_pair_function;
  H->pointer	= P;
  cce_register_error_handler(L, H);
}


/** --------------------------------------------------------------------
 ** Predefined exception handler: list memory release.
 ** ----------------------------------------------------------------- */

__attribute__((nonnull(1,2)))
static void
ccpair_handler_list_function (const cce_condition_t * C CCPAIR_UNUSED, cce_handler_t * H)
{
  if (0) {
    fprintf(stderr, "%s: releasing list %p\n", __func__, (void *)H->pointer);
  }
  ccpair_free_list(H->pointer);
}

void
ccpair_cleanup_handler_list_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
{
  H->function	= ccpair_handler_list_function;
  H->pointer	= P;
  cce_register_cleanup_handler(L, H);
}

void
ccpair_error_handler_list_init (cce_location_t * L, cce_handler_t * H, ccpair_t P)
{
  H->function	= ccpair_handler_list_function;
  H->pointer	= P;
  cce_register_error_handler(L, H);
}

/* end of file */