/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for tokens, wrap-
 * ping around the parse tree
 */

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/atom/atom.h>
#include <sd/lang/vm/vm.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/cast.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

static void tty_obj_ref_del (_T);
static void tty_bitwise_op (_T);
static void tty_bool_cmp (_T);
static void tty_obj_ref (_T);
static void tty_obj_def (_T);
static void tty_math_op (_T);
static void tty_bool_op (_T);
static void tty_expr (_T);
static void tty_syn (_T);

void tty_syn (_T t) {

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

void tty_math_op (_T t) {
	switch (t.t) {
	case '+':
		break;

	case '*':
		break;

	case '-':
		break;

	case '%':
		break;
	}
}

void tty_bitwise_op (_T t) {

	switch (t.t) {
	case '~':
		break;

	case '&':
		break;

	case '|':
		break;
	}

}

void tty_obj_ref_del (_T t) {

	switch (t.t) {

	case '>':
		break;

	case '<':
		break;

	}

}

void tty_bool_cmp (_T t) {}

void tty_obj_ref (_T t) {

	switch (t.t) {
	case '/':
		break;
	case '@':
		break;
	case '.':
		break;
	}

}

void tty_obj_def (_T t) {

	switch (t.t) {
	case ':':
		break;
	case '{':
		break;
	case '}':
		break;
	}

}

void tty_bool_op (_T t) {}

void tty_expr (_T t) {

	switch (t.t) {

	case ';':
		expr_exec ();
		break;

	case '^':
		break;

	}

}

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
