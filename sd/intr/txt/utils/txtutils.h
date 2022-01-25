/**
 * This files contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS

#  include <sd/utils/types/shared.h>
#  include <sd/lang/lang.h>

#  define DELIMITER ':' /// assignment token

// -- `nfind_def` exit status -- //
#  define not_found 0
#  define found 1
#  define ttoken 2
#  define literal 3
#  define repeats 4

extern uint t;

extern const _Kw keyword_manifest[];
extern const _T token_manifest[];

void offset_i (uint*, uint*, char*, uint, char);
bool nfind_def (char);
bool tfind_def (char);

#endif
