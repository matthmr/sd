/**
 * This file contains types CAN be shared
 * through all files; binary agnostic.
 */

#ifndef NULL
#  define NULL (void*)0x0
#endif

#ifndef LOCK_TYPES
#  define LOCK_TYPES

typedef unsigned char bool;
typedef unsigned char _bool;
typedef unsigned char byte;
typedef unsigned char ins;

#endif

#ifndef LOCK_BOOLEAN
#  define LOCK_BOOLEAN

#  define true 0b1
#  define false 0b0

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
#if ADDR_BITS == 64
typedef unsigned long u64;
typedef unsigned long d_addr;
#else
typedef unsigned int d_addr;
#endif

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

#  define ASCII_NUM_OFFSET 0x30
#  define ASCII_LHEX_OFFSET 0x57
#  define ASCII_UHEX_OFFSET ASCII_LHEX_OFFSET - ASCII_CASE_OFFSET
#  define ASCII_CASE_OFFSET 0x20

#endif

#ifndef LOCK_MEMMACROS
#  define LOCK_MEMMACROS

#  define MEMSIZE(x) sizeof (x) / sizeof (*x)

#endif
