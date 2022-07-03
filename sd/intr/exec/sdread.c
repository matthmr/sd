/**
 * @file sdread.c
 *
 * @brief SD read wrapper functionality
 *
 * This file is a WRAPPER arround functionality
 * regarding the SD language. It makes it possible
 * to parse and interpret plain-text source code
 * and execute it on the fly
 */

#include <sd/lang/callback/vmcb.h>
#include <sd/lang/obj/ot.h>
#include <sd/lang/vm/vm.h>

#include <sd/intr/bytecode/sdbcparse.h>
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/exec/sdread.h>
#include <sd/intr/txt/sdparse.h>
#include <sd/intr/limits.h>

#include "arg/argparser.h"

#define PROG "sdread"

byte data[FBUFFER];

// TODO: HERE: seperate by `char` v. `string` instead
// of by flag type?
/// @brief flag manifest implementation,
/// lexicographically sorted at compile
/// time
const FlagManifest flag_manifest = {

	SINGLE (
		(Flag[]) {
			__as_char__ ('b', ACTION_BYTE, MUL, '\0'),
			__as_char__ ('e', ACTION_EXPR, ONE, '\0'),
			__as_char__ ('h', ACTION_HELP, NONE, '\0'),
			__as_char__ ('i', ACTION_INTERACTIVE, NONE, '\0'),
			__as_char__ ('m', ACTION_MODULE, MUL, '\0'),
			__as_char__ ('s', ACTION_SOURCE, MUL, '\0'),
			__as_char__ ('v', ACTION_VERSION, NONE, '\0')
		}
	),

	DOUBLE (
		(Flag[]) {
			__as_string__ ("byte", ACTION_BYTE, MUL, '\0'),
			__as_string__ ("expr", ACTION_EXPR, MUL, '\0'),
			__as_string__ ("help", ACTION_HELP, NONE, '\0'),
			__as_string__ ("int", ACTION_INTERACTIVE, NONE, '\0'),
			__as_string__ ("mod", ACTION_MODULE, MUL, '\0'),
			__as_string__ ("source", ACTION_SOURCE, MUL, '\0'),
			__as_string__ ("version", ACTION_VERSION, NONE, '\0'),
		}
	),

	// not yet implemented
	.flag_singlelong.this = NULL,
	.flag_comp.this = NULL,

};

const char* emsg[] = {
	[0] = (char*)0,

	[EBADARG] = "no such argument ",
	[ENOSUCHFILE] = "no such file ",
	[EMISSFILE] = "missing filename",
	[EMISSARG] = "missing argument",
};

/// @brief error formating for argparsing
///
/// It formats as such
/// @verbatim
///
/// %s: error: %s %s
/// ^          ^  ^ error detail
/// |          | error message
/// | program name
///
/// @endverbatim
static const char efmt[] =\
	BOLD ("%s: ")\
	RED_FG ("error: ")\
	STYLE (__BOLD__, "%s")\
	RESET ("\n");

static enum sdparse_err ecode;
static char** earg = NULL;

static long error_header (void) {
	fprintf (stderr, efmt, emsg[ecode], *earg);
	return ecode;
};

function const header = &error_header;
function const body = NULL;

static ArgData arg = {
	.file = &(struct arg_file) {
		.this = NULL,
		.ftype = SOURCE_DISK,
	},
	.fnum = 0,
};
static struct arg_file** argfile = &arg.file;

static Astatus action_panic (char* cargv, char** cenv) {
	return error_header ();
	//return ARG_ERR;
}
static Astatus action_help (char* cargv, char** cenv) {
	fputs (HELP, stdout);
	return ARG_INFO;
};
static Astatus action_version (char* cargv, char** cenv) {
	fputs ("sdread " VERSION "\n", stdout);
	return ARG_INFO;
};
static Astatus action_interactive (char* cargv, char** cenv) {
	// TODO
	return ARG_OK;
}
static Astatus action_file (char* cargv, char** cenv) {
	(*argfile)->this = fopen (cargv, "rb");
	return (*argfile)->this? ARG_OK: ARG_VERR;
}

const FlagAction flagaction_manifest[] = {
	[ACTION_HELP] = &action_help,
	[ACTION_VERSION] = &action_version,
	[ACTION_INTERACTIVE] = &action_interactive,
	[ACTION_SOURCE] = &action_file,
	[ACTION_BYTE] = &action_file,
	[ACTION_MODULE] = NULL, // TODO
	[ACTION_EXPR] = NULL, // TODO
};

Astatus promise (void) {
	return ARG_OK;
};

const Default defarg = &action_file; ///< @brief simple arg (flagless or not) handler
const SingleDash sdash = &action_file; ///< @brief single dash handler
const DoubleDash ddash = &action_panic;

int main (int argc, char** argv, char** env) {


	struct arg_file* afile = *argfile;

	Astatus astatus = ARG_OK;
	for (uint i = 1; i < argc; i++) {
		astatus = parseargs (PROG, argv[i], env);

		// handle exemption of the main loop
		switch (astatus) {

		// display generic error message; kill the program
		case ARG_ERR:
			Err (ecode, header, body);
			break;

		// show info (implicit action); skip main loop
		case ARG_INFO:
			goto skip;
			break;

		// handle error with a verbose error message; kill the program
		case ARG_VERR: {

		};
		break;

		default: break;
		}
	}

	FILE* file = afile->this;

	// initialise parse tree
	pt_init ();

	// initialise object table
	// Obj groot, lroot;
	// ot_init (&groot);
	// mkchild (&groot, gself = &lroot);

	// initialise SDVM
	vm_init ();

	// main callback loop (vm)
	callback_loop: for (; file; file++) {

		if (file_is_source (afile->ftype)) {
			while (src (src_callback)) {

				// if the callback is a stack callback, do what it says
				if (scope_is_stack (src_callback)) {
					stack_callback (src_callback);
				}
				else // otherwise continue buffering
					parse_src (afile->this, (char*)data, STDBUFFER);

			}
		}

		// TODO: bytecode callback loop
		else if (file_is_bytecode (afile->ftype)) {
			parse_bc (afile->this, (char*)data, STDBUFFER);
		}

	}

	// close `file' on exit if not a pipe
	for (uint i = 0; i < arg.fnum; i++)
		if (! file_is_fifo (afile->ftype))
			fclose (afile->this);

	skip: return 0;

}
