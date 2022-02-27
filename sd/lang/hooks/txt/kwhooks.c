/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for keywords
 */

#include <string.h>

#include <sd/lang/tokens/utils/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/vm/tab/tab.h>
#include <sd/lang/expr/expr.h>
#include <sd/lang/tree/ot.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/verr.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

static void kwty_builtin_obj (_Kw);
static void kwty_builtin_ty (_Kw);
static void kwty_obj_def (_Kw);
static void kwty_qual (_Kw);
static void kwty_flow (_Kw);
static void kwty_env (_Kw);
static void kwty_acc (_Kw);
static void kwty_loop (_Kw);

void kwty_obj_def (_Kw kw) {

	switch (kw.ty) {
	case _LET:
		if (! tab.head)
			expr_expect (SYNC_OBJ);
		else
			vErr (0x03, NULL);
		break;
	case _PROC:
		if (! tab.head)
			expr_expect (SYNC_PROC);
		else
			vErr (0x03, NULL);
		break;
	}

}

void kwty_builtin_obj (_Kw kw) {
	if (kw.id == _THIS); // this
		//
	else { // nil
		//
	}
}

void kwty_builtin_ty (_Kw kw) {}
void kwty_qual (_Kw kw) {}
void kwty_flow (_Kw kw) {}
void kwty_env (_Kw kw) {}
void kwty_acc (_Kw kw) {}
void kwty_loop (_Kw kw) {}

_akw_handler akw_handler[] = {
	[KWTY_BUILTIN_OBJ] = &kwty_builtin_obj,
	[KWTY_BUILTIN_TY] = &kwty_builtin_ty,
	[KWTY_OBJ_DEF] = &kwty_obj_def,
	[KWTY_QUAL] = &kwty_qual,
	[KWTY_FLOW] = &kwty_flow,
	[KWTY_LOOP] = &kwty_loop,
	[KWTY_ENV] = &kwty_env,
	[KWTY_ACC] = &kwty_acc,
};
