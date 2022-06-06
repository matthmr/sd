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

#  define HELP "\nMade by mH (https://github.com/matthmr)\n"\
               "\tsdread\t\t\t  => The standard SD interpreter\n\n"\
               "Usage:\tsdread - \"<expr>\"\t  => read from STDIN\n"\
               "\tsdread <file> \"<expr>\"\t  => <file> is SD source code\n"\
               "\tsdread -s <file> \"<expr>\" => <file> is SD bytecode code (compiled)\n"\
               "\tsdread -m <file> \"<expr>\" => <file> is SD module\n\n"\
               "Info:\tsdread -h\t\t  => Displays this message and exits\n"\
               "\tsdread -v\t\t  => Displays the version and exits\n\n"\
               "Note:\t\"<expr>\" is optional but must be used in quotes\n"\
               "     \tRead more at sdread(1)\n\n"
#  define VERSION "v0.4.0"

/// @brief prompt for interactive mode
#  define PROMPT "> "
#  define NL_PROMPT "~ "

#  define file_is_source(x) (x >= SOURCE_DISK)
#  define file_is_bytecode(x) (x <= BYTECODE_FIFO)
#  define file_is_fifo(x) (x == BYTECODE_FIFO || x == SOURCE_FIFO)

// @brief file types for sdread arguments
enum ftype {
	BYTECODE_DISK,
	BYTECODE_FIFO,

	SOURCE_DISK,
	SOURCE_FIFO,
};

/// @brief promise types for sdread arguments
struct promise {
	enum ftype ftype;

	FILE* file;

	bool PFILE;
	bool HFILE;
};

extern struct promise p;

/// @brief exit status for sdread
enum exit {
	EXIT_OK = 0,
};

/// @brief exit status for parseargs
enum arg {
	ARG_ERR = -1,
	ARG_OK,
	ARG_DEF,
	ARG_INFO,
};

typedef struct promise promise;
typedef enum exit exit;
typedef enum arg arg;

#endif

#ifndef LOCK_DATA
#  define LOCK_DATA

#  include <sd/intr/limits.h>

extern unsigned char data[BUFFER];
// extern char* eol;

#endif
