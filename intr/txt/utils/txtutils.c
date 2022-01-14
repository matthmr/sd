/**
 * This files contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#include "txtutils.h"
#include "../../../utils/utils.h"
#include <string.h>

static uint offset;

bool streq (char* string, const char* kw) { }

void getname (char** name, uint* i, char* line, uint lnsize, char del) {
	char c;
	len = 0;

	while ((len+offset) < lnsize) {
		c = line[len+offset];
		if (c == del ||
			  c == 0x20 || c == 0x0a || c == 0x09 || c == 0x00 ||
			  ! ( LETTER (c) || NUMBER (c)) /// any other non-alpha-numeric token
		) break;
		else
			len++;
	}
	
	/// fall-through
	if (!len) {
		*name = NULL;
		return;
	}
	
	*i = (offset+len-1); /// count for increment

	strncpy (*name, line+offset, len);
	offset += len+1;
}
