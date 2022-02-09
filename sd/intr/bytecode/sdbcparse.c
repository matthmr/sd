/**
 * This file contains the logic
 * for parsing SD bytecode.
 */

#include <stdio.h>

#include <sd/intr/bytecode/sdbcparse.h>
#include <sd/utils/err/err.h>
#include <sd/lang/tokens/bytecode.h>

void parser_bstream (byte** data) {

}

/* this wraps around `parser_bstream` to use `fgets`
 * and load module roots */
void parse_bc (FILE* file, byte* data, const uint BCLINE_LIMIT) {

	e_set (byteruntime);

	while (fgets (data, BCLINE_LIMIT, file) != NULL)
		parser_bstream (&data);

}
