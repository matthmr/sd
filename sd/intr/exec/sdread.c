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
#define DIS "-disable"
#define EN "-enable"

byte data[FBUFFER];

COMPFLAG (_o, ACTION_OPTION,
	(FlagComp[]) {
		__as_comp__ ("color", DIS, _I_COLOR, NONE, '\0'),
	}
);

/// @brief flag manifest implementation,
/// lexicographically sorted at compile-time
/// @note single flags with `NONE` as their
/// `am` field compound if possible (i.e. it
/// can override)
const FlagManifest flag_manifest = {

	SINGLE (
		(Flag[]) {
			__as_char__ ('E', _EXPR_BEFORE, ACTION_EXPR, MUL, '\0', NULL),
			__as_char__ ('b', _BYTE, ACTION_BYTE, MUL, '\0', NULL),
			__as_char__ ('e', _EXPR_AFTER, ACTION_EXPR, MUL, '\0', NULL),
			__as_char__ ('h', _HELP, ACTION_HELP, NONE, '\0', NULL),
			__as_char__ ('i', _INT, ACTION_INT, COMP, '\0', NULL),
			__as_char__ ('m', _MODULE, ACTION_MODULE, MUL, '\0', NULL),
			__as_char__ ('o', _NONE, ACTION_NONE, NONE, '\0', &_o),
			__as_char__ ('s', _SOURCE, ACTION_SOURCE, MUL, '\0', NULL),
			__as_char__ ('v', _VERSION, ACTION_VERSION, NONE, '\0', NULL),
		}
	),

	DOUBLE (
		(Flag[]) {
			__as_string__ ("Expr", _EXPR_BEFORE, ACTION_EXPR, MUL, '\0', NULL),
			__as_string__ ("byte", _BYTE, ACTION_BYTE, MUL, '\0', NULL),
			__as_string__ ("expr", _EXPR_AFTER, ACTION_EXPR, MUL, '\0', NULL),
			__as_string__ ("help", _HELP, ACTION_HELP, NONE, '\0', NULL),
			__as_string__ ("int", _INT, ACTION_INT, NONE, '\0', NULL),
			__as_string__ ("mod", _MODULE, ACTION_MODULE, MUL, '\0', NULL),
			__as_string__ ("source", _SOURCE, ACTION_SOURCE, MUL, '\0', NULL),
			__as_string__ ("version", _VERSION, ACTION_VERSION, NONE, '\0', NULL),
		}
	),

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
static char **earg = NULL;

static int error_header (void) {
	fprintf (stderr, efmt, emsg[ecode], *earg);
	return ecode;
};

function const header = &error_header;
function const body = NULL;

#ifndef UNIT_LOCK_self
static Arg arg = {
	.data = {
		.file = &(struct arg_file) {
			.this = NULL,
			.ftype = SOURCE_DISK,
		},
		.fnum = 0,
		.expr = NULL,
	},
	.set = {0}, // &_set,
};
static ArgFile **argfile = &arg.data.file;
#endif

// default handlers
static Astatus action_panic (int cl, char *arg) {
#ifndef UNIT_LOCK_self
	return error_header ();
#endif
//@unit.replacewith ACTION
}
static Astatus action_help (int cl, char *arg) {
	fputs (HELP, stdout);
	return ARG_INFO;
};
static Astatus action_version (int cl, char *arg) {
	fputs ("sdread " VERSION "\n", stdout);
	return ARG_INFO;
};
static Astatus action_int (int cl, char *arg) {
	// return aset (_INT);
	return ARG_OK;
}
static Astatus action_file (int cl, char *arg) {
#ifndef LOCK_UNIT
	switch (cl) {
	case _BYTE:
		break;
	case _SOURCE:
	default: // assume flagless file as of type `source'
		break;
	}
	return ARG_OK;
#endif
//@unit.replacewith ACTION
}

// compound handlers
static Astatus action_option (int cl, char *arg) {
	return ARG_OK;
}

const FlagAction flagaction_manifest[] = {
	[ACTION_HELP] = &action_help, // --help
	[ACTION_VERSION] = &action_version, // --version
	[ACTION_INT] = &action_int, // --int

	[ACTION_SOURCE] = &action_file, // sd file.sd
	[ACTION_BYTE] = &action_file, // sd -b file.sd
	[ACTION_MODULE] = NULL, // TODO // --mod
	[ACTION_EXPR] = NULL, // TODO // --expr

	[ACTION_OPTION] = &action_option, // -o*
};

Astatus promise (const Flag *FLAG, char *arg) {
	return flagaction_manifest[FLAG->common.action]
	  (FLAG->common.id, arg);
};

const Default defarg = &action_file; ///< @brief simple arg (flagless or not) handler
const SingleDash sdash = &action_file; ///< @brief single dash handler
const DoubleDash ddash = &action_file; ///< @brief double dash handler

int main (int argc, char **argv, char **env) {

#ifndef UNIT_LOCK_self
	ArgFile *afile = *argfile;
#endif

	Astatus astatus = ARG_OK;
	char *ARG = NULL;

	// main argument loop
	for (uint i = 1; i < argc && (ARG = argv[i]); i++) {
		arg: astatus = parseargs (PROG, (char*)(ARG + stroffset));

		// handle exemption of the main loop
		switch (astatus) {

		// handle disambiguation callback
		case ARG_MORE:
			goto arg;
			break;

		// display a generic error message; kill the program
		case ARG_ERR:
#ifndef UNIT_LOCK_self
			Err (ecode, header, body);
#endif
			break;

		// show info (implicit action); skip main loop
		case ARG_INFO:
			goto skip;
			break;

		// handle error with a verbose error message; kill the program
		case ARG_VERR:
			// TODO: implement this
			goto skip;
			break;

		default: break;
		}

		// try to cat, error on fail
	}

#ifndef UNIT_LOCK_self
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
	for (uint i = 0; i < arg.data.fnum; i++)
		if (! file_is_fifo (afile->ftype))
			fclose (afile->this);
#endif

	skip: return 0;

}
//@unit.main main
