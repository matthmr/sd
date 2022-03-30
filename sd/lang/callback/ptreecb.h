/**
 * This file contains callback
 * info for `parse_src` level
 * callback
 *
 *   == `parse_src` is in ==
 *   <sd/intr/txt/sdparse.c>
 */

#ifndef LOCK_PTREECALLBACK
#  define LOCK_PTREECALLBACK

enum ptree_cb {
	PTREE_END,

	PTREE_PUSH, // header

	PTREE_PUSHB,
	PTREE_PUSHW,
	PTREE_PUSHL,
	PTREE_PUSHQ,

	PTREE_POPB,
	PTREE_POPW,
	PTREE_POPL,
	PTREE_POPQ,

	PTREE_POP, // header
};

#  define ptree_stack(x) ()

typedef enum ptree_cb ptree_cb;

extern ptree_cb ptree_callback;

#endif
