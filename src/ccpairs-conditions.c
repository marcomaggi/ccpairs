/*
  Part of: CCPairs
  Contents: exceptional-condition objects
  Date: Nov  7, 2017

  Abstract



  Copyright (C) 2017-2020 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you can redistribute  it and/or modify it under the terms of
  the GNU Lesser General Public License as published by the Free Software Foundation;
  either version 3.0 of the License, or (at your option) any later version.

  This library  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
  WARRANTY; without  even the implied  warranty of  MERCHANTABILITY or FITNESS  FOR A
  PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License along with
  this library; if not, write to the Free Software Foundation, Inc., 59 Temple Place,
  Suite 330, Boston, MA 02111-1307 USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "ccpairs-internals.h"


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: not enough items in list.
 ** ----------------------------------------------------------------- */

static char const *
condition_not_enough_items_static_message (cce_condition_t const * C CCLIB_UNUSED)
{
  return "not enough items in list";
}

static ccpairs_descriptor_not_enough_items_t ccpairs_descriptor_not_enough_items = {
  /* This field is set by the initialisation function below. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_not_enough_items_static_message
};

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static ccpairs_condition_not_enough_items_t const ccpairs_condition_not_enough_items = {
  .logic_error.error.root.condition.descriptor	= &ccpairs_descriptor_not_enough_items.descriptor
};

void
cce_descriptor_set_parent_to(ccpairs_descriptor_not_enough_items_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(ccpairs_descriptor_not_enough_items);
}

/* ------------------------------------------------------------------ */

void
ccpairs_condition_init_not_enough_items (cce_destination_t L CCLIB_UNUSED, ccpairs_condition_not_enough_items_t * C)
{
  cce_condition_init_logic_error(&(C->logic_error));
}

cce_condition_t const *
ccpairs_condition_new_not_enough_items (void)
{
  return (cce_condition_t const *)&ccpairs_condition_not_enough_items;
}

bool
ccpairs_condition_is_not_enough_items (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(ccpairs_descriptor_not_enough_items));
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: invalid empty list as operand.
 ** ----------------------------------------------------------------- */

static char const *
condition_empty_list_static_message (cce_condition_t const * C CCLIB_UNUSED)
{
  return "invalid empty list as operand";
}

static ccpairs_descriptor_empty_list_t ccpairs_descriptor_empty_list = {
  /* This field is set by the initialisation function below. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_empty_list_static_message
};

/* This struct  type has no  dynamic fields,  so there is  only one instance  of this
   struct type.  We allocate it statically. */
static ccpairs_condition_empty_list_t const ccpairs_condition_empty_list = {
  .not_enough_items.logic_error.error.root.condition.descriptor	= &ccpairs_descriptor_empty_list.descriptor
};

void
cce_descriptor_set_parent_to(ccpairs_descriptor_empty_list_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(ccpairs_descriptor_empty_list);
}

/* ------------------------------------------------------------------ */

void
ccpairs_condition_init_empty_list (cce_destination_t L, ccpairs_condition_empty_list_t * C)
{
  ccpairs_condition_init_not_enough_items(L, &(C->not_enough_items));
}

cce_condition_t const *
ccpairs_condition_new_empty_list (void)
{
  return (cce_condition_t *)&ccpairs_condition_empty_list;
}

bool
ccpairs_condition_is_empty_list (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(ccpairs_descriptor_empty_list));
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: invalid circular list as operand.
 ** ----------------------------------------------------------------- */

static char const *
condition_circular_list_static_message (cce_condition_t const * C CCLIB_UNUSED)
{
  return "invalid circular list as operand";
}

static ccpairs_descriptor_circular_list_t ccpairs_descriptor_circular_list = {
  /* This field is set by the initialisation function below. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_circular_list_static_message
};

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static ccpairs_condition_circular_list_t const ccpairs_condition_circular_list = {
  .logic_error.error.root.condition.descriptor	= &ccpairs_descriptor_circular_list.descriptor
};

void
cce_descriptor_set_parent_to(ccpairs_descriptor_circular_list_t) (cce_descriptor_t * const D)
{
  D->parent = cce_descriptor_pointer(ccpairs_descriptor_circular_list);
}

/* ------------------------------------------------------------------ */

void
ccpairs_condition_init_circular_list (cce_destination_t L CCLIB_UNUSED, ccpairs_condition_circular_list_t * C)
{
  cce_condition_init_logic_error(&(C->logic_error));
}

cce_condition_t const *
ccpairs_condition_new_circular_list (void)
{
  return (cce_condition_t *)&ccpairs_condition_circular_list;
}

bool
ccpairs_condition_is_circular_list (cce_condition_t const * C)
{
  return cce_condition_is(C, cce_descriptor_pointer(ccpairs_descriptor_circular_list));
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
ccpairs_conditions_module_initialisation (void)
{
  cce_descriptor_set_parent_to(cce_descriptor_logic_error_t)(cce_descriptor_pointer(ccpairs_descriptor_not_enough_items));
  cce_descriptor_set_parent_to(ccpairs_descriptor_not_enough_items_t)(cce_descriptor_pointer(ccpairs_descriptor_empty_list));
  cce_descriptor_set_parent_to(cce_descriptor_logic_error_t)(cce_descriptor_pointer(ccpairs_descriptor_circular_list));
}

/* end of file */
