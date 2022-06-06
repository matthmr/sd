/**
 * @file vmcb.h
 *
 * @brief callbacks for the SDVM
 *
 * This file contains callback
 * info for `main` scope
 */

#ifndef LOCK_VMCALLBACK
#  define LOCK_VMCALLBACK

enum src_vmcb {
	SRC_END = -2,
	SRC_INIT, // placeholder

	// -- stack scope -- //
	SRC_PUSH, // header

	SRC_PUSHB,
	SRC_PUSHW,
	SRC_PUSHL,
	SRC_PUSHQ,

	SRC_POPB,
	SRC_POPW,
	SRC_POPL,
	SRC_POPQ,

	SRC_POP, // footer
};

/*enum bc_vmcb {
	BC_END,
};*/

#  define src(x) (x != SRC_END)
#  define scope_is_stack(x) (x >= SRC_PUSH || x <= SRC_POP)
#  define stack_callback(x) \

typedef enum src_vmcb src_vmcb;
typedef enum bc_vmcb bc_vmcb;

extern src_vmcb src_callback;
//extern bc_vmcb bc_callback;

#endif
