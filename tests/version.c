/*
  Part of: CCPairs
  Contents: test for version functions
  Date: Nov  7, 2017

  Abstract

	Test file for version functions.

  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  See the COPYING file.
*/

#include <ccpairs.h>
#include <stdio.h>
#include <stdlib.h>

int
main (int argc CCPAIR_UNUSED, const char *const argv[] CCPAIR_UNUSED)
{
  ccpair_init();

  printf("version number string: %s\n", ccpair_version_string());
  printf("libtool version number: %d:%d:%d\n",
	 ccpair_version_interface_current(),
	 ccpair_version_interface_revision(),
	 ccpair_version_interface_age());
  exit(EXIT_SUCCESS);
}

/* end of file */
