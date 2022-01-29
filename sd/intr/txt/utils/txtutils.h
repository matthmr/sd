/**
 * This files contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS

#  include <sd/utils/types/shared.h>
#  include <sd/lang/lang.h>

// -- `nfind_def` exit status -- //
#  define not_found 1
#  define found 2
#  define ttoken 3
#  define literal 4
#  define repeats 5

// -- `nbound_def` manifest type -- //
#  define KEYWORD_MANIFEST 0
#  define TOKEN_MANIFEST 1

// -- `nbound_def` exit status -- //
#  define npass 0
#  define nfound 1

extern uint t;

void offset_i (uint*, char*, const uint);
bool nbound_def (char, uint, uint*, uint*, bool);
bool tfind_def (char);
bool nfind_def (char);

#endif
