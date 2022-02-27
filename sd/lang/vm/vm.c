/**
 * This file contains the
 * implementations for
 * the SD vm
 */

#include <sd/utils/types/shared.h>
#include <sd/utils/types/cast.h>

#define LOCK_LITERALFN
#define LOCK_EXPRFN
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/vm/vm.h>

byte mem[MEM];
u64 reg[REGL_N + REGE_N + REGC_N];

u64 regl[REGL_N];
u64 rege[REGE_N];

u64 curr_mem_ceiling;
u64 curr_stack_ceiling;
u64 curr_heap_ceiling;

u64 mem_goffset = (u64) &mem;
u64 mem_goffset_top;

byte* heapp;
byte* sp;
byte* ip;

byte* s_bot;
byte* s_top;

void jump_ip (void) {
	ip--;
	if (ip == sp)
		;// handle frame collision
}

void vm_init (void) {

	// -- set memory boundaries -- //
	curr_avail_mem = MEM;
	stack_ceiling = MEM_STACK;
	heap_ceiling = MEM - (MEM_TAB+MEM_STACK);

	// -- arrange pointers -- //
	s_bot = mem;
	s_top = mem+curr_stack_ceiling;

	ip = s_top+1;
	heapp = mem+(MEM-1);
	sp = s_bot;

	// -- set registers --/
	regl[0] = reg[0] = 0x0000000000000000;
	regl[1] = reg[1] = 0x0000000000000000;
	rege[0] = reg[2] = 0x0000000000000000;
	rege[1] = reg[3] = 0x0000000000000000;
	regc = reg[4] = 0x0000000000000000;

	// -- set global root -- //
	push_tab (tab.let());
	tab.chroot (CAST_addr ip);

}

void (*vm_kill) (void) = &vm_init;

inline void* pop (void) {
	sp--;
	return (void*) sp;
}

inline void push (byte c) {
	*sp = c;
	sp++;
}

/// signed by default
void* pop_t (bits bits) {

	if (bits <= bits_8c) { /* 8 bits */
		sp -= 1;
		return (char*) sp;
	}

	else if (bits == bits_16i) { /* 16 bits */
		sp -= 2;
		return (short*) sp;
	}

	else if (bits >= bits_32i && bits <=
		#if ADDR_BITS == 32
			bits_addr
		#elif ADDR_BITS == 64
			bits_map
		#endif
	) { /* 32 bits */
		sp -= 4;

		switch (bits) {
		case bits_32i: case bits_enum: case bits_map:
			return (int*) sp; break;
		case bits_32f:
			return (float*) sp; break;

		#if ADDR_BITS == 32
		case bits_addr:
			return (void*) sp; break;
		#endif

		}
	}

	#if ADDR_BITS == 64
	else if (bits >= bits_64l || bits <= bits_addr) { /* 64 bits */
		sp -= 8;

		switch (bits) {
		case bits_64l:
			return (long*) sp; break;
		case bits_64d:
			return (double*) sp; break;
		case bits_addr:
			return (void*) sp; break;
		}
		
	}
	#endif

}

void push_t (bits bits, void* data)  {

	if (bits <= bits_8c) { /* 8 bits */
		CAST_i8 sp = CAST_i8 data;
		sp += 1;
	}

	else if (bits == bits_16i) { /* 16 bits */
		CAST_i16 sp = CAST_i16 data;
		sp += 2;
	}

	else if (bits >= bits_32i && bits <=
		#if ADDR_BITS == 32
			bits_addr
		#elif ADDR_BITS == 64
			bits_map
		#endif
	) { /* 32 bits */

		switch (bits) {
		case bits_32i: case bits_enum: case bits_map:
		#if ADDR_BITS == 32
		case bits_addr:
		#endif
			CAST_i32 sp = CAST_i32 data; break;
		case bits_32f:
			CAST_f32 sp = CAST_f32 data; break;
		}

		sp += 4;
	}

	#if ADDR_BITS == 64
	else if (bits >= bits_64l || bits <= bits_addr) { /* 64 bits */

		switch (bits) {
		case bits_64l:
			CAST_i64 sp = CAST_i64 data;
		case bits_64d: case bits_addr:
			CAST_d64 sp = CAST_d64 data;
		}
		
		sp += 8;
	}
	#endif
}

void push_tab (Normal c) {
	*ip = c;
	ip++;
}

inline void* pop_frame (uint blksize) { }

inline void push_frame (uint blksize, void* data) { }

inline void heap (uint t_size) {
	*heapp += t_size;
}

void mov_rege (u64);
void mov_regl (u64);
