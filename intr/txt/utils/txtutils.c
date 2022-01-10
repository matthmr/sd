/**
 * This files contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#undef LOCK_BOOLEAN

#include "txtutils.h"

bool streq (char* string, char* kw) { }

char* kwget (char* string, char del) {
	if (!del)
		del = (char) 0x20;

	static int level;
}


