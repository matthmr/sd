/**
 * This files contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS

#  include <sd/utils/types/shared.h>

#  define DELIMITER ':' /// assignment token

extern uint offset;

void getname (char**, uint*, char*, uint, char);
void getuname (/* TODO, */ uint*, char*, uint, char);

#endif
