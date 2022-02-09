/**
 * This files contains utils
 * for making the parse tree
 */

#ifndef LOCK_PARSE_TREE
#  define LOCK_PARSE_TREE

#  include <sd/utils/types/shared.h>
#  include <sd/lang/tree/ot.h>

struct assign {
	void* lhs;
	void* rhs;
};

struct bin_op {
	void* lhs;
	void* rhs;
};

/* this wraps arround other parsing schema */
union tree {
	struct bin_op;
	struct assign;
};

typedef union tree Tree;
extern Tree parse_tree;

void swaprhs (void);

#endif
