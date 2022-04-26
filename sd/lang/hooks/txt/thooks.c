/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for tokens, wrap-
 * ping around the parse tree
 */


#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/lang.h>

#define LOCK_PARSE
#define LOCK_STACK
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>

#include <sd/utils/err/verr.h>
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
		break;

	case '^':
		break;
	}

}

// @operator syntax: moslty infix, unary prefix
void tty_math_op (_T t) {

	// infix test: one child and non-null driver == non-unary operator == waiting for another driver
	if (ptree.curr.children == 1 && ptree.curr.high->item._.driver != DRIVER_NULL)
		;//ERR

	switch (t.t) {
	case '+':
		ptree.curr.children
			? ptree_add_op (OP_MATHPLUS)
			: ptree_add_uop (OP_UMATHPLUS);
		break;

	case '*':
		ptree_add_op (OP_MATHTIMES);
		break;

	case '-':
		ptree.curr.children
			? ptree_add_op (OP_MATHMINUS)
			: ptree_add_uop (OP_UMATHMINUS);
		break;

	case '%':
		ptree_add_op (OP_MATHMOD);
		break;
	}
}

// @operator syntax: moslty infix, unary prefix
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

	case '(':
		break;

	case ')':
		break;

	case '[':
		ptree_bracket_open ();
		break;

	case ']':
		if (!ptree.curr.bracket) // extra bracket
			;//ERR

		ptree_bracket_close ();
		break;

	case ',':
		break;
	}

}

void tty_bool_cmp (_T t) {} // has doubles

// @operator syntax: moslty infix, unary prefix
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

void tty_bool_op (_T t) {} // doubles

void tty_expr (_T t) {

	switch (t.t) {
	case ';':
		if (ptree.curr.bracket) // missing closing bracket
			vErr (0x0a, "]", "");
		else
			ptree_exec ();
		break;

	case '^':
		break;
	}

}

const _at_handler at_handler[] = {
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
