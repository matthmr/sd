/**
 * This file contains all objects made
 * in parsing; type agnostic.
 */

#ifndef LOCK_LANG_UTILS
#  define LOCK_LANG_UTILS

#  include <sd/utils/types/shared.h>

// -- `Obj.ref` types -- //
#  define DATA 0
#  define OBJ 1

typedef char ref_t;
typedef unsigned long int oid;

struct obj {
	/* metadata */
	uint cdno;
	ref_t rty;
	oid oid;

	/* data */
	void* ref;
	struct obj* pr;
	struct obj* cd;
};

typedef struct obj Obj;

#endif
