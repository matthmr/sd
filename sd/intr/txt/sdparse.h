/**
 * This file contains all type
 * definitions needed for parsing
 * and executing plain-text sd
 * source code.
 */

#include <sd/utils/types/shared.h>

#ifndef LOCK_PARSE
#  define LOCK_PARSE

#  include <sd/lang/tree/ot.h>

void next (char*, uint*, uint*, bool*, const uint);
void parser_stream (char*, Obj*);
void number_offset (uint*, char*);

#endif

#ifndef LOCK_STACK
#  define LOCK_STACK

/* This is the main wrappable function */
void parse_src (FILE*, char*, uint);

#endif
