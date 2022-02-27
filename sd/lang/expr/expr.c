/**
 * This file contains utils
 * for making a generic
 * parse tree on demand
 */

#include <sd/lang/core/bitmap/masks.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>

Expr g_expr;

static void expr_expect (enum sync);
static void expr_exec (void);

inline void expr_expect (enum sync) {
	tab.buffer (sync_masks[SYNC_LET]);
}

void expr_exec (void) {

}
