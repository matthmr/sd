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

char* vErr_get_type (int id) { return ""; }
char* vErr_verbose (char* a1, uint a2, uint a3, uint a4) { return ""; }
