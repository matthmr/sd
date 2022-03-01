/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

char* fmt;

static const char* errfmt[] = {
	[TIME_ARG] = "arg:%s%s\n",
	[TIME_TXT] = "main:%s%s\n",
	[TIME_BYTE] = "main:%s%s\n",
	[TIME_COMP] = "compile:%s%s\n"
};

const char* errmsg[] = {
	0x00,

	" E0x01: no such file ", // sd <file>
	" E0x02: missing file name ", // sd -s
	" E0x03: cannot cast procedure", // proc a: let b: 1;
	" E0x04: bad integer construction", // 0x0.a, 1..1
	" E0x05: out-of-bound number", // 99....9

};

inline void e_set (Time t) {
	fmt = (char*) errfmt[t];
}

inline void Err (int code, char* info) {
	Die (fmt, errmsg[code], info, code);
}
