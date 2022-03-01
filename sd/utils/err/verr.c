/**
 * This file contains verbose
 * error messaging formating
 */

#include <stdlib.h>
#include <stdio.h>

#include <sd/utils/err/verr.h>
#include <sd/utils/err/err.h>

void vErr (int code, char* info) {
	fprintf (stderr, fmt, errmsg[code], info);
	exit (code);
}
