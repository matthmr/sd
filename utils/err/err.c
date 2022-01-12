/**
 * This file contains standard error
 * information so that error messages
 * can be a bit more informative and
 * centralized
 */

#include "../utils.c"
#include "err.h"

static char* fmt;
static char* info = NULL;

static const char* errfmt[] = {
	[argtime] = "[ARGPARSE]:%s%s\n",
	[txtruntime] = "[RUNTIME]:%s%s\n",
	[byteruntime] = "[RUNTIME]:%s%s\n",
	[cmptime] = "[COMPILE]:%s%s\n",
	[asmtime] = "[ASSEMBLE]:%s%s\n",
	[lntime] = "[LINK]:%s%s\n"
};

static const char* warmsg[] = {
	NULL /* TODO: centrelize warning messages */
};

static const char* errmsg[] = {
	" E01: No such file ",
};

inline void Set (Env env) {
	fmt = (char*) errfmt[env];
}

void Err (int code, char* info) {
	int index = code - 1;
	Die (fmt, errmsg[index], info, code);
}
