/**
 * This file contains generic limits
 * for the SD interpreters
 */

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

#  define LOCK_UTILS
#  include <sd/utils/types/shared.h>
#  include <sd/utils/utils.h>
#  undef LOCK_UTILS

#  define BUFFER 1024*b

#  ifndef ADDR_BITS
#    define ADDR_BITS 64
#  endif

static const u32 STDBUFFER = BUFFER;
static const u32 STDWORD = 8;
static const u32 STDUWORD = 64;

#if ADDR_BITS == 64
	static const u64
#else
	static const u32
#endif

STDOBJ = MAX_OF (ADDR_BITS);

#endif
