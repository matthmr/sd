/**
 * This file contains all type
 * definitions needed for parsing
 * and executing plain-text sd
 * source code.
 */

#ifndef LOCK_PARSE
#  define LOCK_PARSE

#  define LOCK_TYPES
#  undef LOCK_UNSIGNED_INT

#  include "../../utils/sharedtypes.h"

// -- `t_find` exit status -- //
#  define not_found 0
#  define found 1
#  define token 2
#  define number 3
#  define repeats 4

// -- `direction` values -- //
#  define up_down 1
#  define down_up 2

static bool direction;
static uint offset;

bool t_find_def (char);

/// TODO: maybe some upper / lower bound check is needed?
#  define s_comp(x,y) (direction == down_up)? x >= 0: x < y
#  define s_advance(x) (direction == down_up)? x--: x++
#  define s_regress(x) (direction == down_up)? x++: x--

void StreamParser (char**);

#endif

#ifndef LOCK_STACK
#  define LOCK_STACK

#  define LOCK_TYPES
#  undef LOCK_UNSIGNED_INT

#  include "../../utils/sharedtypes.h"

/* This is the main wrappable function */
void StartParse (FILE*, char*, uint,
                 int, char**);

#endif
