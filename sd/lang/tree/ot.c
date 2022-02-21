/**
 * This files contains definitions
 * for `u_obj` creation and basic
 * tree manipulation
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/tree/ot.h>
#include <sd/lang/lang.h>

Obj g_root = {
	.data = {
		.data = NULL,
		.ty = 0,
		.qual = 0,
	},
	.pr = NULL,
	.cd = NULL
};

Obj g_self = {
	.data = {
		.data = NULL,
		.ty = 0,
		.qual = 0,
	},
	.pr = NULL,
	.cd = NULL
};

void push_obj (Obj self) { }

void mkchild (Obj* root, Obj* children) {  }
void rmchild (Obj* root, uint c_id) {  }
