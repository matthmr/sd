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

d_addr prec_mask = (d_addr) 0xf;

struct offset {
	int child1;
	int child2;
	int parent;
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
typedef struct offset Offset;

struct heap {
	Item item;
	Offset offset;
};

typedef struct heap Heap;

struct curr {
	bool children;
	uint bracket;

	Heap* branch;
	Driver* driver;
	Op* op;
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

extern uint bracket;
extern struct parse_tree ptree;
extern Heap ptree_buffer[];

void ptree_cdriver_append (int);
void ptree_cdriver_set (int);

void ptree_add_literal (d_addr);
void ptree_add_float (float);
void ptree_add_op (uint);
// void ptree_add_uword (Hash);

void ptree_exec (void);

#  define ptree_prec_open  ptree.curr.bracket++
#  define ptree_prec_close ptree.curr.bracket--

void ptree_del_open (void);
void ptree_del_close (void);

#endif
