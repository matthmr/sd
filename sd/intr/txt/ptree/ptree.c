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

#include <sd/intr/txt/ptree/op/precedence.h>
#include <sd/intr/txt/ptree/ptree.h>

#define populate if (!ptree.curr.branch) set_branch()

Heap ptree_buffer[BUFFER];
d_addr prec_mask = (d_addr) 0xf;

static Heap* branch[3];
static bool res_open;

static void set_branch (void);
static void append_branch (void);
static void prepend_branch (void);

static void set_op (Op);
static void append_op (Op);
static void prepend_op (Op);

void set_branch (void) {

	union tag_item tag;

	Driver gen_driver = {
		.manifest = DRIVER_NULL,
		.attr_bits = bits_32i,
		.attr_qual = qual_def,
	};

	tag.driver = gen_driver;

	Item item = {
		.get = tag,
		.type = EMPTY,
	};

	Heap* buffer = (Heap*) ptree.buffer;

	buffer[PARENT].item = item;
	buffer[CHILD1].item = item;
	buffer[CHILD2].item = item;

	buffer[PARENT].offset.child._1 = 1;
	buffer[PARENT].offset.child._2 = 2;
	buffer[CHILD1].offset.parent = -1;
	buffer[CHILD2].offset.parent = -2;

	branch[0] = &ptree.buffer[0];
	branch[1] = &ptree.buffer[1];
	branch[2] = &ptree.buffer[2];

	ptree.curr.branch = branch;

	ptree.branch.low = *branch;
	ptree.branch.high1 = *branch;

	ptree.curr.index += 3;

}

// TODO: define a static variable which knows
//       which high* to get from
void append_branch (void) {

	// readjust branch position
	branch[PARENT] = branch[CHILD2];
	branch[CHILD1] = branch[CHILD2]+1;
	branch[CHILD2] = branch[CHILD2]+2;

	// readjust offsets
	branch[CHILD1]->offset.parent = -1;
	branch[CHILD2]->offset.parent = -2;

	// assign new high
	if (branch[PARENT] > ptree.branch.high1)
		ptree.branch.high2 = *branch;
	else
		ptree.branch.high1 = *branch;
}

void prepend_branch (void) {

	// readjust branch position
	branch[PARENT] = branch[CHILD2]+1;
	branch[CHILD2] = branch[CHILD2]+2;

	// readjust offsets
	branch[CHILD1]->offset.parent = -1;
	branch[CHILD2]->offset.parent = -2;

	// assign new low
	ptree.branch.low = *branch;

}

void set_op (Op op) {
	ptree.curr.branch[PARENT]->item.type = OP;
	ptree.curr.branch[PARENT]->item.get.op = op;

	ptree.curr.op = ptree.curr.branch[PARENT]->item.get.op;
}

void append_op (Op op) {
	Heap child2 = *branch[CHILD2];

	// append type
	branch[CHILD2]->item.type = OP;
	branch[CHILD2]->item.get.op = op;
	append_branch ();

	// append child
	*branch[CHILD1] = child2;
	branch[CHILD1]->offset.parent = -2;

	ptree.curr.op = branch[PARENT]->item.get.op;
	ptree.curr.children = 1;
	ptree.curr.index += 2;
}

void prepend_op (Op op) {
	Heap* parent = branch[PARENT];

	// prepend type
	prepend_branch ();
	branch[PARENT]->item.type = OP;
	branch[PARENT]->item.get.op = op;

	// prepend child
	branch[CHILD1] = parent;
	branch[CHILD1]->offset.parent = 2;

	ptree.curr.op = branch[PARENT]->item.get.op;
	ptree.curr.children = 1;
	ptree.curr.index += 2;
}

// -- EXPORTS -- //

void ptree_cdriver_append (int driver) { }
void ptree_cdriver_set (int driver) { }

// TODO: add the literal under a driver so that
//       we can reuse it for uwords as well
void ptree_add_literal (d_addr literal) {

	populate;

	// E0x0b taken care of by the hooks
	if (ptree.curr.children == 0) {
		ptree.curr.branch[CHILD1]->item.get.op = literal; // debug
		ptree.curr.children = 1;
	}
	else if (ptree.curr.children == 1) {
		ptree.curr.branch[CHILD2]->item.get.op = literal; // debug
		ptree.curr.children = 0;
	}

}

void ptree_add_op (uint op) {

	populate;

	// add as orphan
	if (ptree.curr.op == OP_NULL)
		set_op (op);

	// add as parent
	else if (prec (ptree.curr.op) < prec (op) || res_open) {

		if (res_open) {
			H_RESET (res_open);
			ptree.curr.bracket--;
		};

		prepend_op (op);
	}

	else if (ass (ptree.curr.op) == LR)
		prepend_op (op);

	// add as child
	else
		append_op (op);

}

void ptree_add_float (float literal) { }

void ptree_exec (void) {

	struct curr clean_curr = {
		.children = 0,
		.bracket = 0,
		.index = 0,

		.driver = NULL,
		.branch = NULL,
	};

	struct branch clean_branch = {
		.low = NULL,
		.high1 = NULL,
		.high2 = NULL,
	};

	ptree.curr = clean_curr;
	ptree.branch = clean_branch;

}

void ptree_del_open (void) { }
void ptree_del_close (void) { }

void ptree_bracket_close (void) {
	H_LOCK (res_open);
}

void ptree_bracket_open (void) {
	ptree.curr.bracket++;
}

struct parse_tree ptree = {
	.buffer = ptree_buffer,

	.curr = {
		// -- flags -- //
		.children = 0,
		.bracket = 0,
		.index = 0,
		.op = OP_NULL,

		// -- pointers -- //
		.driver = NULL,
		.branch = NULL,
	},

	.branch = {
		.low = NULL,
		.high1 = NULL,
		.high2 = NULL,
	},
};
