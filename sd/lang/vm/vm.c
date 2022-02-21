/**
 * This file contains the
 * implementations for
 * the SD vm
 */

#include <sd/utils/types/shared.h>

#define LOCK_LITERALFN
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/vm/vm.h>

byte mem[MEM];
u64 reg[REGL_N + REGE_N + REGC_N];

u64 regl[REGL_N];
u64 rege[REGE_N];

u64 curr_avail_mem;
u64 stack_ceiling;
u64 heap_ceiling;

u64 mem_goffset = (u64) &mem;
u64 mem_goffset_top;

byte* heapp;
byte* sp;
byte* ip;

byte* s_bot;
byte* s_top;

void ip_next (void) {
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
	s_top = mem+stack_ceiling;

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
	push_tab ( tab.let() );
	tab.chroot ();

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

// signed by default
inline void* pop_t (enum int_t ty) {
	if (ty == _u16 || ty == _i16) {
		sp -= 2;
		return (short*) sp;
	}
	else if (ty == _u32 || ty == _i32) {
		sp -= 4;
		return (int*) sp;
	}
	else if (ty == _u64 || ty == _i64) {
		sp -= 8;
		return (long*) sp;
	}
	else {
		sp -= 4;
		return (float*) sp;
	}
}

inline void push_t (union int_t ty, void* data)  {

	switch (ty) {
	case _u16: *(unsigned short*) sp = *(unsigned short*) data; break;
	case _u32: *(unsigned int*) sp = *(unsigned int*) data; break;
	case _u64: *(unsigned long*) sp = *(unsigned long*) data; break;

	case _i16: *(short*) sp = *(short*) data; break;
	case _i32: *(int*) sp = *(int*) data; break;
	case _i64: *(long*) sp = *(long*) data; break;

	case _f32: *(float*) sp = *(float*) data; break;
	}

	sp += t_size;
}

inline void push_tab (Normal c) {
	*ip = c;
	ip++;
}

inline void* pop_frame (uint blksize) { }

inline void push_frame (uint blksize, void* data) { }

inline void heap (uint t_size) {
	*heapp += t_size;
}
