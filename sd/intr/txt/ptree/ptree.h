/**
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#ifndef LOCK_PARSE_TREE
#  define LOCK_PARSE_TREE

#  define PARENT 0
#  define CHILD1 1
#  define CHILD2 2

#  include <sd/lang/expr/drivers/drivers.h>
#  include <sd/lang/expr/expr.h>

#  include <sd/utils/types/shared.h>

#  include <sd/intr/limits.h>

extern d_addr prec_mask;

struct child_offset {
	int _1;
	int _2;
};

union offset {
	int parent;
	struct child_offset child;
};

union tag_item {
	Driver driver;
	Op op;
};

enum enum_item {
	DRIVER,
	EMPTY,
	OP,
};

struct item {
	union tag_item get;
	enum enum_item type;
};

typedef struct item Item;
typedef union offset Offset;

struct heap {
	Item item;
	Offset offset;
};

typedef struct heap Heap;

struct curr {
	bool children;
	uint bracket;
	uint index;
	Op op;

	Heap** branch;
	Driver* driver;
};

struct branch {
	Heap* low;
	Heap* high1;
	Heap* high2;
};

struct parse_tree {
	Heap* buffer;

	struct curr curr;
	struct branch branch;
};

extern struct parse_tree ptree;
extern Heap ptree_buffer[];

void ptree_cdriver_append (int);
void ptree_cdriver_set (int);

void ptree_add_literal (d_addr);
void ptree_add_float (float);
void ptree_add_op (uint);
// void ptree_add_uword (Hash);

void ptree_exec (void);

void ptree_del_open (void);
void ptree_del_close (void);

/// resoluted by `ptree_add_op`; reset by `ptree_exec`
void ptree_bracket_close (void);
void ptree_bracket_open (void);

#endif
