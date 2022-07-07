/**
 * @file ot.h
 *
 * @brief object table external interface
 *
 * This file contains definitions
 * for object creation and basic
 * tree manipulation
 */

#ifndef LOCK_OBJ_TREE
#  define LOCK_OBJ_TREE

#  include <sd/lang/tokens/groups.h>

#  include "utils/types/shared.h"

struct data {
	void* data;
	addr addr;
};

struct obj {
	struct data data;
	struct obj* pr;
	struct obj* cd;
	addr addr;
};

typedef struct obj Obj;

extern Obj g_root;
extern addr g_self;

void mkchild (Obj*, Obj*);
void rmchild (Obj*, uint);

#endif
