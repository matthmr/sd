/**
 * @file shared.h
 *
 * @brief shared macros and utils
 *
 * This file contains types can be shared
 * through all files; interface agnostic.
 */

#ifndef NULL
#  define NULL ((void*)0x0)
#endif

#ifndef LOCK_8BIT_TYPES
#  define LOCK_8BIT_TYPES ///< lock: lock 8-bit length typedefs

typedef unsigned char bool;
typedef unsigned char byte;

#endif

#ifndef LOCK_BOOLEAN
#  define LOCK_BOOLEAN ///< lock: lock boolean

#  define true '\1'
#  define false '\0'

#endif

#ifndef LOCK_BYTE_TYPES
#  define LOCK_BYTE_TYPES ///< lock: lock multiple bit length typedefs

#  define LOCK_INTR_LIMITS
#  include <sd/intr/limits.h>
#  undef LOCK_INTR_LIMITS

typedef void* addr;
typedef unsigned int uint;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#  if ADDR_BITS == 64
typedef unsigned long u64;
typedef unsigned long d_addr;
typedef unsigned int d_addrl;
#  else
typedef unsigned int d_addr;
typedef unsigned int d_addrl;
#  endif

#endif

#ifndef LOCK_MEM
#  define LOCK_MEM ///< lock: lock memory utils

#  define b  1
#  define kb 1000
#  define mb 1000000
#  define gb 1000000000

#endif

#ifndef LOCK_MAGICN
#  define LOCK_MAGICN ///< lock: lock magic numbers

#  define ASCII_NUM_OFFSET 0x30  ///< positive offset from ASCII to decimal (IF VALID)
#  define ASCII_LHEX_OFFSET 0x57 ///< positive offset from ASCII lowercase hex to decimal
#  define ASCII_UHEX_OFFSET 0x37 ///< positive offset from ASCII uppercase hex to decimal
#  define ASCII_CASE_OFFSET 0x20 ///< positive offset from ASCII uppercase to lowercase; negative otherwise

#endif
