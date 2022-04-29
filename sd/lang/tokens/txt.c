/**
 * This file contains all the arrays
 * for all keywords and tokens of
 * the standard SD language
 */
#include <sd/lang/tokens/gen/txtmaps.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>

#define kw(a,b,c) { .kw = a, .id = b, .ty = c }
#define t(a,b,c,d) { .t = a, .id = b, .vty = c, .ty = d }

const _Kw keyword_manifest[] = {

	/**
	 * The keywords are sorted by:
	 *
	 *   1. alphabetic - repetition - size
	 *      aabc
	 *      aa
	 *      bbcd
	 *      bb
	 *
	 *   2. alphabetic - plain - size
	 *      abcd
	 *      bcde
	 *      cdef
	 */

	// -- ASSIGNMENT -- //
	/* built-in data types */
	[KW_BOOL] = kw ("bool", _BOOL, KWTY_BUILTIN_TY),
	[KW_CHAR] = kw ("char", _CHAR, KWTY_BUILTIN_TY),
	[KW_SHORT] = kw ("short", _SHORT, KWTY_BUILTIN_TY),
	[KW_INT] = kw ("int", _INT, KWTY_BUILTIN_TY),
	[KW_FLOAT] = kw ("float", _FLOAT, KWTY_BUILTIN_TY),
	[KW_LONG] = kw ("long", _LONG, KWTY_BUILTIN_TY),

	/* qualifiers */
	[KW_CONST] = kw ("const", _CONST, KWTY_QUAL),
	[KW_STATIC] = kw ("static", _STATIC, KWTY_QUAL),
	[KW_UNSIGNED] = kw ("unsigned", _UNSIGNED, KWTY_QUAL),
	[KW_SIGNED] = kw ("signed", _SIGNED, KWTY_QUAL),

	/* modifiers */
	[KW_ENUM] = kw ("enum", _ENUM, KWTY_MOD),

	/* object definition */
	[KW_RM] = kw ("rm", _RM, KWTY_OBJ_DEF),
	[KW_TYPE] = kw ("type", _TYPE, KWTY_OBJ_DEF),
	[KW_TAG] = kw ("tag", _TAG, KWTY_OBJ_DEF),

	/* scope control */
	[KW_IMPORT] = kw ("import", _IMPORT, KWTY_ENV),
	[KW_IMPL] = kw ("impl", _IMPL, KWTY_ENV),
	[KW_SCOPE] = kw ("scope", _SCOPE, KWTY_ENV),
	[KW_HERE] = kw ("here", _HERE, KWTY_ENV),

	// -- INTRINSIC -- //
	/* built-in objects */
	[KW_NIL] = kw ("nil", _NIL, KWTY_BUILTIN_OBJ),
	[KW_THIS] = kw ("this", _THIS, KWTY_BUILTIN_OBJ),
	[KW_TRUE] = kw ("true", _TRUE, KWTY_BUILTIN_OBJ),
	[KW_FALSE] = kw ("false", _FALSE, KWTY_BUILTIN_OBJ),

	// -- FLOW -- //
	/* flow control */
	[KW_ASYNC] = kw ("async", _ASYNC, KWTY_FLOW),
	[KW_SYNC] = kw ("sync", _SYNC, KWTY_FLOW),
	[KW_END] = kw ("end", _END, KWTY_FLOW),
	[KW_JUMP] = kw ("jump", _JUMP, KWTY_FLOW),
	[KW_RET] = kw ("ret", _RET, KWTY_FLOW),
	[KW_GOTO] = kw ("goto", _GOTO, KWTY_FLOW),

	// -- MISC -- //
	/* accumulatives */
	[KW_AS] = kw ("as", _AS, KWTY_ACC),

	/* loops */
	[KW_ITER] = kw ("iter", _ITER, KWTY_LOOP),

};

