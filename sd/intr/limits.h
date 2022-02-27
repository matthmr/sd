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

static const u32 STDBUFFER = BUFFER;
static const u32 STDOBJ = MAX_OF (32*b);

#endif
