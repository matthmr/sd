/**
 * This file contains glibc atoms
 */

#ifndef LOCK_ATOM
#  define LOCK_ATOM

#  include <sd/utils/types/shared.h>

enum math_op {
	PLUS,
	DIV,
	TIMES,
	MINUS,
	MOD,
};

enum bool_op {
	LAND,
	LOR,
	LNOT,
	LEQ,
	LLT,
	LGT,
};

enum bit_op {
	BWAND,
	BWOR,
	BWNOT,
	BWXOR,
	BWRSHIFT,
	BWLSHIFT,
};

typedef union op {
	enum math_op m_op;
	enum bool_op B_op;
	enum bit_op b_op;
} Op;

typedef void (*_atom_math,*_atom_bit,*_atom_bool) (void);

typedef struct atom {
	_atom_math math;
	_atom_bit bit;
	_atom_bool bool;
} Atom;

extern Atom atom;

#endif
