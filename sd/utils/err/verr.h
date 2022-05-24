/**
 * @file verr.h
 *
 * @brief verbose error formating
 *
 * This file contains verbose
 * error messaging formating
 */

#ifndef LOCK_VERR
#  define LOCK_VERR ///< lock: standard lock

#  include <sd/utils/err/err.h>

#  define ERR(x) vErr (x, NO_INFO, NO_LINEINFO) ///< macro: call vErr as Err
#  define NO_INFO_ERR(x,y) vErr (x, NO_INFO, y) ///< macro: call vErr without info
#  define NO_LINEINFO_ERR(x,y) vErr (x, y, NO_LINEINFO) ///< macro: call vErr without line info

#  include <sd/utils/types/shared.h>

extern bool verr;

void vErr (int, char*, char*);

char* vErr_get_type (int);
char* vErr_verbose (char*, uint, uint, uint);

#endif
