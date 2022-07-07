/**
 * @file ptree.h
 *
 * @brief parse tree implementation
 *
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#ifndef LOCK_PARSE_TREE
#  define LOCK_PARSE_TREE

// -- `branch` values -- //
#  define PARENT 0
#  define CHILD1 1
#  define CHILD2 2
#  define AVAILABLE_CHILD ptree.curr.children+1
#  define CURRENT_CHILD ptree.curr.children

#  include <sd/lang/expr/drivers/drivers.h>
#  include <sd/lang/expr/expr.h>

#  include "utils/types/shared.h"

#  include <sd/intr/limits.h>

// -- `direction` values; they map to `branch`'s children -- //
#  define LEFT CHILD1
#  define RIGHT CHILD2
#  define dir bool

#  define UNARY LEFT

// `struct offset`
struct child_offset {
	short _1;
	short _2;
};

// `struct node`
struct offset {
	short parent;
	struct child_offset child;
};

// `struct item`; node.item's content
union tag_item {
	Driver driver;
	Op op;
};

// `struct item`; node.item's tag
enum enum_item {
	TY_OP = -2,
	TY_DRIVER,
	TY_EMPTY=0, // empty item indicates the parent is an unary operator
};

// `struct node`
struct item {
	union tag_item _;
	enum enum_item type;
};

typedef struct item Item;
typedef struct offset Offset;

struct node {
	Item item;
	Offset offset;
};

typedef struct node Node;

// `struct parse_tree`
struct curr {

	// flags
	u8 children;
	uint bracket;
	Op op;

	// pointers
	Node** branch;
	Driver** driver;

};

// `struct parse_tree`
struct branch {
	Node* low;
	Node* high;
};

// `struct parse_tree`
struct expect {
	Driver driver;
	bool _;
};

struct parse_tree {
	Node* buffer; // shorthand
	Node* bk_stack; // shorthand

	uint buffer_size; // metadata @ptree.buffer

	struct expect expect; // metadata @ptree.buffer.item._.driver
	struct curr curr; // metadata @ptree
	struct branch branch; // metadata @ptree.buffer
};

extern struct parse_tree ptree;
extern Node* ptree_buffer;
extern Node* bk_stack;

// -- drivers -- //
void ptree_add_driver_bits (int);
void ptree_add_driver_qual (int);
void ptree_add_driver_manifest (int);

// -- hooks -- //
void ptree_add_literal (d_addr);
void ptree_add_float (float);
void ptree_add_double (double);
void ptree_add_op (Op);
void ptree_add_uop (Op); // u: unary
// void ptree_add_uword (Hash); // u: user

//   -- delimiters/brackets -- //
void ptree_del_open (void);
void ptree_del_close (void);

void ptree_bracket_close (void);
void ptree_bracket_open (void);

//   -- resolution; error checked in the callee's scope -- //
void ptree_exec (void);

// -- init -- //
void pt_init (void);

#endif
