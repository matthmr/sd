/**
 * @file limits.h
 *
 * @brief limits for SD and the SDVM
 *
 * This file contains generic limits
 * for the SD interpreters and other
 * utilities such as
 *  - SD compilers
 *  - SDVM `memmgrs`
 */

#ifndef ADDR_BITS
#  define ADDR_BITS 64 ///< memory address size fallback
#endif

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS ///< lock: standard lock

#  include "utils/types/shared.h"
#  include "utils/macros.h"

// size utils
#  define KiB * POW2 (10) *b
#  define MiB * POW2 (10) *KiB
#  define GiB * POW2 (10) *MiB

#  define FBUFFER 4 KiB     ///< buffer size for SD source code text

// standards
#  define STDBUFFER FBUFFER
#  define STDWORD 8        ///< word size; used to lengthen the word buffer
#  define STDUWORD 64      ///< uword size; used to lengthen the uword buffer
#  define STDOBJ MAX_OF (unsigned int) ///< maximum number of children per object; set to 0xffffffff

#endif
