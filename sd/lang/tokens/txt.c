/**
 * @file txt.c
 *
 * @brief plain text manifests
 *
 * This file contains sorted manifests
 * for keywords and tokens of the
 * standard written SD language
 */

#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/tokens/virtual/vt.h>
#include <sd/lang/tokens/groups.h>
#include <sd/lang/tokens/txtid.h>

#include <sd/intr/txt/tokens/form.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

/// @brief keyword manifest interface macro
#define __keyword__(_kw, _kwid, _cid, _cty) \
[_kwid] = { \
	.this = _kw, \
	._ = __kcommon__ (_cid, _cty), \
}

/// @brief token manifest interface macro
#define __token__(_t, _tid, _cid, _cty, _cprec, _cass, _cvt, _csfix, _vop, _vt) \
[_tid] = { \
	.token = { \
		.this = _t, \
		._ = __common__ (_cid, _cty, _cprec, _cass, _cvt, _csfix), \
	}, \
	.vt = _vop _vt, \
}

/// @brief keyword manifest
///
/// The keywords are sorted by:
/// @verbatim
///   1. alphabetic - repetition - size
///      aabc
///      aa
///      bbcd
///      bb
///
///   2. alphabetic - plain - size
///      abcd
///      bcde
///      cdef
/// @endverbatim
const _Kw keyword_manifest[] = {

	// TODO: redesign this
	// -- ASSIGNMENT -- //
	/* built-in data types */
	__keyword__ ("bool", KW_BOOL, _BOOL, KWTY_BUILTIN_TY),

	// TODO: redesign this?
	/* qualifiers */
	__keyword__ ("const", KW_CONST, _CONST, KWTY_QUAL),
	__keyword__ ("static", KW_STATIC, _STATIC, KWTY_QUAL),
	__keyword__ ("unsigned", KW_UNSIGNED, _UNSIGNED, KWTY_QUAL),
	__keyword__ ("signed", KW_SIGNED, _SIGNED, KWTY_QUAL),

	/* modifiers */
	__keyword__ ("enum", KW_ENUM, _ENUM, KWTY_MOD),

	/* object definition */
	__keyword__ ("rm", KW_RM, _RM, KWTY_OBJ_DEF),
	__keyword__ ("type", KW_TYPE, _TYPE, KWTY_OBJ_DEF),
	__keyword__ ("tag", KW_TAG, _TAG, KWTY_OBJ_DEF),
	__keyword__ ("let", KW_LET, _LET, KWTY_OBJ_DEF),
	__keyword__ ("proc", KW_PROC, _PROC, KWTY_OBJ_DEF),

	/* scope control */
	__keyword__ ("import", KW_IMPORT, _IMPORT, KWTY_ENV),
	__keyword__ ("impl", KW_IMPL, _IMPL, KWTY_ENV),
	__keyword__ ("scope", KW_SCOPE, _SCOPE, KWTY_ENV),
	__keyword__ ("here", KW_HERE, _HERE, KWTY_ENV),
	__keyword__ ("unwrap", KW_UNWRAP, _UNWRAP, KWTY_ENV),
	__keyword__ ("wrap", KW_WRAP, _WRAP, KWTY_ENV),

	// -- INTRINSIC -- //
	/* built-in objects */
	__keyword__ ("nil", KW_NIL, _NIL, KWTY_BUILTIN_OBJ),
	__keyword__ ("true", KW_TRUE, _TRUE, KWTY_BUILTIN_OBJ),
	__keyword__ ("false", KW_FALSE, _FALSE, KWTY_BUILTIN_OBJ),
	__keyword__ ("this", KW_THIS, _THIS, KWTY_BUILTIN_TY),

	// -- FLOW -- //
	/* flow control */
	__keyword__ ("async", KW_ASYNC, _ASYNC, KWTY_FLOW),
	__keyword__ ("sync", KW_SYNC, _SYNC, KWTY_FLOW),
	__keyword__ ("end", KW_END, _END, KWTY_FLOW),
	__keyword__ ("jump", KW_JUMP, _JUMP, KWTY_FLOW),
	__keyword__ ("ret", KW_RET, _RET, KWTY_FLOW),
	__keyword__ ("goto", KW_GOTO, _GOTO, KWTY_FLOW),
	__keyword__ ("branch", KW_BRANCH, _BRANCH, KWTY_FLOW),
	__keyword__ ("peek", KW_PEEK, _PEEK, KWTY_FLOW),
	__keyword__ ("label", KW_LABEL, _LABEL, KWTY_FLOW),

	// -- MISC -- //
	/* AST probe */
	__keyword__ ("as", KW_AS, _AS, KWTY_AST),
	__keyword__ ("res", KW_RES, _RES, KWTY_AST),

	/* loops */
	__keyword__ ("iter", KW_ITER, _ITER, KWTY_LOOP),

};

