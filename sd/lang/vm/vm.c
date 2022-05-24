/**
 * @file vm.c
 *
 * @brief SDVM implementation
 *
 * This file contains the
 * implementations for
 * the SDVM
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

void push8 (u8 val) {
	*sp = 1;
	sp += 1 / (ADDR_BITS / 8);
}

void push_tab (byte c) {
	*ip = c;
	ip++;
}

void* pop_frame (uint blksize) { }
void push_frame (uint blksize, void* data) { }

void push_reg (d_addr regv) { }
d_addr* pop_reg (void) { }

void mov_rege (u64 val) { }
void mov_regl (u64 val) { }
