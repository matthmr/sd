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

// -- `direction` values
#  define LEFT 0
#  define RIGHT 1

extern unsigned char direction;

extern d_addr prec_mask;

// for `union offset`
struct child_offset {
	short _1;
	short _2;
};

// for `union offset`
struct prec_offset {
	short next;
	short prev;
};

// for `struct heap`
union offset {
	short parent;
	struct prec_offset prec;
	struct child_offset child;
};

// for `struct item`
union tag_item {
	Driver driver;
	Op op;
};

// for `struct item`
enum enum_item {
	DRIVER,
	EMPTY,
	OP,
};

// for `struct heap`
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

// for `struct parse_tree`
struct curr {
	bool children;
	uint bracket;
	uint index;
	Op op;

	Heap** branch;
	Driver* driver;
};

// for `struct parse_tree`
struct branch {
	Heap* low;
	Heap* high;
};

struct parse_tree {
	Heap* buffer;

	struct curr curr;
	struct branch branch;
};

extern struct parse_tree ptree;
extern Heap* ptree_buffer;

// -- drivers -- //
void ptree_cdriver_append (int);
void ptree_cdriver_set (int);

// -- hookings -- //
void ptree_add_literal (d_addr);
void ptree_add_float (float);
void ptree_add_op (uint);
void ptree_add_uop (uint);
// void ptree_add_uword (Hash);

// -- delimiters/brackets -- //
void ptree_del_open (void);
void ptree_del_close (void);

/// resoluted by `ptree_add_op`; reset by `ptree_exec`
void ptree_bracket_close (void);
void ptree_bracket_open (void);

// -- resolution -- //
void ptree_exec (void);

#endif
