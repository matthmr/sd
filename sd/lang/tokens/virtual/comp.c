/**
 * @file comp.c
 *
 * @brief virtual compound token definition
 *
 * This file contains virtual compound
 * token definition
 */

#include <sd/lang/tokens/interface/vti.h>
#include <sd/lang/tokens/virtual/comp.h>
#include <sd/lang/tokens/groups.h>

#define comp(x,y,z,w) { .with = x, .common = { .id = y, .vty = z, .ty = w } }

///< @brief virtual compound token identification interface

/// @brief virtual compound direct token definition
const vtid_comp_txt txt[] = {

	// -- direct -- //
	[_CHILD] = comp ('/', _MATH_DIV, AS_IS, TTY_MATH_OP),
	[_BIT_AND] = comp ('&', _BOOL_AND, AS_IS, TTY_BOOL_CMP),
	[_BIT_OR] = comp ('|', _BOOL_OR, AS_IS, TTY_BOOL_CMP),
	[_PIPE] = comp ('%', _MATH_MOD, AS_IS, TTY_BOOL_OP),
	[_CAST] = comp ('.', _OBJ_PARENT, AS_IS, TTY_OBJ_REF),
	[_SELF] = comp ('^', _BIT_XOR, AS_IS, TTY_BITWISE_OP),
	[_LIT] = comp ('$', _MACRO_LIT, AS_IS, TTY_SYN),
	[_ARR_BEGIN] = comp ('<', _BIT_LS, AS_IS, TTY_BITWISE_OP),
	[_ARR_END] = comp ('>', _BIT_RS, AS_IS, TTY_BITWISE_OP),
	[_MATH_PLUS] = comp ('+', _MATH_INC, AS_IS, TTY_MATH_OP),
	[_MATH_MINUS] = comp ('-', _MATH_DEC, AS_IS, TTY_MATH_OP),
	[_IF] = comp ('?', _WHILE, AS_IS, TTY_COND),

	// -- indirect -- //

};

const _vti [] = {
	[_MATH_LTEQ] = { .against = _BOOL_EQ, .make = _MATH_LTEQ },
	[_MATH_GTEQ] = 0,
	[_MATH_NEQ] = vtid_append (0x0017),

	[_ASSIGN_PLUS] = vtid_append (0x0018),
	[_ASSIGN_MINUS] = vtid_append (0x0019),
	[_ASSIGN_DIV] = vtid_append (0x001a),
	[_ASSIGN_TIMES] = vtid_append (0x001b),
	[_ASSIGN_MOD] = vtid_append (0x001c),
	[_ASSIGN_AND] = vtid_append (0x001d),
	[_ASSIGN_OR] = vtid_append (0x001e),
	[_ASSIGN_NOT] = vtid_append (0x001f),
	[_ASSIGN_BWAND] = vtid_append (0x0020),
	[_ASSIGN_BWOR] = vtid_append (0x0021),
	[_ASSIGN_BWXOR] = vtid_append (0x0022),
	[_ASSIGN_BWNOT] = vtid_append (0x0023),
	[_ASSIGN_BWRS] = vtid_append (0x0024),
	[_ASSIGN_BWLS] = vtid_append (0x0025),
	[_ASSIGN_LTEQ] = vtid_append (0x0026),
	[_ASSIGN_GTEQ] = vtid_append (0x0027),
	[_ASSIGN_NEQ] = vtid_append (0x0028),
	[_ASSIGN_EQ] = vtid_append (0x0029),
};

const _vti vtoken_manifest_comp = {
	.txt = vtoken_manifest_comp_direct,
	.mask = vtoken_manifest_comp_indirect,
	.comp = vtoken_manifest_comp_indirect,
};
