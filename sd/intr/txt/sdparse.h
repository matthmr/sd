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

extern const _Kw keyword_manifest[];
extern const _T token_manifest[];

void parser_stream (char**, Obj*);
uint litsize_offset (uint*, char*);

#endif

#ifndef LOCK_STACK
#  define LOCK_STACK

/* This is the main wrappable function */
void parse_src (FILE*, char*, uint);

#endif
