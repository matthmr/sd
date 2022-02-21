/**
 * This files contains definitions
 * for `u_obj` creation and basic
 * tree manipulation
 */

#ifndef LOCK_OBJ_TREE
#  define LOCK_OBJ_TREE

#  include <sd/lang/lang.h>

struct data {
	enum pt ty;
	enum ptq qual;
	void* data;
};

struct obj {
	struct data data;
	struct obj* pr;
	struct obj* cd;
};

typedef struct obj Obj;

extern Obj g_root;
extern Obj g_self;

void pushobj (Obj);

void mkchild (Obj*, Obj*);
void rmchild (Obj*, uint);

#endif
