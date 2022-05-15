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
#include <sd/utils/err/verr.c>
#include <sd/utils/utils.h>

#if ADDR_BITS == 64
double getd_num (char* s, uint dot_offset) { return 0.F; }
#endif

float get_fnum (char* s, uint dot_offset) { return 0.f; }

d_addr get_num_with_base (char* s, uint rel, u8 base) {

	d_addr exp = 1;
	d_addr ret = 0;

	int lim = (base == 10)? 0: // ...    : decimal
	          (base == 8)? 1:  // 0...   : octal
	          2;               // 0x...  : hex

	// octal and decimal
	if (base != 16) for (int i = rel-1; i >= lim; i--) {
		ret += (s[i]-ASCII_NUM_OFFSET)*exp;
		exp *= base;
	}

	// hex
	else for (int i = rel-1; i >= lim; i--) {
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

void aint_hook (char* s, uint rel) {

	uint dot_offset;
	char* dot;

	d_addr ret;

	float retf;
	double retd;

	if ((dot = strchr (s, '.')) != NULL) {
		dot_offset = (uint) (dot - s);
		retf = get_fnum (s, dot_offset);
		gs_ctxt.base = 10;
		// TODO: the entire float/double shebang
		// ptree_add_float (retf);
		// ptree_add_double (retd);
	}
	else {
		ret = get_num_with_base (s, rel, gs_ctxt.base);
		gs_ctxt.base = 10;

		if (ptree.curr.children >= 1 && ptree.curr.op == OP_NULL) // as in: 1 1
			ERR (0x0b);
		else
			ptree_add_literal (ret);
	}

}

void astring_hook (char* s) {
	// TODO: copy the string to heap
}
