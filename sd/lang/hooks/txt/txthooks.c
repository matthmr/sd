/**
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#include <sd/lang/tokens/utils/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>

bool lock_stream = false;

struct stream_ctxt gs_ctxt = {
	.cmt = 0,
	.str = 0,

	.literal = 0,
	.expect_double = 0,
	.__PAD = 0,

	.base = 10,
};

inline struct mem_ctxt new_mem_ctxt (void) {
	struct mem_ctxt new_mem_ctxt = {
		.assign = 0,
		.assign_arg = 0,
		.assign_proto = 0,
		.__PAD = 0,
	};
	return new_mem_ctxt;
}


inline struct data_type new_data_ctxt (void) {
	struct data_type new_data_ctxt = {
		._sign = 1,
		._int = 0,
		._float = 0,
		._char = 0,
		._long = 0,
		._short = 0,
		._array = 0,
		.__PAD = 0,
	};
	return new_data_ctxt;
}
