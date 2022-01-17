/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

static char* fmt;

static const char* errfmt[] = {
	[argtime] = "[ARGPARSE]:%s%s\n",
	[txtruntime] = "[RUNTIME]:%s%s\n",
	[byteruntime] = "[RUNTIME]:%s%s\n",
	[cmptime] = "[COMPILE]:%s%s\n",
	[asmtime] = "[ASSEMBLE]:%s%s\n",
	[lntime] = "[LINK]:%s%s\n"
};

static const char* warmsg[] = {
	0x00 /* TODO: centralize warning messages */
};

static const char* errmsg[] = {
	0x00,
	" E01: No such file ",
	" E02: Missing file name "
};

inline void Set (Env env) {
	fmt = (char*) errfmt[env];
}

void Err (int code, char* info) {
	Die (fmt, errmsg[code], info, code);
}
