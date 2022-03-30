/**
 * This file contains callback
 * info for `main` level callback
 */

#ifndef LOCK_VMCALLBACK
#  define LOCK_VMCALLBACK

enum src_vmcb {
	SRC_END,

	SRC_PUSH, // header

	SRC_PUSHB,
	SRC_PUSHW,
	SRC_PUSHL,
	SRC_PUSHQ,

	SRC_POPB,
	SRC_POPW,
	SRC_POPL,
	SRC_POPQ,

	SRC_POP, // header
};

enum bc_vmcb {
	BC_END,
};

#  define src_stack(x) (x >= SRC_PUSH || x <= SRC_POP)
#  define stack_callback(x) \

typedef enum src_vmcb src_vmcb;
typedef enum bc_vmcb bc_vmcb;

extern src_vmcb src_callback;
extern bc_vmcb bc_callback;

#endif
