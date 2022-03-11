/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

char* fmt;
char* vfmt;

static const char* errfmt[] = {
	[TIME_ARG] = "arg:%s%s\n",
	[TIME_TXT] = "main:%s%s\n",
	[TIME_BYTE] = "main:%s%s\n",
	[TIME_COMP] = "compile:%s%s\n"
};

// TODO: file:LN:COL: ERR: ...
static const char* verrfmt[] = {
	[TIME_ARG] = "arg:%s%s%s\n",
	[TIME_TXT] = "main:%s%s%s\n",
	[TIME_BYTE] = "main:%s%s%s\n",
	[TIME_COMP] = "compile:%s%s%s\n"
};

const char* errmsg[] = {
	0x00,

	" E0x01: no such file ", // sd <file>
	" E0x02: missing file name ", // sd -s
	" E0x03: cannot cast different assignment drivers (`proc` and `let`)", // proc a: let b: 1;
	" E0x04: bad integer construction", // 0x0.a, 1..1
	" E0x05: out-of-bound number", // 99....9
	" E0x06: out-of-bound uword (maximum of 64 case-insensitive alpha-numeric characters plus '$' and '_')", // a...a
	" E0x07: undefined uword cannot cast type ", // int a: 1;
	" E0x08: keyword cannot be uword", // let let
	" E0x09: unhookable word", // a b
	" E0x0a: missing ", // [1;
	" E0x0b: literals are unhookable without `expr`s ", // 1 1

};

inline void e_set (Time t) {
	fmt = (char*) errfmt[t];
	vfmt = (char*) verrfmt[t];
}

inline void Err (int code, char* info) {
	Die (fmt, errmsg[code], info, code);
}
