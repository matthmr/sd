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
static const char efmt[] =\
	BOLD ("%s:%s:%s:")\
	RED_FG("error: ")\
	STYLE(__BOLD__, " %s") \
	RESET("\n");

/// @brief verbose error formating for run/compile-time
/// It formats as such
/// @verbatim
///
///    %s | %s\n%s
///    ^    ^   ^ error pointer
///    |    | line
///    | line number
///
/// @endverbatim
static const char vefmt[] =\
	LIGHT_GREY_FG ("\n%s |") \
	RESET (" %s\n") \
	GREEN_FG ("%s") RESET ("\n"); // TODO: make verbose error messaging
                             // optional at compile-time
                             // TODO: did-you-mean

/// @brief error message manifest
const char* emsg[] = {

	[0] = (char*)0,

	// -- on run -- //
	[EDRIV] = "cannot cast different assignment drivers", // proc a: let b: 1;
	[EINT] = "bad integer construction", // 0x0.a, 1..1
	[EOOBID] = "out-of-bound identifier", // a...a
	[EOOBN] = "out-of-bound number", // 99....9
	[EUNDEFID] = "undefined identifier", // a;
	[EKWID] = "keyword cannot be identifier", // let let
	[EUNHOID] = "unhookable identifier", // a b
	[EMISSMATCH] = "missing appropiate matcher", // [1;
	[EUNHOL] = "literals are unhookable", // 1 1

};

/// @brief standard error exitter
/// @param code exit code
/// @param finfo file info
/// @param einfo error info
void Err (int ecode, FInfo finfo, EInfo einfo) {

	// error header
	fprintf (stderr, efmt,
		finfo.filename,
		finfo.line,
		finfo.column,
		emsg[ecode]);

	// error body
	fprintf (stderr, vefmt,
		finfo.line,
		einfo.line,
		einfo.msg);

	exit (ecode);
}
