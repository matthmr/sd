/**
 * @file txtutils.h
 *
 * @brief plain-text source code utilities
 *
 * This file contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS ///< lock: standard lock

#  include <sd/lang/tokens/groups.h>

#  include "utils/types/shared.h"

#  define not_found 1 ///< (`nfind_def`): if not found
#  define found 2 ///< (`nfind_def`): if found to be word
#  define ttoken 3 ///< (`nfind_def`): if found to be a token
#  define number 4 ///< (`nfind_def`): if found to be a number
#  define repeats 5 ///< (`nfind_def`): if found to be a word but needs differentiation

#  define KEYWORD_MANIFEST 0 ///< (`nbound_def`): as a keyword
#  define TOKEN_MANIFEST 1 ///< (`nbound_def`): as a token

#  define npass 0 ///< (`nbound_def`): if exhausted seek space (normal case)
#  define nfound 1 ///< (`nbound_def`): if had an **exact** match (best case)

#  define BLOCK_SIZE 4 ///< (`nbount_def`): block size

extern uint t;

void number_offset (uint*, char*);
bool number_base (char, uint);

bool nbound_def (char, uint, uint*, uint*, bool);
void offset_i (uint*, char*, const uint);
bool tfind_def (char);
bool nfind_def (char);

#endif
