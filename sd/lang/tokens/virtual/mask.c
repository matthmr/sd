/**
 * @file mask.c
 *
 * @brief virtual masked token definition
 *
 * This file contains virtual masked
 * token interfaces
 */

#include <sd/lang/tokens/interface/vti.h>
#include <sd/lang/tokens/virtual/mask.h>
#include <sd/lang/tokens/groups.h>

/// @brief virtual mask token identification interface
#define mask(x,y,z) { .common = { .id = x, .vty = y, .ty = z } }

/// @brief virtual mask token manifest, identified by text
static const vtid_mask_txt txt[] = {
	[norm_mask_txt (_BOOL_LT)] = mask (_ARR_BEGIN, AS_IS, TTY_OBJ_REF_DEL),
	[norm_mask_txt (_BOOL_GT)] = mask (_ARR_END, AS_IS, TTY_OBJ_REF_DEL),
	[norm_mask_txt (_MATH_PLUS)] = mask (_MATH_UPLUS, AS_IS|SUFFIX_NOC2, TTY_MATH_OP),
	[norm_mask_txt (_MATH_MINUS)] = mask (_MATH_UMINUS, AS_IS|SUFFIX_NOC2, TTY_MATH_OP),
	[norm_mask_txt (_BOOL_NEG)] = mask (_IN_WHILE, AS_IS|SUFFIX_NOC1|SUFFIX_CHLD, TTY_COND),
};

/// @brief virtual mask token manifest
const vtid_mask mask = {
	.txt = txt,
	.mask = (vtid_mask_txt*)0,
	.comp = (vtid_mask_comp*)0,
};
