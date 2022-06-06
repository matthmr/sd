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

#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

char* fmt; ///< @brief normal error format
char* vfmt; ///< @brief verbose error format

/// @brief normal error formating for run/compile-time
static const char* errfmt[] = {
	[TIME_ARG] = "arg:%s%s\n",
	[TIME_TXT] = "main:%s%s\n",
	[TIME_BYTE] = "main:%s%s\n",
	[TIME_COMP] = "compile:%s%s\n"
};

// TODO: file:LN ERR: ...
/// @brief verbose error formating for run/compile-time
static const char* verrfmt[] = {
	[TIME_ARG] = "arg:%s%s%s\n",
	[TIME_TXT] = "main:%s%s%s\n",
	[TIME_BYTE] = "main:%s%s%s\n",
	[TIME_COMP] = "compile:%s%s%s\n"
};

/// @brief error message manifest
const char* errmsg[] = {

	// -- on call -- //
	[ENOSUCH] = " E0x01: no such file ", // sd <file>
	[EMISS] = " E0x02: missing file name ", // sd -s

	// -- on run -- //
	[EDRIV] = " E0x03: cannot cast different assignment drivers", // proc a: let b: 1;
	[EINT] = " E0x04: bad integer construction", // 0x0.a, 1..1
	[EOOBN] = " E0x05: out-of-bound number", // 99....9
	[EOOBID] = " E0x06: out-of-bound identifier", // a...a
	[EUNDEFID] = " E0x07: undefined identifier", // a;
	[ENUID] = " E0x08: identifier cannot being with number", // 1a
	[EKWID] = " E0x08: keyword cannot be identifier", // let let
	[EUNHOID] = " E0x09: unhookable identifier ", // a b
	[EMISS] = " E0x0a: missing ", // [1;
	[EUNHOL] = " E0x0b: literals are unhookable without expression token", // 1 1

};

/// @brief error time setter
/// @param t time to be set to
void e_set (Time t) {
	fmt = (char*) errfmt[t];
	vfmt = (char*) verrfmt[t];
}

/// @brief standard error exitter
/// @param code exit code
/// @param info message to send to the error handler
void Err (int code, char* info) {
	Die (fmt, errmsg[code], info, code);
}
