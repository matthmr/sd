/**
 * This file contains promises
 * set for parser frontends
 * and misc data for sdread
 * frontend
 */

#ifndef LOCK_READ
#  define LOCK_READ

#  define HELP "\nMade by mH (https://github.com/matthmr)\n"\
               "\tsdread\t\t\t  => The standard SD interpreter\n\n"\
               "Usage:\tsdread - \"<expr>\"\t  => read from STDIN\n"\
               "\tsdread <file> \"<expr>\"\t  => <file> is SD source code\n"\
               "\tsdread -s <file> \"<expr>\" => <file> is SD bytecode code (compiled)\n\n"\
               "Info:\tsdread -h\t\t  => Displays this message and exits\n"\
               "\tsdread -v\t\t  => Displays the version and exits\n\n"\
               "Note:\t\"<expr>\" is optional but must be used in quotes\n\n"
#  define VERSION "v0.3.2"

// prompt for interactive mode
#  define PROMPT "> "
#  define NL_PROMPT "~ "

#  define FILE_IS_SOURCE(x) (x >= SOURCE_DISK)
#  define FILE_IS_BYTECODE(x) (x <= BYTECODE_FIFO)
#  define FILE_IS_FIFO(x) (x == BYTECODE_FIFO || x == SOURCE_FIFO)

enum ftype {
	BYTECODE_DISK,
	BYTECODE_FIFO,

	SOURCE_DISK,
	SOURCE_FIFO,
};

struct promise {
	enum ftype ftype;

	FILE* file;

	bool PFILE;
	bool HFILE;
};

extern struct promise p;

enum exit {
	EXIT_OK = 0,
};

enum arg {
	ARG_ERR = 1,
	ARG_OK = 0,
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