const _T token_manifest[] = {

	/**
	 * The tokens that have `COMPOUND` or `MASK` (or both)
	 * do NOT have to specify what level of suffix their
	 * virual counterpart has OR what that counterpart is:
	 * their `_T.id` gets it for them.
	 */

	/* reference delimiters */
	[T_OBJ_BEGIN] = t ('[', _OBJ_BEGIN, MATCH_OPEN, TTY_OBJ_REF_DEL),
	[T_OBJ_END] = t (']', _OBJ_END, MATCH_CLOSE, TTY_OBJ_REF_DEL),
	[T_MOD_BEGIN] = t ('<', _MOD_BEGIN, MATCH_OPEN|COMPOUND|MASK, TTY_OBJ_REF_DEL),
	[T_MOD_END] = t ('>', _MOD_END, MATCH_CLOSE|COMPOUND|MASK, TTY_OBJ_REF_DEL),
	[T_PROC_BEGIN] = t ('(', _PROC_BEGIN, MATCH_OPEN, TTY_OBJ_REF_DEL),
	[T_PROC_END] = t (')', _PROC_END, MATCH_CLOSE, TTY_OBJ_REF_DEL),
	[T_SEP] = t (',', _SEP, AS_IS, TTY_OBJ_REF_DEL),

	/* object reference */
	[T_CHILD] = t ('/', _CHILD, COMPOUND, TTY_OBJ_REF),
	[T_DEREF] = t ('@', _DEREF, AS_IS, TTY_OBJ_REF),
	[T_CAST] = t ('.', _CAST, COMPOUND, TTY_OBJ_REF),

	/* object definition */
	[T_BODY_BEGIN] = t ('{', _BODY_BEGIN, MATCH_OPEN, TTY_OBJ_DEF),
	[T_BODY_END] = t ('}', _BODY_END, MATCH_CLOSE, TTY_OBJ_DEF),
	[T_ASSIGN] = t (':', _ASSIGN, AS_IS, TTY_OBJ_DEF),

	/* expression control */
	[T_EXPR_END] = t (';', _EXPR_END, AS_IS, TTY_EXPR),
	[T_SELF] = t ('^', _SELF, COMPOUND, TTY_EXPR),

	/* misc syntax */
	[T_STRING] = t ('"', _STRING, MATCH_OPEN|MATCH_CLOSE, TTY_SYN),
	[T_COMMENT] = t ('#', _COMMENT, AS_IS, TTY_SYN),
	[T_LABEL] = t ('$', _LABEL, COMPOUND, TTY_SYN),

	/* math operation */
	[T_MATH_PLUS] = t ('+', _MATH_PLUS, MASK|COMPOUND, TTY_MATH_OP),
	[T_MATH_TIMES] = t ('*', _MATH_TIMES, AS_IS, TTY_MATH_OP),
	[T_MATH_MINUS] = t ('-', _MATH_MINUS, MASK|COMPOUND, TTY_MATH_OP),

	/* bool comparison */
	[T_BOOL_EQ] = t ('=', _BOOL_EQ, AS_IS, TTY_BOOL_CMP),

	/* bool operation */
	[T_BOOL_NEG] = t ('!', _BOOL_NEG, MASK|COMPOUND, TTY_BOOL_OP),

	/* bitwise operation */
	[T_BIT_NEG] = t ('~', _BIT_NEG, AS_IS, TTY_BITWISE_OP),
	[T_BIT_AND] = t ('&', _BIT_AND, COMPOUND, TTY_BITWISE_OP),
	[T_BIT_OR] = t ('|', _BIT_OR, COMPOUND, TTY_BITWISE_OP),

	/* piping */
	[T_PIPE] = t ('%', _PIPE, COMPOUND, TTY_PIPE),

	/* conditional branching */
	[T_IF] = t ('?', _IF, COMPOUND, TTY_COND),

};

const uint keyword_manifest_len = BYTES (keyword_manifest);
const uint token_manifest_len = BYTES (token_manifest);
