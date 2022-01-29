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

#define VERSION "v0.3.1"
#include <stdio.h>

#define LOCK_PARSE
#undef LOCK_STACK

#include <sd/intr/txt/sdparse.h>

#undef LOCK_ERR

#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

#define LOCK_TYPES

#include <sd/intr/bytecode/sdbcparse.h>
#include <sd/lang/tokens/bytecode.h>
#include <sd/utils/types/shared.h>
#include <sd/intr/exec/sdread.h>
#include <sd/intr/limits.h>

/// TODO: unhandled `<expr>`: parse it and execute within main file context
int main (int argc, char** argv) {

	uint i = 0;

	bool pipe = false;
	bool promise = false;

	FILE* file = NULL;

	enum ftype f_type = SOURCE;

	e_set (argtime);

	if (argc > 1) for (i = 1; i < argc; i++) {
		if (! promise) {
			if (argv[i][0] == '-') {
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
					return 1;
					break;
				}
			}
			else { /// argv[i][0] != '-'
				f_type = SOURCE;
				goto open;
			}
		}
		else /// promise file type
			goto open;
	}
	else { /// interpret as `sdread -`
		LOCK (pipe);
		file = stdin;
	}

	if (promise)
		Err (0x02, " ");

	if (0) {
	open: {
		if (! (file = fopen (argv[i], "r")))
			Err (0x01, argv[i]);
	}
	expr: ;
	}

	byte data[LINE_LIMIT];

	/// TODO: maybe accept multiple files as modules? this would become a loop
	switch (f_type) {
		case SOURCE:
			parse_src (file, data, LINE_LIMIT);
			break;
		case BYTECODE:
			parse_bc (file, data, BCLINE_LIMIT);
			break;
	}

	/* close `file` on exit */
	if (!pipe)
		fclose (file);

	return 0;

}
