/**
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>

bool lock_stream = false;

struct stream_ctxt gs_ctxt = {
	.cmt = 0,
	.str = 0,
	.literal = 0,
	.expect_compound = 0,
	.expect_match = 0,
	.__PAD = 0,

	.base = 10,
};
