/**
 * This file contains generic limits
 * for the SD interpreters
 */

#ifndef ADDR_BITS
#  define ADDR_BITS 32 /* fallback to 32 bits */
#endif

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

#  define LOCK_UTILS
#  include <sd/utils/types/shared.h>
#  include <sd/utils/utils.h>
#  undef LOCK_UTILS

#  define BUFFER 1024*b
#  define STDBUFFER BUFFER
#  define STDWORD 8
#  define STDUWORD 64

#  define STDOBJ MAX_OF

#endif
