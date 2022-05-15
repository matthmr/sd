/**
 * This file contains verbose
 * error messaging formating
 */

#ifndef LOCK_VERR
#  define LOCK_VERR

#  include <sd/utils/err/err.h>

#  define ERR(x) vErr (x, NO_INFO, NO_LINEINFO)
#  define NO_INFO_ERR(x,y) vErr (x, NO_INFO, y)
#  define NO_LINEINFO_ERR(x,y) vErr (x, y, NO_LINEINFO)

#  include <sd/utils/types/shared.h>

extern bool verr;

void vErr (int, char*, char*);

char* vErr_get_type (int);
char* vErr_verbose (char*, uint, uint, uint);

#endif
