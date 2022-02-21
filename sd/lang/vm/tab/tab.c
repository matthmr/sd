/**
 * This file contains the
 * implementations for
 * the SD vm table
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/core/bitmap/bitmap.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/vm/vm.h>

Normal normal_buffer[10];

static Normal (*let) (void);
static Normal (*proc) (void);
static void (*buffer) (byte);

static u64 OGID;
static uint nbindex;

Normal* let (NormalRef r) { }

void buffer (byte b) {
	normal_buffer[nbindex] | b;
	i++;
}

Tab tab = {
	.let = &let,
	.proc = &proc,
	.heap_data = NULL,
	.head = NULL,
	.chroot = NULL,
	.buffer = &buffer,
};
