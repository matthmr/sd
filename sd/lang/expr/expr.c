/**
 * This file contains utils
 * for making a generic
 * parse tree on demand
 */

#include <sd/lang/core/bitmap/masks.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>

Expr g_expr;

inline void expr_expect (enum sync obj_type) {
	tab.buffer (sync_masks[obj_type]);
}

void expr_exec (void) { }
