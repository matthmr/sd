/**
 * This file contains
 * type definitions
 * for the SD vm
 */

#ifndef ADDR_BITS
#  define ADDR_BITS 32 /* fallback to 32 bits */
#endif

#ifndef LOCK_VM
#  define LOCK_VM

#  include <sd/utils/types/shared.h>

#  ifdef LOCK_UTILS
#    include <sd/utils/utils.h>
#  else
#    define LOCK_UTILS
#    include <sd/utils/utils.h>
#    undef LOCK_UTILS
#  endif

#  include <sd/intr/limits.h>

#  define tmphoststack d_addr* mstack

// #  define popvmstack asm ( "sub $8, %%rsp" __nl )

#  define mkvmstack \
	tmphoststack; \
	sp = mstack /* ; \
	popvmstack */

#  define MEM_INC 8*KiB

#  define MEM_TAB 8*KiB
#  define MEM_STACK 8*KiB

#  define M_MEM 32*MEM
#  define H_MEM 64*M_MEM
#  define HH_MEM 128*H_MEM
#  define HHH_MEM 256*HH_MEM

#  define REGL_N 2
#  define REGE_N 2
#  define REGC_N 1
#  define REGF_N 1
#  define REG_N REGL_N + REGE_N + REGC_N + REGF_N

extern byte* heap;
extern byte* tab;

extern uint heapsize;
extern uint tabsize;

extern d_addr* sp;
extern d_addr* ip;

extern d_addr* s_top;

extern d_addr reg[REG_N];

extern d_addr* regl;
extern d_addr* rege;
extern d_addr* regc;
extern d_addr* regf;

// -- memory layout -- //
void heap_alloc (int);
void tab_alloc (int);
void vm_init (void);

// -- flow -- //
void jump_ip (d_addr);
void call_ip (d_addr);
void ret (void);

// -- STACK -- //
void* pop (void);
void push (byte);

void* pop_reg (void);
void push_reg (d_addr);

// TODO: make a `push*` type for each and
//       every possible stack push
void* pop_t (uint);
void push_t (uint, void*);

void* pop_frame (uint);
void push_frame (uint, void*);

// -- TABLE -- //
void push_tab (byte);

// -- REGISTERS -- //
void mov_rege (
	#if ADDR_BITS == 64
		unsigned long
	#else
		unsigned int
	#endif
);

void mov_regl (
	#if ADDR_BITS == 64
		unsigned long
	#else
		unsigned int
	#endif
);
#endif
