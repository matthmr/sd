/**
 * @file atom.c
 *
 * @brief SDVM atoms
 *
 * This file contains glibc atoms
 * for the SDVM
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
}

void atom_math_div (void) {
	long long top = pop();
	float ret = pop() / top;
	push (ret);
}

void atom_math_times (void) {
	u64 (*popr)(void) = g_expr.get_popr ();
	void (*pushr)(u64) = g_expr.get_pushr ();

	u64 ret = popr () * popr ();
	g_expr.get_pushr () (ret);
}

void atom_math_mod (void) {
	float top = pop();
	float ret = pop() % top;
	push (ret);
}

Atom atom;

atom.math = {
	[M32_PLUS] = &atom_math_plus,
	[M32_DIV] = &atom_math_div,
	[M32_TIMES] = &atom_math_times,
	[M32_MINUS] = &atom_math_minus,
	[M32_MOD] = &atom_math_mod,
};

atom.bool = {
	[L_AND] = &atom_bool_land,
	[L_OR] = &atom_bool_lor,
	[L_NOT] = &atom_bool_lnot,
	[L_EQ] = &atom_bool_leq,
	[L_LT] = &atom_bool_llt,
	[L_GT] = &atom_bool_lgt,
};

atom.bit = {
	[BW_AND] = &atom_bit_bwand,
	[BW_OR] = &atom_bit_bwor,
	[BW_NOT] = &atom_bit_bwnot,
	[BW_XOR] = &atom_bit_bwxor,
	[BW_RSHIFT] = &atom_bit_bwrshift,
	[BW_LSHIFT] = &atom_bit_bwlshift,
};
