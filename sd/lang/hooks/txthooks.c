/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form
 */

#include <string.h>

#include <sd/lang/utils/langutils.h>
#include <sd/lang/hooks/txthooks.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

bool lock_stream = false;
txt_Ctxt g_ctxt;

// -- `tty` -- //
void tty_obj_ref_del (_T _t) { }

void tty_obj_ref (_T _t) { }

void tty_obj_def (_T _t) { }

void tty_expr_hook (_T _t) { }

void tty_syn_hook (_T _t) {

	switch (_t.t) {
	case '#':
		lstream (H_LOCK (g_ctxt.cmt));
		break;
	case '"':
		lstream (H_LOCK (g_ctxt.str));
	case '^':
		break;
	}

	// TODO: resolute `^` as dereferencing `_`

}

_at_handler at_handler[5] = {
	[TTY_OBJ_REF_DEL] = &tty_obj_ref_del,
	[TTY_OBJ_REF] = &tty_obj_ref,
	[TTY_OBJ_DEF] = &tty_obj_def,
	[TTY_EXPR] = &tty_expr_hook,
	[TTY_SYN] = &tty_syn_hook
};
// -- `tty` -- //

// -- `kwty` -- //
// _akw_handler akw_handler[] {  };
// -- `kwty` -- //
