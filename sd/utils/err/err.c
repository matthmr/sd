/**
 * @file err.c
 *
 * @brief standard error formatting
 *
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */


#include <stdio.h>
#include <stdlib.h>

// TODO: ignore colors at runtime
#include <sd/utils/verbose/colors.h>
#include <sd/utils/err/err.h>

/// @brief error formating for run/compile-time
///
/// It formats as such
/// @verbatim
///
///    %s:%s:%s %s
///    ^  ^  ^   ^ error message
///    |  |  | column number
///    |  | line number
///    | filename
///
/// @endverbatim
static const char* efmt[] =\
	BOLD ("%s:%s:%s:")\
	RED_FG("error: ")\
	STYLE(__BOLD__, " %s\n") __RESET__;

/// @brief verbose error formating for run/compile-time
/// It formats as such
/// @verbatim
///
///    %s | %s\n%s
///    ^    ^  ^ error message (optional)
///    |    | line
///    | line number
///
/// @endverbatim
static const char* vefmt[] =\
	LIGHT_GREY_FG ("\n%s |")\
	__RESET__ " %s\n"\
	GREEN_FG ("%s") __RESET__; // TODO: make verbose error messaging
                             // optional at compile-time
                             // TODO: did-you-mean

/// @brief error message manifest
const char* errmsg[] = {

	/* [ENOSUCHFILE] = " E0x01: no such file", // sd <file> */
	/* [EMISSFILE] = " E0x02: missing file name", // sd -s */

	[0] = NULL,

	// -- on run -- //
	[EDRIV] = "E0x01: cannot cast different assignment drivers", // proc a: let b: 1;
	[EINT] = "E0x02: bad integer construction", // 0x0.a, 1..1
	[EOOBID] = "E0x03: out-of-bound identifier", // a...a
	[EOOBN] = "E0x04: out-of-bound number", // 99....9
	[EUNDEFID] = "E0x05: undefined identifier", // a;
	[EKWID] = "E0x06: keyword cannot be identifier", // let let
	[EUNHOID] = "E0x07: unhookable identifier", // a b
	[EMISSMATCH] = "E0x08: missing appropiate matcher", // [1;
	[EUNHOL] = "E0x09: literals are unhookable", // 1 1

};

/// @brief standard error exitter
/// @param code exit code
/// @param info message to send to the error handler
void Err (int ecode, FInfo finfo, EInfo einfo) {

	// error header
	fprintf (stderr, efmt,
		finfo.filename,
		finfo.line,
		finfo.column,
		efmt[ecode]);

	// error body
	fprintf (stderr, vefmt,
		finfo.line,
		einfo.line,
		einfo.msg);

	exit (ecode);
}
