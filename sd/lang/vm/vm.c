/**
 * This file contains the
 * implementations for
 * the SD vm
 */

#include <stdlib.h>

#include <sd/intr/limits.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/types/cast.h>

#define LOCK_EXPRFN
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/vm/vm.h>

// -- user memory -- //
byte* tab;
byte* heap;

// -- virtual registers -- //
d_addr reg[REG_N];

d_addr* regl;
d_addr* rege;
d_addr* regf;
d_addr* regc;

// -- program pointers -- //
d_addr* s_top;
d_addr* sp;
d_addr* ip;

uint heapsize;
uint tabsize;

void jump_ip (d_addr addr) { }
void call_ip (d_addr addr) { }
void ret (void) { }

void heap_alloc (int kib) {

	static u8 call;

	if (! call) {
		H_LOCK (call);
		heap = (byte*) malloc (kib*KiB);
		heapsize = (unsigned)kib;
	}
	else {
		heap = realloc (heap, heapsize+kib*KiB);
		heapsize += (unsigned)kib;
	}

}

void tab_alloc (int kib) {
	static u8 call;

	if (! call) {
		H_LOCK (call);
		tab = (byte*) malloc (kib*KiB);
		tabsize = (unsigned)kib;
	}
	else {
		tab = realloc (tab, tabsize+kib*KiB);
		tabsize += (unsigned)kib;
	}

}

void vm_init (void) {

	// -- set memory pointers -- //
	s_top = sp;

	// -- set registers --/
	reg[0] = reg[1] = // regl
	reg[2] = reg[3] = // rege
	reg[4] =          // regc
	reg[5] =          // regf
	0;

	regl = &reg[0];
	rege = &reg[2];
	regf = &reg[4];
	regc = &reg[5];
	
	// -- set global root -- //
	/*tab_mkroot (&tab);
	tab_push (tab.root);
	tab_chroot (tab.root);*/

	// -- allocate heap-like mem -- //
	heap_alloc (8*KiB);
	tab_alloc (8*KiB);

}

inline void* pop (void) { }
inline void push (byte c) { }

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
			bits_map
		#else
			bits_addr
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
		#if ADDR_BITS == 64
			bits_map
		#else
			bits_addr
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

void push_tab (byte c) {
	*ip = c;
	ip++;
}

inline void* pop_frame (uint blksize) { }

inline void push_frame (uint blksize, void* data) { }

void mov_rege (u64) { }
void mov_regl (u64) { }
