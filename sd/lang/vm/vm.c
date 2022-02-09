/**
 * This file contains the
 * implementations for
 * the SD vm
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/vm/vm.h>

typedef void (*fn_ptr) (void*);

byte mem[DEF_MEM_ALLOC];
byte reg[DEF_REG_ALLOC];

static ulint curr_avail_mem = DEF_MEM_ALLOC; // max of ~4G of ram per process, using base of 1M
static ulint stack_ceiling = DEF_STACKMEM_ALLOC; // max of ~1G of stack ram per process, using base of 250K
static ulint heap_ceiling = DEF_HEAPMEM_ALLOC; // max of ~3G of heap ram per process, using base of 750K

stack_type* sp = mem;

inline byte* pop (void) {
	byte* csp = sp;
	--sp;
	return csp;
}

inline void push (byte* blk, uint size) {
	sp += size;
}

inline void* pop_frame (uint blksize) {
	sp -= blksize;
}

inline void push_frame (uint blksize, fn_ptr stack_hook) {
	sp += blksize;
	stack_hook ();
}

inline void* pop_t (uint blksize) {

}

inline void push_t () {

}
