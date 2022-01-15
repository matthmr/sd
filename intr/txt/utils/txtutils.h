/**
 * This files contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS

#  include "../../../utils/types/shared.h"

#  define DELIMITER ':' /// assignment token

extern uint offset;

bool streq (char*, const char*);
void getname (char**, uint*, char*, uint, char);

#endif
