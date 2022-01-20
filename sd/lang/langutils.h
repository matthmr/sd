/**
 * This file contains all objects made
 * in parsing; type agnostic.
 */

#ifndef LOCK_LANG_UTILS
#  define LOCK_LANG_UTILS

#  include <sd/utils/types/shared.h>

union reference {
	void* data; /// pass by value
	void* obj;  /// pass by pointer
};

typedef union reference ref;

struct obj {
	uint cdno;
	ref ref;
	struct obj* pr;
	struct obj* cd;
};

typedef struct obj Obj;

Obj* mkchild (Obj*, Obj*);

#endif
