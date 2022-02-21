/**
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/intr/txt/ptree/ptree.h>

#include <sd/utils/types/shared.h>

u16 promote = 8;

static void (*data) (void);

void data (void) {
	static u16 ptree_promote = promote;
	heap (gd_ctxt.ty.bits);
}
