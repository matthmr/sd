/**
 * This file contains virtual
 * tokens: tokens that can be
 * infered or constructed
 */

#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/tokens/virtual/vt.h>
#include <sd/lang/ast/astelem.h>
#include <sd/lang/core/obj.h>

#define vt(a,b) {.mask = a, .compound = b}
#define mask(a) vt (a, 0)
#define compound(a) vt (0, a)

const _vT vtoken_manifest[] = {

	[T_MOD_BEGIN] = vt (_BOOL_LT, _BIT_LS),
	[T_MOD_END] = vt (_BOOL_GT, _BIT_RS),
	[T_MATH_PLUS] = vt (_MATH_UPLUS, _MATH_INC),
	[T_MATH_MINUS] = vt (_MATH_UMINUS, _MATH_DEC),
	[T_BOOL_NEG] = vt (_WHILE, _WHILE_TRUE),

	[T_BIT_AND] = compound (_BOOL_AND),
	[T_BIT_OR] = compound (_BOOL_OR),
	[T_PIPE] = compound (_MATH_MOD),
	[T_CHILD] = compound (_MATH_DIV),
	[T_CAST] = compound (_OBJ_PARENT),
	[T_SELF] = compound (_BIT_XOR),
	[T_LABEL] = compound (_MACRO_LIT),
	[T_IF] = compound (_IF_TRUE),

};
