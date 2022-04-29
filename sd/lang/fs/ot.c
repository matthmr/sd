/**
 * This file contains definitions
 * for object creation and basic
 * tree manipulation
 */

#include <sd/utils/types/shared.h>
#include <sd/utils/types/cast.h>

#include <sd/lang/fs/ot.h>
#include <sd/lang/lang.h>

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
