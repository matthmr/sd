/**
 * This file contains generic limits
 * for the SD interpreters
 */

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

static const unsigned short int LINE_LIMIT = (1 << 16) - 1;
static const unsigned short int CHILDREN_LIMIT = (1 << 16) - 1;

#endif
