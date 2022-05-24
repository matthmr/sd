/**
 * @file atom.h
 *
 * @brief SDVM atoms
 *
 * This file contains glibc atoms
 * for the SDVM
 */

#ifndef LOCK_ATOM
#  define LOCK_ATOM

#  include <sd/utils/types/shared.h>

typedef union op {
	uint math_op;
	uint bool_op;
	uint bit_op;
	uint unary_op;
} Op;

#  ifndef LOCK_ATOM_FN
#    define LOCK_ATOM_FN

typedef void (*_atom_math[5]) (void);
typedef void (*_atom_bit[6]) (void);
typedef void (*_atom_bool[6]) (void);

typedef struct atom {
	_atom_math math;
	_atom_bit bit;
	_atom_bool bool;
} Atom;

extern Atom atom;

#  endif

#endif
