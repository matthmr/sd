/**
 * This file contains basic / useful
 * functionality that are used throughout
 * the resolution of symbols
 */

#ifndef LOCK_UTILS
#  define LOCK_UTILS

void Die (char*, const char*, char*, int);
void War (char*, const char*, char*);

#endif

#ifndef  LOCK_MACROS
#  define LOCK_MACROS

// numeric utils
#  define NUMBER(X) ((X) >= '0' && (X) <= '9')
#  define NUMBER_UHEX(X) ((X) >= 'A' && (X) <= 'F')
#  define NUMBER_LHEX(X) ((X) >= 'a' && (X) <= 'f')
#  define NUMBER_BIN(X) ((X) == '0' || (X) == '1')
#  define NUMBER_OCT(X) ((X) >= '0' && (X) <= '7')

// alphabetic utils
#  define LOWER_ALPHA(X) ((X) >= 'a' && (X) <= 'z')
#  define UPPER_ALPHA(X) ((X) >= 'A' && (X) <= 'Z')
#  define WHITESPACE(X) ((X) == 0x20 || (X) == 0x0a || (X) == 0x09 || (X) == 0x00)
#  define ATOI(X) (!(NUMBER(X)))? -1: (X) - 48

// language-specific utils
#  define VALID(X) (LOWER_ALPHA(X) || UPPER_ALPHA(X) || (X) == '_')
#  define VALIDN(X) (VALID(X) || NUMBER (X))

// general purpose utils
#  define TOGGLE(X) (X) = (X)^1
#  define LOCK(X) if (!X) (X)=1
#  define RESET(X) if (X)  (X)=0
#  define H_LOCK(X) (X)=1
#  define H_RESET(X) (X)=0
#  define MAX_OF(x) (x) 0|1 // as cast to `type`
#  define POW2(x) (unsigned)((unsigned)1 << x)
#  define BIT(x) POW2(x)

// string utils
#  define __nl "\t\n"

#endif
