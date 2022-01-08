/**
 * This file contains limits for the
 * interpreters of SD
 */

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

#  undef LOCK_UNSIGNED_INT
#  include "../utils/sharedtypes.h"

static const uint LINE_LIMIT = 10000; /// 10 kb

#endif
