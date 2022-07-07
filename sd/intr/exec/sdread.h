/**
 * @file sdread.h
 *
 * @brief SD read wrapper functionality
 *
 * This file contains promises
 * set for parser frontends
 * and misc data for sdread
 * frontend
 */

#ifndef LOCK_READ
#  define LOCK_READ ///< lock: standard lock

#  include <stdio.h>

#  include "arg/argparser.h"

#  define VERSION\
	"v0.4.2"

/// @brief prompt for interactive mode
#  define PROMPT "> "
#  define NL_PROMPT "~ "

/// @brief file types for sdread arguments
enum ftype {
	BYTECODE_DISK,
	BYTECODE_FIFO,
	SOURCE_DISK,
	SOURCE_FIFO,
};

/// @brief flag actions for sdread
/// Each flag has its own function to handle whatever
/// action it must do. `argparser.h` also provides a
/// couple global variables for common arg parsing.
enum action {
	ACTION_HELP,
	ACTION_VERSION,
	ACTION_MODULE,
	ACTION_EXPR,
	ACTION_SOURCE,
	ACTION_BYTE,
	ACTION_INTERACTIVE,
	ACTION_INTERPRETER,
};

/// @brief flag ids
enum id {

	// single flags
	_EXPR_BEFORE,
	_BYTE,
	_EXPR_AFTER,
	_HELP,
	_INTERACTIVE,
	_MODULE,
	_SOURCE,
	_VERSION,

	// double flags
	// TODO: as of 202207062339, they are all just alternatives,
	// so we don't need to repeat ourselves
	
	// compound flags
	_I_COLOR,
};

typedef enum ftype Ftype;
typedef enum action Action;

// `struct arg_data`
struct arg_file {
	FILE *this;
	Ftype ftype;
};

typedef struct arg_file ArgFile;

/// @brief sdread's argument data interface
struct arg_data {
	ArgFile *file; // this is actually an array (malloc is used)
	unsigned int fnum;
};

typedef struct arg_data ArgData;

/// @brief exit status for sdread
/// @note any other error that isn't
///       at top level exits with
///       its corresposing error exit
///       code at <sd/utils/err/err.h>
enum exit {
	EOK = 0, ///< @brief default success
	EBADARG,
	ENOSUCHFILE,
	EMISSFILE,
	EMISSARG,
};

/// @brief exit status for parseargs

typedef struct promise Promise;
typedef enum exit Exit;

#  define file_is_source(x) (x == SOURCE_DISK | x == SOURCE_FIFO)
#  define file_is_bytecode(x) (x == BYTECODE_DISK | x == BYTECODE_FIFO)
#  define file_is_fifo(x) (x == BYTECODE_FIFO || x == SOURCE_FIFO)

// help message
#  define HELP \
MADEBY ("mH", "https://github.com/matthmr") \
DESCRIPTION ("sdread", "The standard SD interpreter") \
USAGE ( \
	FLAG_VAL ("sdread", "byte", "b", "<file...>", "Streams a bytecode file") \
	FLAG_VAL ("sdread", "source", "s", "<file...>", "Streams a plain-text source file (used to override `--byte')") \
	FLAG_VAL ("sdread", "mod", "m", "<mod...>", "Runs the `main' procedure of `mod'") \
	FLAG_VAL ("sdread", "expr", "e", "<expr...>", "Parses `expr' and executes it after parsing the file") \
	FLAG_VAL ("sdread", "Expr", "E", "<expr...>", "Parses `expr' and executes it before parsing the file") \
	FLAG_NOVAL ("sdread", "int", "i", "Runs in interactive mode") \
	"\n" \
	FLAG_NOVAL ("sdread", "help", "h", "Displays this message and exits") \
	FLAG_NOVAL ("sdread", "version", "v", "Displays the version and exits") \
) \
MORE ("sdread(1)")

#endif

#ifndef LOCK_DATA
#  define LOCK_DATA

#  include <sd/intr/limits.h>

extern unsigned char data[FBUFFER];
// extern char* eol;

#endif
