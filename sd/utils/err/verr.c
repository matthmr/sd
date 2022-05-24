/**
 * @file verr.c
 *
 * @brief verbose error formating
 *
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

extern uint ln; ///< @brief current line number
bool verr = 0; ///< @brief lock: use verbose error

/// @brief standard verbose error exitter
/// @param code exit code
/// @param info message to send to the error handler
/// @param lineinfo file info to send to the error handler
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
