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
 ** Base exceptional condition descriptor.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	descriptor_base_static_message;

static ccpair_descriptor_base_t descriptor_base = {
  /* This "parent" field is set by the initialisation function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= descriptor_base_static_message
};

ccpair_descriptor_base_t const * const ccpair_descriptor_base = &descriptor_base;

const char *
descriptor_base_static_message (cce_condition_t const * C CCPAIR_UNUSED)
{
  return "CCPair exceptional condition";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: not enough items in list.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_not_enough_items_static_message;

static ccpair_descriptor_not_enough_items_t const descriptor_not_enough_items = {
  .descriptor.parent		= &descriptor_base.descriptor,
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
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
ccpair_conditions_module_initialisation (void)
{
  cce_descriptor_set_root_parent(&descriptor_base.descriptor);
}


/* end of file */
