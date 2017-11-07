/*
  Part of: CCPairs
  Contents: version functions
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


const char *
ccpair_version_string (void)
{
  return ccpair_VERSION_INTERFACE_STRING;
}
int
ccpair_version_interface_current (void)
{
  return ccpair_VERSION_INTERFACE_CURRENT;
}
int
ccpair_version_interface_revision (void)
{
  return ccpair_VERSION_INTERFACE_REVISION;
}
int
ccpair_version_interface_age (void)
{
  return ccpair_VERSION_INTERFACE_AGE;
}

/* end of file */
