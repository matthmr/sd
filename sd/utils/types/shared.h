/**
 * This file contains types CAN be shared
 * through all files; binary agnostic.
 */

#ifndef NULL
#  define NULL ((void*)0x0)
#endif

#ifndef LOCK_TYPES
#  define LOCK_TYPES

typedef unsigned char bool;
typedef unsigned char byte;

#endif

#ifndef LOCK_BOOLEAN
#  define LOCK_BOOLEAN

#  define true (char)1
#  define false (char)1

#endif

#ifndef LOCK_UNSIGNED_INT
#  define LOCK_UNSIGNED_INT

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
#  define LOCK_MEM

#  define b  1
#  define kb 1000
#  define mb 1000000
#  define gb 1000000000

#endif

#ifndef LOCK_MAGICN
#  define LOCK_MAGICN

#  define ASCII_NUM_OFFSET 0x30  // positive offset from ASCII to decimal (IF VALID)
#  define ASCII_LHEX_OFFSET 0x57 // positive offset from ASCII lowercase hex to decimal
#  define ASCII_UHEX_OFFSET 0x37 // positive offset from ASCII uppercase hex to decimal
#  define ASCII_CASE_OFFSET 0x20 // positive offset from ASCII uppercase to lowercase; negative otherwise

#endif

#ifndef LOCK_MEMMACROS
#  define LOCK_MEMMACROS

#  define BYTES(x) sizeof (x) / sizeof (*x)

#endif
