/**
 * This file contains types CAN be shared
 * through all files; binary agnostic.
 */

#ifndef LOCK_TYPES
#  define LOCK_TYPES

typedef unsigned char bool;
typedef unsigned char _bool;
typedef unsigned char byte;

#endif

#ifndef LOCK_BOOLEAN
#  define LOCK_BOOLEAN

#  define true 0b1
#  define false 0b0

#endif

#ifndef LOCK_UNSIGNED_INT
#  define LOCK_UNSIGNED_INT

typedef unsigned int uint;
typedef unsigned short int usint;
typedef unsigned long int ulint;

#endif

#ifndef LOCK_MEM
#  define LOCK_MEM

#  define b  1
#  define kb 1000
#  define mb 1000000
#  define gb 1000000000

#endif
