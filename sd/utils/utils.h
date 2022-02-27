/**
 * This file contains basic / useful
 * functionality that are used throughout
 * the resolution of symbols; language
 * agnostic
 */

#ifndef LOCK_UTILS
#  define LOCK_UTILS

void Die (char*, const char*, char*, int);
void War (char*, const char*, char*);
#endif

#ifndef  LOCK_MACROS
#  define LOCK_MACROS

#  define NUMBER(X) (X) >= '0' && (X) <= '9'
#  define NUMBER_HEX(X) ((X) >= '0' && (X) <= '9') || ((X) >= 'a' && (X) <= 'f')
#  define NUMBER_BIN(X) (X) == '0' || (X) == '1'
#  define NUMBER_OCT(X) (X) >= '0' && (X) <= '7'
#  define LOWER_ALPHA(X) (X) >= 'a' && (X) <= 'z'
#  define UPPER_ALPHA(X) (X) >= 'A' && (X) <= 'Z'
#  define VALID(X) (LOWER_ALPHA(X) || UPPER_ALPHA(X) || (X) == '_')
#  define WHITESPACE(X) ((X) == 0x20 || (X) == 0x0a || (X) == 0x09 || (X) == 0x00)
#  define ATOI(X) (!(NUMBER(X)))? 0: (X) - 48
#  define TOGGLE(X) (X) = (X)^1
#  define LOCK(X) if (!X) (X)=1
#  define RESET(X) if (X)  (X)=0
#  define H_LOCK(X) (X)=1
#  define H_RESET(X) (X)=0
#  define E_LOCK(X,Y) if (!X) (X)=(Y)
#  define MAX_OF(X) (((unsigned)(1<<(X-1))-1)<<1)+1

#endif
