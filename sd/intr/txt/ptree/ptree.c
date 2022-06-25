/**
 * @file ptree.c
 *
 * @brief parse tree implementation
 *
 * This file defines parse
 * tree mapping for plain-
 * text SD source code
 */

#include <stdlib.h>

#include <sd/lang/expr/drivers/drivers.h>
#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/macros.h>

#include <sd/intr/txt/ptree/ptree.h>
#include <sd/intr/limits.h>

struct parse_tree ptree;

Node* ptree_buffer;
Node* bk_stack;

static Node* branch[3];
static Driver* driver[3];

static bool res_open;

// -- tree functionality -- //
static void set_branch (void);
static void append_branch (void);  // append.slave
static void prepend_branch (void); // prepend.slave
static void calc_branch (Node**);

// -- branch functionality -- //
static void set_op (Op);
static void append_op (Op);  // append.master
static void prepend_op (Op); // prepend.master
static void subs_op (Op, dir);

void set_branch (void) {

	/**
	 * the branch (& parse tree) are setup as
	 *
	 * @verbatim
	 *             [PARENT] {1, 2}
	 *      [CHILD1] {-1}  [CHILD2] {-2}
	 * @endverbatim
	 */

	// populate ptree.buffer
	ptree_buffer[PARENT].offset.child._1 = 1;
	ptree_buffer[PARENT].offset.child._2 = 2;

	ptree_buffer[CHILD1].offset.parent = -1;
	ptree_buffer[CHILD2].offset.parent = -2;

	// set up the local branch
	branch[PARENT] = &ptree.buffer[PARENT];
	branch[CHILD1] = &ptree.buffer[CHILD1];
	branch[CHILD2] = &ptree.buffer[CHILD2];

	// initialize local branch
	branch[PARENT]->item.type = TY_OP;
	branch[CHILD1]->item.type = TY_DRIVER;
	branch[CHILD2]->item.type = TY_DRIVER;

	// set up the drivers
	driver[CHILD1] = &branch[PARENT]->item._.driver;
	driver[CHILD2] = &branch[PARENT]->item._.driver;

	// initialize drivers
	driver[CHILD1]->attr_bits = bits_32;
	driver[CHILD2]->attr_bits = bits_32;
	driver[CHILD1]->attr_qual = (qual)0;
	driver[CHILD2]->attr_qual = (qual)0;

	// set up `ptree.curr`
	ptree.curr.branch = branch;
	ptree.curr.driver = driver;

	// set up `ptree.branch`
	ptree.branch.low = *branch;
	ptree.branch.high = *branch;

}

// append.slave
void append_branch (void) {

}

// prepend.slave
void prepend_branch (void) {

}

void set_op (Op op) {
	branch[PARENT]->item.type = TY_OP;
	branch[PARENT]->item._.op = op;

	ptree.curr.children++;
}

// append.master
void append_op (Op op) {
	branch[AVAILABLE_CHILD]->item.type = TY_OP;
	branch[AVAILABLE_CHILD]->item._.op = op;

	ptree.curr.children++;
}

// prepend.master
void prepend_op (Op op) {

}

void subs_op (Op op, dir d) {

}

// -- EXPORTS -- //
void ptree_add_driver_bits (int kw) { }
void ptree_add_driver_qual (int kw) { }
void ptree_add_driver_manifest (int kw) {

	LOCK (ptree.expect._);

	Driver driver = {
		.manifest = DRIVER_NULL,
		.drivee = { .as32 = 0 },
		.attr_bits = bits_32,
		.attr_qual = qual_here,
		.tag = AS_INLINE,
	};

	driver.manifest =  (kw);

	ptree.expect.driver = driver;
	**ptree.curr.driver = ptree.expect.driver;

}

void ptree_add_literal (d_addr literal) {

	Driver literal_driver = {
		.manifest = DRIVER_LITERAL,
		.drivee = 0,

		.attr_bits = bits_32,
		.attr_qual = qual_here,

		.tag = AS_INLINE,
	};

	// edge case: first branch
	if (ptree.branch.low == ptree.branch.high) {

		// edge case: first driver == no cast; assume 32 bits
		if (! ptree.curr.op)
			goto _ptree_add_literal_as32;

		else if (driver[CURRENT_CHILD]->attr_bits == bits_32)
			goto _ptree_add_literal_as32;
		else
			goto _ptree_add_literal_as64;

		_ptree_add_literal_as64: {
			literal_driver.drivee.as64 = literal;
			goto _ptree_add_literal_out;
		}
		_ptree_add_literal_as32: {
			literal_driver.drivee.as32 = (d_addrl) literal;
			goto _ptree_add_literal_out;
		}

		_ptree_add_literal_out:
			branch[AVAILABLE_CHILD]->item._.driver = literal_driver;

		ptree.curr.children++;

	}

	// normal case: can inherit from sibblings OR from cast

	ptree.curr.children++;

}

void ptree_add_op (Op op) {

	// edge case: first branch
	if (ptree.branch.low == ptree.branch.high) {
		set_op (op);
		return;
	}

	// normal case: check precedence; hook with whichever action is appropiate
	else if (prec (op) > prec (ptree.curr.op))
		prepend_op (op);
	else if (prec (op) < prec (ptree.curr.op))
		append_op (op);
	else if (ass (op) == LR) {

	}
	else {

	}

}

void ptree_add_uop (Op op) {

	// edge case: first branch
	if (ptree.branch.low == ptree.branch.high) {
		set_op (op);
		branch[UNARY]->item.type = TY_DRIVER;
		branch[UNARY]->item._.driver.manifest = DRIVER_UNARY;
		return;
	}
	else ;

}

void ptree_add_float (float literal) {

}

void ptree_del_open (void) {

}

void ptree_del_close (void) {

}

void ptree_bracket_close (void) {
	H_LOCK (res_open);
}

void ptree_bracket_open (void) {
	ptree.curr.bracket++;
}

void ptree_exec (void) {

}

void pt_init (void) {

	struct curr curr = {
		// -- flags -- //
		.children = 0,
		.bracket = 0,
		.op = OP_NULL,

		// -- pointers -- //
		.driver = driver,
		.branch = branch,
	};

	struct branch branch = {
		.low = NULL,
		.high = NULL,
	};

	Driver expect_driver = {
		.manifest = DRIVER_NULL,
		.drivee = { .as32 = 0 },

		.attr_bits = bits_32,
		.attr_qual = qual_here|qual_signed,

		.tag = AS_INLINE,
	};

	ptree.curr = curr;
	ptree.branch = branch;
	ptree.expect.driver = expect_driver;
	ptree.expect._ = false;

	// TODO: implement a bootstrapped version of `malloc`
	// for heap memory allocation
	ptree_buffer = ptree.buffer = malloc (
		ptree.buffer_size = (STDBUFFER / 2) / sizeof (Node)
	);

	bk_stack = ptree.bk_stack =
		&ptree.buffer [ptree.buffer_size-1];

	set_branch ();

}
