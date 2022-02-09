/**
 * This file contains type definitions
 * for the SD vm
 */

#ifndef LOCK_VM
#  define LOCK_VM

#  include <sd/utils/types/shared.h>

#  define DEF_MEM_ALLOC 1*mb
#  define DEF_REG_ALLOC 16 * 8 * b

#  define DEF_STACKMEM_ALLOC 250*kb
#  define DEF_HEAPMEM_ALLOC 750*kb

#  define MID_MEM_ALLOC 10*mb
#  define HIGH_MEM_ALLOC 100*mb
#  define VERY_HIGH_MEM_ALLOC 1*gb

extern byte mem[];
extern byte reg[];

extern byte* sp;

byte* pop (void);
void push (byte*, uint);

void* pop_frame (uint);
void push_frame (uint, void (*) (void*));

void* pop_t (uint);
void push_t (uint);
#endif
