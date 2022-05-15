/**
 * This file contains the
 * implementations for
 * the SD vm table
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/core/bitmap/bitmap.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/vm/vm.h>

#include <sd/intr/limits.h>

byte tab_index_buffer[5]; // 4 + 4*7 = 32 bits

static ALIGN_AS(unsigned) goid;

Tab tab = {
	.root = NULL,
	.head = NULL,
	.gidn = 0,
	.gid = 0,
};
