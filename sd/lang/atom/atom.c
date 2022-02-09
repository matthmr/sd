/**
 * This file contains glibc atoms
 */

#include <sd/utils/types/shared.h>

#include <sd/lang/atom/atom.h>
#include <sd/lang/vm/vm.h>

static void atom_math_plus (void);
static void atom_math_div (void);
static void atom_math_times (void);
static void atom_math_minus (void);
static void atom_math_mod (void);

static void atom_bool_land (void);
static void atom_bool_lor (void);
static void atom_bool_lnot (void);
static void atom_bool_leq (void);
static void atom_bool_llt (void);
static void atom_bool_lgt (void);

static void atom_bit_bwand (void);
static void atom_bit_bwor (void);
static void atom_bit_bwnot (void);
static void atom_bit_bwxor (void);
static void atom_bit_bwrshift (void);
static void atom_bit_bwlshift (void);

void atom_math_plus (void) {
	float ret = pop() + pop();
	push (ret);
}

void atom_math_minus (void) {
	void* top;

	switch (sp.t) {
	case BT_INT:
		top = (int*) pop_t (sp.t);
		break;
	case BT_UINT:
		top = (uint*) pop_t (sp.t);
		break;
	case BT_FLOAT:
		top = (float*) pop_t (sp.t);
		break;
	}

	float ret = pop_t (sp.t) - top;
	push (ret);
}

void atom_math_div (void) {
	float top = pop();
	float ret = pop() / top;
	push (ret);
}

void atom_math_times (void) {
	int ret = pop() * pop();
	push (ret);
}

void atom_math_mod (void) {
	float top = pop();
	float ret = pop() % top;
	push (ret);
}

Atom atom;

atom.math = {
	[PLUS] = &atom_math_plus,
	[DIV] = &atom_math_div,
	[TIMES] = &atom_math_times,
	[MINUS] = &atom_math_minus,
	[MOD] = &atom_math_mod,
};

atom.bool = {
	[LAND] = &atom_bool_land,
	[LOR] = &atom_bool_lor,
	[LNOT] = &atom_bool_lnot,
	[LEQ] = &atom_bool_leq,
	[LLT] = &atom_bool_llt,
	[LGT] = &atom_bool_lgt,
};

atom.bit = {
	[BWAND] = &atom_bit_bwand,
	[BWOR] = &atom_bit_bwor,
	[BWNOT] = &atom_bit_bwnot,
	[BWXOR] = &atom_bit_bwxor,
	[BWRSHIFT] = &atom_bit_bwrshift,
	[BWLSHIFT] = &atom_bit_bwlshift,
};
