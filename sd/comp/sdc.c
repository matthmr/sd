/**
 * @file sdc.c
 *
 * @brief SD compiler source code entry
 *
 * This file contains the logic
 * for the compiler to bytecode
 *
 * The parser for this format
 * is individually implemented
 * in other units.
 */

#include <stdio.h>

#include <sd/intr/limits.h>
#include <sd/comp/sdc.h>

#include "utils/err/err.h"

int main (int argc, char** argv) {

	uint i = 0;

	bool pipe = false;
	bool promise = false;

	FILE* file;

	if (argc > 1)
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {

			// -- info -- //
			case 'v':
				printf ("sdc " VERSION "\n");
				return 0;
				break;
			case 'h':
				fprintf (stdout, HELP);
				return 0;
				break;

			case '\0':
				LOCK (pipe);
				file = stdin;
				break;

			default:
				fprintf (stderr, "[ !! ] Bad usage. See sdread -h\n");
				return 1;
				break;
			}
		}
	}

	else /// promise file type
		goto open;
	}

	if (0) open: { 
	if (! (file = fopen (argv[i], "r")))
		Err (0x01, argv[i]);
	}

	compile: compile_src (file, data, LINE_LIMIT);

	return 0;

}
