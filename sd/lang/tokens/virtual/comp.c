/**
 * @file comp.c
 *
 * @brief virtual compound token definition
 *
 * This file contains virtual compound
 * token definition
 */

#include <sd/lang/tokens/virtual/gen/id.h>
#include <sd/lang/tokens/virtual/comp.h>
#include <sd/lang/tokens/groups.h>

/// @brief virtual compound token identification interface
#define compound(x,y,z,w) { .with = x, .common = { .id = y, .vty = z, .ty = w } }

/// @brief virtual compound token manifest, direct compound, identified by text
static const vtid_comp_txt_dir txt_dir[] = {
	[norm_comp_txt_dir (_CHILD)] = compound ('/', _MATH_DIV, COMPOUND_INDIR|SUFFIX_CHLD, TTY_MATH_OP),
	[norm_comp_txt_dir (_BIT_AND)] = compound ('&', _BOOL_AND, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BOOL_CMP),
	[norm_comp_txt_dir (_BIT_OR)] = compound ('|', _BOOL_OR, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BOOL_CMP),
	[norm_comp_txt_dir (_PIPE)] = compound ('%', _MATH_MOD, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BOOL_OP),
	[norm_comp_txt_dir (_CAST)] = compound ('.', _OBJ_PARENT, AS_IS|SUFFIX_CHLD, TTY_OBJ_REF),
	[norm_comp_txt_dir (_SELF)] = compound ('^', _BIT_XOR, AS_IS|SUFFIX_CHLD, TTY_BITWISE_OP),
	[norm_comp_txt_dir (_LIT)] = compound ('$', _MACRO_LIT, AS_IS|SUFFIX_NOC1, TTY_SYN),
	[norm_comp_txt_dir (_BOOL_LT)] = compound ('<', _BIT_LS, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BITWISE_OP),
	[norm_comp_txt_dir (_BOOL_GT)] = compound ('>', _BIT_RS, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BITWISE_OP),
	[norm_comp_txt_dir (_MATH_PLUS)] = compound ('+', _MATH_INC, AS_IS|SUFFIX_NOC1, TTY_MATH_OP),
	[norm_comp_txt_dir (_MATH_MINUS)] = compound ('-', _MATH_DEC, AS_IS|SUFFIX_NOC1, TTY_MATH_OP),
	[norm_comp_txt_dir (_IF)] = compound ('?', _IN_IF, AS_IS|SUFFIX_CHLD, TTY_COND),
	[norm_comp_txt_dir (_ASSIGN)] = compound (':', _IN_ASSIGN, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
};

// TODO: make a group that deals with bool_cmp a bit more specifically
/// @brief virtual compound token manifest, indirect compound, identified by text
static const vtid_comp_txt_indir txt_indir[] = {
	[norm_comp_txt_indir (_BOOL_LT)] = compound ('=', _BOOL_LTEQ, AS_IS|SUFFIX_CHLD, TTY_BOOL_CMP),
	[norm_comp_txt_indir (_BOOL_GT)] = compound ('=', _BOOL_GTEQ, AS_IS|SUFFIX_CHLD, TTY_BOOL_CMP),
	[norm_comp_txt_indir (_BOOL_NEG)] = compound ('=', _BOOL_NEQ, AS_IS|SUFFIX_CHLD, TTY_BOOL_CMP),
	[norm_comp_txt_indir (_MATH_PLUS)] = compound (':', _ASSIGN_PLUS, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_txt_indir (_MATH_MINUS)] = compound (':', _ASSIGN_MINUS, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_txt_indir (_MATH_TIMES)] = compound (':', _ASSIGN_TIMES, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_txt_indir (_BIT_OR)] = compound (':', _ASSIGN_OR, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_txt_indir (_BIT_AND)] = compound (':', _ASSIGN_AND, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
};

/// @brief virtual compound token manifest, direct compound, identified by compound
static const vtid_comp_comp comp[] = {
	[norm_comp_comp (_MATH_MOD)] = compound (':', _ASSIGN_MOD, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_comp (_MATH_DIV)] = compound (':', _ASSIGN_DIV, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_comp (_BOOL_AND)] = compound (':', _ASSIGN_AND, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_comp (_BOOL_OR)] = compound (':', _ASSIGN_OR, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	//[norm_comp_cond (_BOOL_XOR)] = compound (':', _ASSIGN_XOR, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF), //TODO
	[norm_comp_comp (_BIT_XOR)] = compound (':', _ASSIGN_BWXOR, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_comp (_BIT_RS)] = compound (':', _ASSIGN_BWRS, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
	[norm_comp_comp (_BIT_LS)] = compound (':', _ASSIGN_BWLS, AS_IS|SUFFIX_CHLD, TTY_OBJ_DEF),
};

/// @brief virtual compound token text bundle
static const vtid_comp_txt txt = {
	.direct = (vtid_comp_txt_dir*)txt_dir,
	.indirect = (vtid_comp_txt_indir*)txt_indir,
};

/// @brief virtual compound token manifest
const vtid_comp vtoken_manifest_comp = {
	.txt = &txt,
	.mask = (vtid_comp_mask*)0,
	.comp = (vtid_comp_comp*)comp,
};
