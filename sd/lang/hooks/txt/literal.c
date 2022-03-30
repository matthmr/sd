/**
 * This file contains functionality
 * for literal integer-like
 * assignment/reference
 */

#include <string.h>

#include <sd/intr/txt/ptree/ptree.h>

#include <sd/lang/expr/drivers/drivers.h>
#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/hooks/txt/literal.h>
#include <sd/lang/vm/vm.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

float get_fnum (char* s, uint dot_offset) {  }

d_addr get_num_with_base (char* s, uint rel, u8 base) {

	d_addr exp = 1;
	d_addr ret = 0;

	int lim = (base == 10)? 0: // ...
	          (base == 8)? 1: // 0...
	          2; // 0x...

	if (base != 16)
		for (int i = rel-1; i >= lim; i--) {
			ret += (s[i]-ASCII_NUM_OFFSET)*exp;
			exp *= base;
		}
	else
		for (int i = rel-1; i >= lim; i--) {

			if (NUMBER (s[i]))
				ret += (s[i]-ASCII_NUM_OFFSET)*exp;
			else if (NUMBER_LHEX (s[i]))
				ret += (s[i]-ASCII_LHEX_OFFSET)*exp;
			else
				ret += (s[i]-ASCII_UHEX_OFFSET)*exp;

			exp *= 16;
		}

	return ret;
}

ptree_cb aint_hook (char* s, uint rel) {

	uint dot_offset;
	char* dot;

	d_addr ret;
	float retf;

	if (dot = strchr (s, '.')) {
		dot_offset = (uint) (dot - s);
		retf = get_fnum (s, dot_offset);
		gs_ctxt.base = 10;
		// ptree_add_float (retf);
	}
	else {
		ret = get_num_with_base (s, rel, gs_ctxt.base);
		gs_ctxt.base = 10;

		if ((ptree.curr.children == 1 && !ptree.curr.op) ||
			  (ptree.curr.children >= 2 && !ptree.curr.op))
			;//ERR

		ptree_add_literal (ret);
	}

}

void astring_hook (char* s) {

	// TODO: copy the string to heap

}
