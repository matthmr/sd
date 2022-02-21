/**
 * This file contains generic limits
 * for the SD interpreters
 */

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS

#  define NEWLINE_BUFFER_LIMIT (1 << 16) - 1
#  define GBUFFER_M1 (1 << 16)

static const unsigned short int LINE_LIMIT = (1 << 16) - 1;
static const unsigned short int BCLINE_LIMIT = (1 << 16) - 1;
static const unsigned short int CHILDREN_LIMIT = (1 << 16) - 1;

#endif
