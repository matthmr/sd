/**
 * This file contains verbose
 * error messaging formating
 */

#include <stdlib.h>
#include <stdio.h>

#include <sd/lang/tokens/gen/txtmaps.h>

#include <sd/utils/verbose/colors.h>
#include <sd/utils/types/shared.h>
#include <sd/utils/err/verr.h>
#include <sd/utils/err/err.h>

extern uint ln;
bool verr = 0;

void vErr (int code, char* info, char* lineinfo) {
	fprintf (stderr, vfmt, errmsg[code], info, lineinfo);
	verr = 1;
	// exit (code);
}

/// TODO: what the fuck happened here?
//char* vErr_get_type (int id) {
//	switch (id) {
//	case _INT: return "`int`"; break;
//	case _CHAR: return "`char`"; break;
//	case _FLOAT: return "`float`"; break;
//	case _ENUM: return "`enum`"; break;
//	case _ARRAY: return "`array`"; break;
//	case _LONG: return "`long`"; break;
//	case _SHORT: return "`short`"; break;
//	}
//}

char* vErr_get_type (int id) { return ""; }
