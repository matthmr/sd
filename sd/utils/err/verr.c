/**
 * This file contains verbose
 * error messaging formating
 */

#include <stdlib.h>
#include <stdio.h>

#include <sd/lang/tokens/utils/txtmaps.h>

#include <sd/utils/verbose/colors.h>
#include <sd/utils/types/shared.h>
#include <sd/utils/err/verr.h>
#include <sd/utils/err/err.h>

extern uint ln;

void vErr (int code, char* info, char* lineinfo) {
	fprintf (stderr, vfmt, errmsg[code], info, lineinfo);
	exit (code);
}

char* vErr_get_type (int id) {
	switch (id) {
	case _INT: return "`int`"; break;
	case _CHAR: return "`char`"; break;
	case _FLOAT: return "`float`"; break;
	case _ENUM: return "`enum`"; break;
	case _LIST: return "`list`"; break;
	case _MAP: return "`map`"; break;
	case _LONG: return "`long`"; break;
	case _SHORT: return "`short`"; break;
	}
}

char* vErr_verbose (char* data, uint ln, uint wstart_i, uint wsize) {  }
