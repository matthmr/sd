/**
 * This file contains all objects made
 * in parsing; type agnostic.
 */

#ifndef LOCK_LANG_UTILS
#  define LOCK_LANG_UTILS

#  include <sd/utils/types/shared.h>
#  include <sd/intr/limits.h>

struct obj {
	Name childrenno;
	void* data;
	struct obj* parent;
	struct obj* children;
};

typedef struct obj Obj;

Obj mkchild (Obj*, void*);

#endif
