/*
  Part of: CCPairs
  Contents: test for version functions
  Date: Nov  7, 2017

  Abstract

	Test file for version functions.

  Copyright (C) 2017, 2018, 2020 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc CCLIB_UNUSED, const char *const argv[] CCLIB_UNUSED)
{
  ccpairs_library_init();

  printf("version number string: %s\n", ccpairs_version_string());
  printf("libtool version number: %d:%d:%d\n",
	 ccpairs_version_interface_current(),
	 ccpairs_version_interface_revision(),
	 ccpairs_version_interface_age());
  exit(EXIT_SUCCESS);
}

/* end of file */
