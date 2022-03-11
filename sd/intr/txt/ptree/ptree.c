/**
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#include <sd/lang/expr/drivers/drivers.h>
#include <sd/lang/tokens/utils/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

#include <sd/intr/txt/ptree/ptree.h>

Heap ptree_buffer[BUFFER];

static Heap branch[3];
static int offset[3] = {
	[PARENT] = 0,
	[CHILD1] = 1, // left
	[CHILD2] = 2, // right
};

static Heap* get_branch (int*);
static void set_branch (void); // orphan

static void append_child (Heap); // child <- parent
static void append_op (Op); // child <- parent
static void prepend_op (Op); // parent -> child

Heap* get_branch (int* offset) { }

void set_branch (void) {

	Heap* cbranch = (Heap*) ptree.buffer;

	// branch = get_branch (offset);

	ptree.curr.branch = branch;

	ptree.branch.low = branch;
	ptree.branch.high1 = branch;

}

void append_child (Heap child) { }
void append_op (Op op) { }
void prepend_op (Op op) { }

// -- EXPORTS -- //

void ptree_cdriver_append (int driver) { }
void ptree_cdriver_set (int driver) { }

// TODO: add the literal under a driver so that
//       we can reuse it for uwords as well
void ptree_add_literal (d_addr literal) {

	if (!ptree.curr.branch)
		set_branch ();

	if (ptree.curr.children == 1) // E0x0b taken care of by the hook
		;//append_child ();

}

void ptree_add_op (uint op) {

	// add as orphan
	if (!ptree.curr.op)
		set_branch ();

	// add as parent
	if (ptree.curr.op &&
	    *ptree.curr.op < op)
		prepend_op (op);

	// add as child
	else
		append_op (op);

}

void ptree_add_float (float literal) { }

void ptree_exec (void) { }

void ptree_del_open (void) { }
void ptree_del_close (void) { }

struct parse_tree ptree = {
	.buffer = ptree_buffer,

	.curr = {
		.children = 0,
		.bracket = 0,
		.driver = NULL,
		.branch = NULL,
		.op = NULL,
	},

	.branch = {
		.low = NULL,
		.high1 = NULL,
		.high2 = NULL,
	},
};
