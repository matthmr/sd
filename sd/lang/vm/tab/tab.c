/**
 * This file contains the
 * implementations for
 * the SD vm table
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/core/bitmap/bitmap.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/vm/vm.h>

Normal normal_buffer[5]; // 4 + 4*7 = 32 bits

static u64 goid;
static uint nbindex;

Normal* let (void) { }

void buffer (byte mask) {
	normal_buffer[nbindex] |= mask;
	nbindex++;
}

/*inline void chroot (addr addr) {
	g_self = addr;
}*/

Tab tab = {
	.let = &let,
	.proc = NULL,
	.heap_data = NULL,
	.head = NULL,
	.chroot = NULL,
	.buffer = &buffer,
};
