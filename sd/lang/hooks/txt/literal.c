/**
 * This file contains functionality
 * for literal integer-like
 * assignment/reference
 */

#include <string.h>

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

float get_fnum (char* s, uint dot_offset) {  }

u64 get_num_base (char* s, uint rel, u8 base) {

	u64 exp = 1;
	u64 ret = 0;

	int lim = (base == 10)? 0: (base == 8)? 1: 2;

	for (int i = rel-1; i >= lim; i--)
		ret += ((s[i]-ASCII_NUM_OFFSET)*(exp*=base));

	return ret;
}

void aint_hook (char* s, uint rel) {

	uint dot_offset;
	char* dot;

	u64 ret;
	float retf;

	if (dot = strchr (s, '.')) {
		dot_offset = (uint) (dot - s);
		retf = get_fnum (s, dot_offset);
		// TODO: add floating point expr
	}
	else {
		ret = get_num_base (s, rel, gs_ctxt.base);
		gs_ctxt.base = 10;
		// TODO: add the appropiate size expr
	}

}

void astring_hook (char* s) {

	// TODO: copy the string to heap

}
