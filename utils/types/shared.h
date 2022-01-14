/**
 * This file contains types CAN be shared
 * through all files; binary agnostic.
 */

#ifndef LOCK_TYPES
#  define LOCK_TYPES
#endif

#ifndef LOCK_BOOLEAN
#  define LOCK_BOOLEAN

#  define true 0b1
#  define false 0b0
typedef unsigned char bool;
typedef unsigned char _bool;

#endif

#ifndef LOCK_UNSIGNED_INT
#  define LOCK_UNSIGNED_INT

typedef unsigned int uint;

#endif
