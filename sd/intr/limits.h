/**
 * This file contains generic limits
 * for the SD interpreters
 */

#ifndef ADDR_BITS
#  define ADDR_BITS 32 /* fallback to 32 bits */
#endif

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

#  include <sd/utils/types/shared.h>

#  ifdef LOCK_UTILS
#    include <sd/utils/utils.h>
#  else
#    define LOCK_UTILS
#    include <sd/utils/utils.h>
#    undef LOCK_UTILS
#  endif

#  define KiB POW2 (10)*b
#  define MiB POW2 (10)*KiB
#  define GiB POW2 (10)*MiB

#  define BUFFER 8*KiB
#  define STDBUFFER BUFFER
#  define STDWORD 8
#  define STDUWORD 64

#  define STDOBJ MAX_OF

#endif
