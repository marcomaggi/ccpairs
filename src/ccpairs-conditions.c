/*
  Part of: CCPairs
  Contents: condition objects
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


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: not enough items in list.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_not_enough_items_static_message;

static ccpair_descriptor_not_enough_items_t descriptor_not_enough_items = {
  /* This field is set by the initialisation function below. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_not_enough_items_static_message
};

ccpair_descriptor_not_enough_items_t const * const ccpair_descriptor_not_enough_items = &descriptor_not_enough_items;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static ccpair_condition_not_enough_items_t const condition_not_enough_items = {
  .base.condition.descriptor	= &descriptor_not_enough_items.descriptor
};

cce_condition_t const *
ccpair_condition_new_not_enough_items (void)
{
  return (cce_condition_t *)&condition_not_enough_items;
}

char const *
condition_not_enough_items_static_message (cce_condition_t const * C CCPAIR_UNUSED)
{
  return "not enough items in list";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: invalid empty list as operand.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_empty_list_static_message;

static ccpair_descriptor_empty_list_t const descriptor_empty_list = {
  .descriptor.parent		= &descriptor_not_enough_items.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_empty_list_static_message
};

ccpair_descriptor_empty_list_t const * const ccpair_descriptor_empty_list = &descriptor_empty_list;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static ccpair_condition_empty_list_t const condition_empty_list = {
  .base.condition.descriptor	= &descriptor_empty_list.descriptor
};

cce_condition_t const *
ccpair_condition_new_empty_list (void)
{
  return (cce_condition_t *)&condition_empty_list;
}

char const *
condition_empty_list_static_message (cce_condition_t const * C CCPAIR_UNUSED)
{
  return "invalid empty list as operand";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: invalid circular list as operand.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_circular_list_static_message;

static ccpair_descriptor_circular_list_t descriptor_circular_list = {
  /* This field is set by the initialisation function below. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_circular_list_static_message
};

ccpair_descriptor_circular_list_t const * const ccpair_descriptor_circular_list = &descriptor_circular_list;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static ccpair_condition_circular_list_t const condition_circular_list = {
  .base.condition.descriptor	= &descriptor_circular_list.descriptor
};

cce_condition_t const *
ccpair_condition_new_circular_list (void)
{
  return (cce_condition_t *)&condition_circular_list;
}

char const *
condition_circular_list_static_message (cce_condition_t const * C CCPAIR_UNUSED)
{
  return "invalid circular list as operand";
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
ccpair_conditions_module_initialisation (void)
{
  descriptor_not_enough_items.descriptor.parent	= &(cce_descriptor_logic_error_ptr->descriptor);
  descriptor_circular_list.descriptor.parent	= &(cce_descriptor_logic_error_ptr->descriptor);
}


/* end of file */
