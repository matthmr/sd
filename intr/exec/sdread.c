/**
 * This file is a WRAPPER arround functionality
 * regarding the sd language. It makes it possible
 * to parse and interpret plain-text source code
 * and execute it on the fly.
 *
 * sd can be compiled by sdcinto a .sdo file
 * which can be directly executed by sdexec.
 *
 * This is the main source for the functionality
 * used by scriptsd.
 */

/// TODO: make an argparser for this to
///       be able to differentiate bet-
///       ween operating modes

#define VERSION "v0.2.4"
#include <stdio.h>

#define LOCK_PARSE
#include "../txt/sdparse.h"
#include "../../utils/utils.h"
#include "../../utils/err/err.h"

#define LOCK_TYPES
#include "../../utils/types/shared.h"
#include "../limits.h"
#include "sdread.h"

/// TODO: unhandled `<expr>`
int main (int argc, char** argv) {

	bool pipe = false;
	bool promise = false;

	FILE* file = NULL;

	enum ftype f_type = SOURCE;

	Set (argtime);

	if (argc > 1) for (uint i = 1; i < argc; i++) {
		if (! promise) {
			if (argv[i][0] == '-')
				switch (argv[i][1]) {

				// -- info -- //
				case 'v':
					printf ("sdread " VERSION "\n");
					return 0;
					break;
				case 'h':
					fprintf (stdout, HELP);
					return 0;
					break;

				case 'a': if (! file)
					f_type = ASM;
					LOCK (promise);
					continue;
					break;
				case 's': if (! file)
					f_type = BYTECODE;
					LOCK (promise);
					continue;
					break;

				case '\0':
					LOCK (pipe);
					file = stdin;
					goto expr;
					break;

				default:
					fprintf (stderr, "[ !! ] Bad usage. See sdread -h\n");
					return 0;
					break;
				}
			else {
				if (! (file = fopen (argv[i], "r")) )
					Err (0x01, argv[i]);
				goto expr;
			}
		}
		else { /// promise file type
			if (! (file = fopen (argv[i], "r")) )
				Err (0x01, argv[i]);
			goto expr;
		}
	}
	else { /// interpret as `sdread -`
		LOCK (pipe);
		file = stdin;
	}

	if (promise)
		Err (0x02, " ");

	if (0) expr: { };

	byte data[LINE_LIMIT];

	/* send `file` to the appropiate parser */
	switch (f_type) {
		case SOURCE: parse_src (file, data, LINE_LIMIT); break;
		case ASM: break;
		case BYTECODE: break;
	}

	/* close `file` on exit */
	if (!pipe)
		fclose (file);

	return 0;

}
