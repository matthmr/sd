/**
 * @file sdparse.h
 *
 * @brief `sdread`'s plain-text source code backend
 *
 * This file contains type definitions
 * needed for parsing and executing
 * plain-text sd source code.
 */

#include <sd/utils/types/shared.h>

#ifndef LOCK_PARSE
#  define LOCK_PARSE ///< lock: lock function interface

//#  include <sd/lang/obj/ot.h>

void next (char*, uint*, uint*, bool*, const uint);
void parser_stream (char*, uint);

#endif

#ifndef LOCK_STACK
#  define LOCK_STACK

void parse_src (FILE*, char*, uint);

#endif

#ifndef LOCK_VERBOSITY
#  define LOCK_VERBOSITY ///< lock: lock verbose metadata (line number, etc...)

extern uint ln;
extern uint wstart_i;
extern uint wsize;

#endif
