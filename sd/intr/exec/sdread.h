/**
 * This file contains promises
 * set for parser frontends
 * and misc data for sdread
 * frontend
 */

#define VERSION "v0.3.2"

#ifndef LOCK_READ
#  define LOCK_READ

#  define HELP "\nMade by mH (https://github.com/matthmr)\n"\
               "\tsdread\t\t\t  => The standard SD interpreter\n\n"\
               "Usage:\tsdread - \"<expr>\"\t  => read from STDIN\n"\
               "\tsdread <file> \"<expr>\"\t  => <file> is SD source code\n"\
               "\tsdread -s <file> \"<expr>\" => <file> is SD bytecode code (compiled)\n\n"\
               "Info:\tsdread -h\t\t  => Displays this message and exits\n"\
               "\tsdread -v\t\t  => Displays the version and exits\n\n"\
               "Note:\t\"<expr>\" is optional but must be used in quotes\n\n"\

#  define PROMPT "> "
#  define NL_PROMPT "~ "

enum ftype {
	SOURCE,
	BYTECODE
};

#endif
