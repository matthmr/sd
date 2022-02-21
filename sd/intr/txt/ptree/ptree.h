/**
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#ifndef LOCK_PARSE_TREE
#  define LOCK_PARSE_TREE

#  include <sd/utils/types/shared.h>
#  include <sd/lang/expr/expr.h>

extern u16 promote;

struct call {
	addr caller;
	addr callee;
	u64 callee_n;
};

struct assign {
	addr u_obj;
	void* s_obj;
};

struct ptree {
	struct nest {
		void (*start) (void);
		void (*end) (void);
	} nest;
	void (*data) (void*);
	void (*op) (op);
};

extern struct ptree ptree;

#endif
