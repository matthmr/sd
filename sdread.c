/**
 * This file is a WRAPPER arround functionality
 * regarding the sd language. It makes it possible
 * to parse and interpret plain-text source code
 * and execute it on the fly.
 *
 * sd can be compiled by sdcomp into a .sdo file
 * which can be linked by sdlink into a .sde file,
 * which in turn can be "directly" executed by sdexec.
 *
 * This is the main source for the functionality
 * used by scriptsd.
 */

#include <stdio.h>

#define VERSION "sdread v0.2.4\n"
#define LOCK_PARSE

#include "sdparse.h"
#include "utils/utils.h"

/**
 * Lock type *AFTER* including utils.h because
 * we don't want the enum, but utils.h does.
 */
#define LOCK_TYPES

#include "utils/sharedtypes.h"
#include "intr/limits.h"

int main (int argc, char** argv) {

	bool pipe;
	FILE* file;

	/// gets the type of input stream
	if (argc > 1) {
		if (argv[1][0] == '-') switch (argv[1][1]) {
			case 'v':
				printf (VERSION);
				return 0; break;
			case '\0':
				LOCK (pipe);
				file = stdin; break;
			case 'h':
				fprintf (stderr,
					"\nMade by mH (https://github.com/matthmr)\n"
					"\tsdread\t\t => The standard SD plain-text interpreter\n\n"
					"Usage:\t[data stream] | sdread - \"[expression]\"\n"
					"\tsdread [file] \"[expression]\"\n\n"
					"Info:\tsdread -h\t => Displays this message and exits\n"
					"\tsdread -v\t => Displays the version and exits\n\n");
				return 0; break;
		 default:
				fprintf (stderr,
					"[ !! ] Bad usage. See sdread -h\n"
				);
				return 0; break;
		}
		else if (argv[1][0] != '\0') {
			file = fopen (argv[1], "r");
			if (!file) Die ("E01: File not found", 1);
		}
	}
	else {
		LOCK (pipe);
		file = stdin;
	}

	unsigned char data[LINE_LIMIT];

	StartParse (file, data, LINE_LIMIT, argc, argv);

	if (!pipe)
		fclose (file);

	return 0;

}
