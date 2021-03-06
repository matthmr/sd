/**
 * @file kwhooks.c
 *
 * @brief hooks for text keywords
 *
 * This file contains the
 * implementation for built-in
 * object hooks found in plain-
 * text form for keywords
 */

#include <string.h>

#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/tokens/groups.h>

#include "utils/err/err.h"

#define LOCK_PARSE
#define LOCK_STACK
#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/txt/sdparse.h>

static void kwty_builtin_obj (_Kw);
static void kwty_builtin_ty (_Kw);
static void kwty_obj_def (_Kw);
static void kwty_qual (_Kw);
static void kwty_flow (_Kw);
static void kwty_env (_Kw);
static void kwty_ast (_Kw);
static void kwty_loop (_Kw);

void kwty_obj_def (_Kw kw) {
	if (! ptree.curr.driver)
		ptree_add_driver_manifest (kw._.id);
	else
		NO_INFO_ERR (0x08, "");
}

void kwty_builtin_obj (_Kw kw) {
}

void kwty_builtin_ty (_Kw kw) {
	if (ptree.curr.driver) {
		/// TODO: check to prevent type override
		ptree_add_driver_bits (kw._.id);
	}
	else
		NO_LINEINFO_ERR (0x07, "\n");
}

void kwty_qual (_Kw kw) {}
void kwty_flow (_Kw kw) {}
void kwty_env (_Kw kw) {}
void kwty_ast (_Kw kw) {}
void kwty_loop (_Kw kw) {}

const _akw_handler akw_handler[] = {
	[KWTY_BUILTIN_OBJ] = &kwty_builtin_obj,
	[KWTY_BUILTIN_TY] = &kwty_builtin_ty,
	[KWTY_OBJ_DEF] = &kwty_obj_def,
	[KWTY_QUAL] = &kwty_qual,
	[KWTY_FLOW] = &kwty_flow,
	[KWTY_LOOP] = &kwty_loop,
	[KWTY_ENV] = &kwty_env,
	[KWTY_AST] = &kwty_ast,
};