/// @brief plain-text token manifest
/// @note the `SUFFIX` bit field only applies to
///       their immidiate (plain-text) forms,
///       virtual forms **may** have different
///       types of suffixing
const _T token_manifest[] = {

	/* reference delimiters */
	__token__ ('[', T_OBJ_BEGIN,
		_OBJ_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
		VIRT, __match__ (V_MMATCHER,
			_OBJ_END, TTY_OBJ_REF_DEL, PREC_INF, ASS_IRR, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	__token__ (']', T_OBJ_END,
		_OBJ_END, TTY_OBJ_REF_DEL, PREC_INF, ASS_IRR, MATCH, SUFFIX_CLOSE,
		VIRT, __match__ (V_MMATCHEE,
			_OBJ_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_OPEN,
			DONE, 0)
	),

	__token__ ('(', T_PROC_BEGIN,
		_PROC_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
		VIRT, __match__ (V_MMATCHER,
			_PROC_END, TTY_OBJ_REF_DEL, 1u, LEFTRIGHT, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	__token__ (')', T_PROC_END,
		_PROC_END, TTY_OBJ_REF_DEL, 1u, LEFTRIGHT, MATCH, SUFFIX_CLOSE,
		VIRT, __match__ (V_MMATCHEE,
			_PROC_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_OPEN,
			DONE, 0)
	),

	__token__ (',', T_SEP,
		_SEP, TTY_OBJ_REF_DEL, AS_IS, 16u, LEFTRIGHT, SUFFIX_CHLD|SUFFIX_NOC1|SUFFIX_NOC2,
		NOVIRT, NONEST
	),

	/* object reference */
	__token__ ('/', T_CHILD,
		_CHILD, TTY_OBJ_REF, 1u, LEFTRIGHT, COMPOUND, SUFFIX_NOC1|SUFFIX_CHLD,
		VIRT, __comp__ (_CHILD,
			_MATH_DIV, TTY_MATH_OP, 4u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
			NEST, __comp__ (_ASSIGN,
				_ASSIGN_DIV, TTY_OBJ_DEF, 14u, RIGHTLEFT, AS_IS, SUFFIX_CHLD,
				DONE, 0)
			)
	),

	__token__ ('@', T_REF,
		_REF, TTY_OBJ_REF, 2u, RIGHTLEFT, AS_IS, SUFFIX_NOC1,
		NOVIRT, NONEST
	),

	__token__ ('.', T_CAST,
		_CAST, TTY_OBJ_REF, 13u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		VIRT, __comp__ (_CAST,
			_OBJ_PARENT, TTY_OBJ_REF, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CHLD,
			DONE, 0)
	),

	/* object definition */
	__token__ ('{', T_BODY_BEGIN,
		_BODY_BEGIN, TTY_OBJ_DEF, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
		VIRT, __match__ (V_MMATCHER,
			_BODY_END, TTY_OBJ_DEF, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	__token__ ('}', T_BODY_END,
		_BODY_END, TTY_OBJ_DEF, PREC_IRR, ASS_IRR, MATCH, SUFFIX_CLOSE,
		VIRT, __match__ (V_MMATCHEE,
			_BODY_BEGIN, TTY_OBJ_DEF, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_OPEN,
			DONE, 0)
	),

	__token__ (':', T_ASSIGN,
		_ASSIGN, TTY_OBJ_DEF, 14u, RIGHTLEFT, COMPOUND, SUFFIX_CHLD,
		VIRT, __comp__ (_ASSIGN,
			_IN_ASSIGN, TTY_OBJ_DEF, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	/* expression control */
	__token__ (';', T_EXPR_END,
		_EXPR_END, TTY_EXPR, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_IRR,
		NOVIRT, NONEST
	),

	__token__ ('^', T_SELF,
		_SELF, TTY_EXPR, PREC_IRR, ASS_IRR, COMPOUND, SUFFIX_IRR,
		VIRT, __comp__ (_SELF,
			_BIT_XOR, TTY_BITWISE_OP, 9u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
			NEST, __comp__ (_ASSIGN,
				_ASSIGN_BWXOR, TTY_OBJ_REF_DEL, 14u, RIGHTLEFT, AS_IS, SUFFIX_CHLD,
				DONE, 0
			)
		)
	),

	/* misc syntax */
	__token__ ('\'', T_CHAR,
		_SCHAR, TTY_SYN, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
		VIRT, __match__ (V_MSELF,
			_SCHAR, TTY_SYN, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	__token__ ('"', T_STRING,
		_DCHAR, TTY_SYN, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
		VIRT, __match__ (V_MSELF,
			_DCHAR, TTY_SYN, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CLOSE,
			DONE, 0)
	),

	__token__ ('#', T_COMMENT,
		_COMMENT, TTY_SYN, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_IRR,
		NOVIRT, NONEST
	),

	__token__ ('$', T_LIT,
		_LIT, TTY_SYN, PREC_IRR, ASS_IRR, COMPOUND, SUFFIX_NOC1,
		NOVIRT, __comp__ (_LIT,
			_MACRO_LIT, TTY_SYN, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_NOC1,
			DONE, 0)
	),

	/* math operation */
	__token__ ('+', T_MATH_PLUS,
		_MATH_PLUS, TTY_MATH_OP, 4u, LEFTRIGHT, MASK|COMPOUND, SUFFIX_CHLD,
		, ALL (
			__mask__ (_MATH_UPLUS, TTY_MATH_OP, 2u, RIGHTLEFT, AS_IS, SUFFIX_NOC1,
				DONE, 0),
			__comp__ (_MATH_PLUS,
				// TODO: differentiate increments (this is postfix increment)
				_MATH_INC, TTY_MATH_OP, 1u, LEFTRIGHT, AS_IS, SUFFIX_NOC2,
				DONE, 0
			)
		)
	),

	__token__ ('*', T_MATH_TIMES,
		_MATH_TIMES, TTY_MATH_OP, 3u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		VIRT, __comp__ (_ASSIGN,
			_ASSIGN_TIMES, TTY_OBJ_DEF, 1u, RIGHTLEFT, AS_IS, SUFFIX_CHLD,
			DONE, 0)
	),

	__token__ ('-', T_MATH_MINUS,
		_MATH_MINUS, TTY_MATH_OP, 4u, LEFTRIGHT, MASK|COMPOUND, SUFFIX_CHLD,
		, ALL (
			__mask__ (_MATH_UMINUS, TTY_MATH_OP, 2u, RIGHTLEFT, AS_IS, SUFFIX_NOC1,
				DONE, 0),
			__comp__ (_MATH_MINUS,
				_MATH_DEC, TTY_MATH_OP, 1u, LEFTRIGHT, AS_IS, SUFFIX_NOC2,
				DONE, 0
			)
		)
	),

	/* bool comparison */
	__token__ ('=', T_BOOL_EQ,
		_BOOL_EQ, TTY_BOOL_CMP, 7u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
		NOVIRT, NONEST
	),

	__token__ ('<', T_BOOL_LT,
		_BOOL_LT, TTY_BOOL_CMP, 6u, LEFTRIGHT, COMPOUND|MASK, SUFFIX_CHLD,
		, ALL (
			__comp__ (_BOOL_LT,
				_BIT_LS, TTY_BITWISE_OP, 5u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
				NEST, __comp__ (_ASSIGN,
					_ASSIGN_BWLS, TTY_OBJ_DEF, 14u, RIGHTLEFT, AS_IS, SUFFIX_CHLD,
					DONE, 0)
			),
			__comp__ (_BOOL_EQ,
				_BOOL_LTEQ, TTY_BOOL_OP, 6u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0
			),
			__mask__ (_MOD_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
				NEST, __match__ (V_MMATCHER,
					_MOD_END, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_CLOSE,
					DONE, 0)
			),
			__mask__ (_ARR_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, MATCH, SUFFIX_OPEN,
				NEST, __match__ (V_MMATCHER,
					_ARR_END, TTY_OBJ_REF_DEL, 1u, LEFTRIGHT, AS_IS, SUFFIX_CLOSE,
					DONE, 0)
			),
		)
	),

	__token__ ('>', T_BOOL_GT,
		_BOOL_GT, TTY_BOOL_CMP, 6u, LEFTRIGHT, COMPOUND|MASK, SUFFIX_CHLD,
		, ALL (
			__comp__ (_BOOL_GT,
				_BIT_RS, TTY_BITWISE_OP, 5u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
				NEST, __comp__ (_ASSIGN,
					_ASSIGN_BWRS, TTY_OBJ_DEF, 14u, RIGHTLEFT, AS_IS, SUFFIX_CHLD,
					DONE, 0)
				),
			__comp__ (_BOOL_EQ,
				_BOOL_GTEQ, TTY_BOOL_OP, 6u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0
			),
			__mask__ (_MOD_END, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, MATCH, SUFFIX_CLOSE,
				NEST, __match__ (V_MMATCHEE,
					_MOD_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_OPEN,
					DONE, 0)
				),
			__mask__ (_ARR_END, TTY_OBJ_REF_DEL, 1u, LEFTRIGHT, MATCH, SUFFIX_CLOSE,
				NEST, __match__ (V_MMATCHEE,
					_ARR_BEGIN, TTY_OBJ_REF_DEL, PREC_IRR, ASS_IRR, AS_IS, SUFFIX_OPEN,
					DONE, 0)
				),
		)
	),

	/* bool operation */
	__token__ ('!', T_BOOL_NEG,
		_BOOL_NEG, TTY_BOOL_OP, 3u, RIGHTLEFT, COMPOUND|MASK, SUFFIX_NOC1,
		, ALL (
			__mask__ (_WHILE, TTY_COND, 15u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				NEST, __comp__ (_BOOL_NEG,
					_IN_WHILE, TTY_COND, 15u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
					DONE, 0)
				),
			__comp__ (_BOOL_EQ,
				_BOOL_NEQ, TTY_BOOL_OP, 7u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0),
		)
	),

	/* bitwise operation */
	__token__ ('~', T_BIT_NEG,
		_BIT_NEG, TTY_BITWISE_OP, 3u, RIGHTLEFT, AS_IS, SUFFIX_NOC1,
		NOVIRT, NONEST),

	__token__ ('&', T_BIT_AND,
		_BIT_AND, TTY_BITWISE_OP, 8u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		, ALL (
			__comp__ (_BIT_AND,
				_BOOL_AND, TTY_BOOL_OP, 11u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0),
			__comp__ (_ASSIGN,
				_ASSIGN_BWAND, TTY_OBJ_REF, 14u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0)
		)
	),

	__token__ ('|', T_BIT_OR,
		_BIT_OR, TTY_BITWISE_OP, 10u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		, ALL (
			__comp__ (_BIT_OR,
				_BOOL_OR, TTY_BOOL_OP, 12u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0),
			__comp__ (_ASSIGN,
				_ASSIGN_BWOR, TTY_OBJ_REF, 14u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0)
		)
	),

	/* piping */
	__token__ ('%', T_PIPE,
		_PIPE, TTY_PIPE, 1u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		VIRT, __comp__ (_PIPE,
			_MATH_MOD, TTY_MATH_OP, 4u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
			NEST, __comp__ (_ASSIGN,
				_ASSIGN_MOD, TTY_OBJ_DEF, 14u, LEFTRIGHT, AS_IS, SUFFIX_CHLD,
				DONE, 0)
			)
	),

	/* conditional branching */
	__token__ ('?', T_IF,
		_IF, TTY_COND, 15u, LEFTRIGHT, COMPOUND, SUFFIX_CHLD,
		VIRT, __comp__ (_IF,
			_IN_IF, 15u, LEFTRIGHT, TTY_COND, AS_IS, SUFFIX_CHLD, // TODO: this is not true
			DONE, 0)
	),
};

const uint keyword_manifest_len = BYTES (keyword_manifest);
const uint token_manifest_len = BYTES (token_manifest);
