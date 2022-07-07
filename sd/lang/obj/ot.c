/**
 * @file ot.c
 *
 * @brief object table external interface
 *
 * This file contains definitions
 * for object creation and basic
 * tree manipulation
 */

#include <sd/lang/tokens/groups.h>
#include <sd/lang/obj/ot.h>

Obj g_root = {
	.data = {
		.data = NULL,
		.addr = 0,
	},
	.pr = NULL,
	.cd = NULL
};

addr g_self = CAST_addr &g_root;

void mkchild (Obj* root, Obj* children) {  }
void rmchild (Obj* root, uint c_id) {  }
