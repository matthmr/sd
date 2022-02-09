/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for tokens, wrap-
 * ping around the parse tree
 */

#  include <sd/lang/hooks/txt/txthooks.h>
#  include <sd/lang/atom/atom.h>
#  include <sd/lang/vm/vm.h>
#  include <sd/lang/lang.h>

#  include <sd/utils/err/err.h>
#  include <sd/utils/utils.h>

static void tty_obj_ref_del (txt_T);
static void tty_bitwise_op (txt_T);
static void tty_bool_cmp (txt_T);
static void tty_obj_ref (txt_T);
static void tty_obj_def (txt_T);
static void tty_math_op (txt_T);
static void tty_bool_op (txt_T);
static void tty_expr (txt_T);
static void tty_syn (txt_T);

void tty_syn (txt_T t) {

	switch (t.t) {
	case '#':
		lstream (H_LOCK (gs_ctxt.cmt));
		break;
	case '"':
		lstream (H_LOCK (gs_ctxt.str));
	case '^':
		break;
	}

}

void tty_math_op (txt_T t) {
	switch (t.t) {
	case '+':
		atom.math[PLUS] (stack);
		break;
	case '*':
		atom.math[TIMES] (stack);
		break;
	case '-':
		atom.math[MINUS] (stack);
		break;
	case '%':
		atom.math[MOD] (stack);
		break;
	}
}

void tty_bitwise_op (txt_T t) {

	switch (t.t) {
	case '~':
		atom.bit[BWNOT] (stack);
		break;
	case '&':
		atom.bit[BWAND] (stack);
		break;
	case '|':
		atom.bit[BWOR] (stack);
		break;
	}

}

void tty_obj_ref_del (txt_T t) {}
void tty_bool_cmp (txt_T t) {}
void tty_obj_ref (txt_T t) {}
void tty_obj_def (txt_T t) {}
void tty_bool_op (txt_T t) {}
void tty_expr (txt_T t) {}

_at_handler at_handler[] = {
	[TTY_OBJ_REF_DEL] = &tty_obj_ref_del,
	[TTY_BITWISE_OP] = &tty_bitwise_op,
	[TTY_BOOL_CMP] = &tty_bool_cmp,
	[TTY_OBJ_REF] = &tty_obj_ref,
	[TTY_OBJ_DEF] = &tty_obj_def,
	[TTY_MATH_OP] = &tty_math_op,
	[TTY_BOOL_OP] = &tty_bool_op,
	[TTY_EXPR] = &tty_expr,
	[TTY_SYN] = &tty_syn,
};

