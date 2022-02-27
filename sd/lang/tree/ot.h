/**
 * This file contains definitions
 * for object creation and basic
 * tree manipulation
 */

#ifndef LOCK_OBJ_TREE
#  define LOCK_OBJ_TREE

#  include <sd/utils/types/shared.h>
#  include <sd/lang/lang.h>

struct data {
	enum pt ty;
	enum ptq qual;
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
