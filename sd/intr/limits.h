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
/// memory address size; can
/// be overwritten by `ADDR_BITS`
/// in the Makefile
#  define ADDR_BITS 64
#endif

#ifndef LOCK_INTR_LIMITS
#  define LOCK_INTR_LIMITS ///< lock: standard lock

#  include <sd/utils/types/shared.h>
#  include <sd/utils/utils.h>

#  define KiB POW2 (10) *b
#  define MiB POW2 (10) *KiB
#  define GiB POW2 (10) *MiB

#  define BUFFER 8*KiB     ///< buffer size for SD source code text
#  define STDBUFFER BUFFER ///< standard IO buffer size; set to BUFFER
#  define STDWORD 8        ///< word size; used to lengthen the word buffer
#  define STDUWORD 64      ///< uword size; used to lengthen the uword buffer
#  define STDOBJ MAX_OF (unsigned int) ///< maximum number of children per object; set to 0xffffffff

#endif
