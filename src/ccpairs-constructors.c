/*
  Part of: CCPairs
  Contents: constructor functions
  Date: Nov 23, 2017

  Abstract



  Copyright (C) 2017, 2018 Marco Maggi <marco.maggi-ipsu@poste.it>

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


ccpair_t
ccpair_list (cce_destination_t upper_L, ccpair_item_constructor_t * C, ccpair_item_destructor_t * D)
{
  ccpair_t volatile		head = NULL;

  {
    cce_location_t		L[1];
    uintptr_t			first_item;
    ccpair_item_handler_t	first_item_H[1];

    /* First build  the first item.   If the constructor "C()"  raises a
       break exception: the HEAD will stay NULL and we return it.

       Then build  the first  pair.  If the  constructor "ccpair_cons()"
       raises an exception:  we finalise the FIRST_ITEM  and reraise the
       exception. */
    if (cce_location(L)) {
      if (cce_condition_is_break(cce_condition(L))) {
	if (0) { fprintf(stderr, "%s: break at first item\n", __func__); }
	cce_run_body_handlers(L);
	return head;
      } else {
	if (0) { fprintf(stderr, "%s: error at first item\n", __func__); }
	cce_run_catch_handlers_raise(L, upper_L);
      }
    } else {
      if (0) { fprintf(stderr, "%s: doing item 0\n", __func__); }
      first_item = C(L, 0);
      ccpair_error_handler_item_init(L, first_item_H, first_item, D);
      head = ccpair_cons(L, first_item, NULL);
      cce_run_body_handlers(L);
    }
  }

  /* Build the other pairs and items.  If the constructor "C()" raises a
     break exception: the list is finished and we return the HEAD. */
  {
    cce_location_t		L[1];
    ccpair_list_item_handler_t	head_H[1];

    if (cce_location(L)) {
      if (cce_condition_is_break(cce_condition(L))) {
	if (0) { fprintf(stderr, "%s: break at item\n", __func__); }
	cce_run_body_handlers(L);
	return head;
      } else {
	if (0) { fprintf(stderr, "%s: error at item\n", __func__); }
	cce_run_catch_handlers_raise(L, upper_L);
      }
    } else {
      ccpair_t		prev = head;

      ccpair_error_handler_list_item_init(L, head_H, head, D);

      for (ccpair_idx_t idx=1;; ++idx) {
	if (0) { fprintf(stderr, "%s: doing item %lu\n", __func__, idx); }
	prev->D	= (uintptr_t) ccpair_cons(L, C(L, idx), NULL);
	prev	= (ccpair_t)  (prev->D);
      }

      cce_run_body_handlers(L);
      return head;
    }
  }
}

/* end of file */
