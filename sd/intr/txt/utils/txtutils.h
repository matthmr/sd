/**
 * This files contains utils
 * for parsing plain-text
 * SD source code
 */

#ifndef LOCK_TXT_UTILS
#  define LOCK_TXT_UTILS

#  include <sd/utils/types/shared.h>

#  define DELIMITER ':' /// assignment token

extern uint g_offset;

// TODO: void getuname (void);
void getinptr (uint*, char*, uint, char);

#endif
