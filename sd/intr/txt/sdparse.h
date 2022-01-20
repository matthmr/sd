/**
 * This file contains all type
 * definitions needed for parsing
 * and executing plain-text sd
 * source code.
 */

#include <sd/utils/types/shared.h>

#ifndef LOCK_PARSE
#  define LOCK_PARSE

#  include <sd/lang/core/obj.h>
#  include <sd/lang/langutils.h>
#  include <sd/lang/lang.h>

// -- `nfind_def` exit status -- //
#  define not_found 0
#  define found 1
#  define token 2
#  define literal 3
#  define repeats 4

// -- `direction` values -- //
#  define up_down 1
#  define down_up 2

static bool direction;

bool nfind_def (uint*, char);

/// TODO: maybe some upper / lower bound check is needed?
#  define s_comp(x,y) (direction == down_up)? x >= y: x <= y
#  define s_advance(x) (direction == down_up)? x--: x++
#  define s_regress(x) (direction == down_up)? x++: x--

void parser_stream (char**, Obj*);

uint litsize_offset (uint*, char*);

#endif

#ifndef LOCK_STACK
#  define LOCK_STACK

/* This is the main wrappable function */
void parse_src (FILE*, char*, uint);

#endif
