/**
 * This files contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#include <string.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

void getinptr (uint* i, char* line, uint lnsize, char del) {
	char c;
	uint len = 0;

	while ((len+g_offset) < lnsize) {
		c = line[len+g_offset];
		if (c == del || WHITESPACE (c) ||
		!  ( LETTER (c) || NUMBER (c) ))
			break;
		else
			len++;
	}

	if (!len) /// fall-through
		return;
	
	g_offset += len; /// point to `i` of an adjancent name...
	*i = (g_offset-1); /// ... counting for incremental loop
}
