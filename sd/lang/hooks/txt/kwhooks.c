/**
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for keywords
 */

#include <string.h>

#include <sd/lang/tokens/utils/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/err.h>
#include <sd/utils/utils.h>

static void kwty_builtin_obj (txt_Kw);
static void kwty_builtin_ty (txt_Kw);
static void kwty_obj_def (txt_Kw);
static void kwty_qual (txt_Kw);
static void kwty_flow (txt_Kw);
static void kwty_env (txt_Kw);
static void kwty_acc (txt_Kw);

inline void kwty_obj_def (txt_Kw kw) {

	switch (kw.id) {
	case _LET:
		push_obj (OBJ);
		expect (ASSIGN);
		break;
	case _PROC:
		push_obj (PROC);
		expect (ASSIGN);
		break;
	case _TYPE:
		push_obj (TYPE);
		expect (ASSIGN);
		break;
	}

}

void kwty_builtin_obj (txt_Kw kw) {}
void kwty_builtin_ty (txt_Kw kw) {}
void kwty_qual (txt_Kw kw) {}
void kwty_flow (txt_Kw kw) {}
void kwty_env (txt_Kw kw) {}
void kwty_acc (txt_Kw kw) {}

_akw_handler akw_handler[] = {
	[KWTY_BUILTIN_OBJ] = &kwty_builtin_obj,
	[KWTY_BUILTIN_TY] = &kwty_builtin_ty,
	[KWTY_OBJ_DEF] = &kwty_obj_def,
	[KWTY_QUAL] = &kwty_qual,
	[KWTY_FLOW] = &kwty_flow,
	[KWTY_ENV] = &kwty_env,
	[KWTY_ACC] = &kwty_acc,
};
