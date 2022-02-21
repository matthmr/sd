/**
 * This file contains type definitions
 * for the SD vm
 */

#ifndef LOCK_VM
#  define LOCK_VM

#  include <sd/utils/types/shared.h>

#  define MEM 10*kb

#  define MEM_TAB 6*kb
#  define MEM_HEAP 1*kb
#  define MEM_STACK 3*kb

#  define M_MEM 1*mb
#  define H_MEM 10*mb
#  define HH_MEM 100*mb
#  define HHH_MEM 1*gb

#  define REGL_N 2
#  define REGE_N 2
#  define REGC_N 1

/*
 *   == memory layout ==
 *
 * [[ HIGH MEMORY ]]  (mem_goffset_top)
 * == HEAP ==    vvv
 * == TAB ==     vvv
 * == STACK ==   ^^^
 * [[ LOW MEMORY ]]   (mem_goffset)
 *
 */

extern byte mem[];
extern u64 reg[REGL_N + REGE_N + REGC_N];

extern u64 regl[REGL_N];
extern u64 rege[REGE_N];

extern u64 regc;

extern byte* heapp;
extern byte* sp;
extern byte* ip;

extern byte* s_bot;
extern byte* s_top;

extern u64 curr_avail_mem;
extern u64 stack_ceiling;
extern u64 heap_ceiling;

extern u64 mem_goffset;
extern u64 mem_goffset_top;

void vm_init (void);
void (*vm_kill) (void);

void ip_next (void);

void* pop (void);
void push (byte);

void* pop_t (uint);
void push_t (uint, void*);

void* pop_frame (uint);
void push_frame (uint, void*);

void heap (uint);

void push_tab (byte*);

void mov_rege (addr, u64);
void mov_regl (addr, u64);
#endif