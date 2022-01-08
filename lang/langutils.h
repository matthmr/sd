/**
 * This file contains all objects made
 * in parsing; type agnostic.
 */

#ifndef LOCK_PARSE_TYPE
#  define LOCK_PARSE_TYPE

#  include "tokens.h"

struct promise {
	bool _comment_start;
	bool _comment_end;
};

struct lock {
	bool _comment;
};

struct expression {
	int null;
};

struct object {
	int null;
};

typedef struct expression Expression;
typedef struct object Object;

struct tree {
	Object node;
	struct tree* child;
	struct tree* parent;
};

typedef struct tree Tree;

void MakeChild(Tree, Object, int);

static Tree root;
static struct promise Promise;
static struct lock Lock;

Object Eval(Expression);
#endif
