/**
 * @file comp.c
 *
 * @brief virtual compound token definition
 *
 * This file contains virtual compound
 * token definition
 */

#include <sd/lang/tokens/virtual/comp.h>
#include <sd/lang/tokens/virtual/vt.h>
#include <sd/lang/core/obj.h>

#include <sd/utils/utils.h>

/// @brief virtual compound direct token definition
const vtid_comp_direct vtoken_manifest_comp_direct[] = {
	// compound only
	[T_BIT_AND] = _BOOL_AND,
	[T_BIT_OR] = _BOOL_OR,
	[T_PIPE] = _MATH_MOD,
	[T_CHILD] = _MATH_DIV,
	[T_CAST] = _OBJ_PARENT,
	[T_SELF] = _BIT_XOR,
	[T_LABEL] = _MACRO_LIT,

	// compound and mask
	[T_ARR_BEGIN] = _BIT_LS,
	[T_ARR_END] = _BIT_RS,
	[T_MATH_PLUS] = _MATH_INC,
	[T_MATH_MINUS] = _MATH_DEC,
	[T_BOOL_NEG] = _WHILE_TRUE,
};

const vtid_comp_indirect vtoken_manifest_comp_indirect[] = {
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

const unsigned short compdlen = BYTES (vtoken_manifest_comp_direct);
const unsigned short compidlen = BYTES (vtoken_manifest_comp_indirect);

vitd_comp vtoken_manifest_comp = {
	.direct = vtoken_manifest_comp_direct,
	.indirect = vtoken_manifest_comp_indirect,
};
