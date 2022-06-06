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
#include <sd/lang/core/statement.h>
#include <sd/lang/tokens/groups.h>

#include <sd/intr/txt/tokens/form.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/utils.h>

#define kw(a,b,c) { .kw = a, .id = b, .ty = c } ///< @brief keyword plain-text interface
#define t(a,b,c,d) { .t = a, .id = b, .vty = c, .ty = d } ///< @brief token plain-text interface

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
	[KW_LET] = kw ("let", _LET, KWTY_OBJ_DEF),
	[KW_PROC] = kw ("proc", _PROC, KWTY_OBJ_DEF),

	/* scope control */
	[KW_IMPORT] = kw ("import", _IMPORT, KWTY_ENV),
	[KW_IMPL] = kw ("impl", _IMPL, KWTY_ENV),
	[KW_SCOPE] = kw ("scope", _SCOPE, KWTY_ENV),
	[KW_HERE] = kw ("here", _HERE, KWTY_ENV),
	[KW_UNWRAP] = kw ("unwrap", _UNWRAP, KWTY_ENV),

	// -- INTRINSIC -- //
	/* built-in objects */
	[KW_NIL] = kw ("nil", _NIL, KWTY_BUILTIN_OBJ),
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
	[KW_BRANCH] = kw ("branch", _BRANCH, KWTY_FLOW),
	[KW_PEEK] = kw ("peek", _PEEK, KWTY_FLOW),
	[KW_LABEL] = kw ("label", _LABEL, KWTY_FLOW),

	// -- MISC -- //
	/* AST probe */
	[KW_AS] = kw ("as", _AS, KWTY_AST),
	[KW_RES] = kw ("res", _RES, KWTY_AST),

	/* loops */
	[KW_ITER] = kw ("iter", _ITER, KWTY_LOOP),

};

/// @brief plain-text token manifest
/// @note the `SUFFIX` bit field only applies to
///       their immidiate (plain-text) forms,
///       virtual forms **may** have different
///       types of suffixing
const _T token_manifest[] = {

	/* reference delimiters */
	[T_OBJ_BEGIN] = t ('[', _OBJ_BEGIN, MATCH, TTY_OBJ_REF_DEL),
	[T_OBJ_END] = t (']', _OBJ_END, MATCH, TTY_OBJ_REF_DEL),
	[T_PROC_BEGIN] = t ('(', _PROC_BEGIN, MATCH, TTY_OBJ_REF_DEL),
	[T_PROC_END] = t (')', _PROC_END, MATCH, TTY_OBJ_REF_DEL),
	[T_SEP] = t (',', _SEP, AS_IS|SUFFIX_NOC2|SUFFIX_CHLD|SUFFIX_NOC1, TTY_OBJ_REF_DEL),

	/* object reference */
	[T_CHILD] = t ('/', _CHILD, COMPOUND_DIR|SUFFIX_NOC1|SUFFIX_CHLD, TTY_OBJ_REF),
	[T_DEREF] = t ('@', _DEREF, AS_IS|SUFFIX_NOC1, TTY_OBJ_REF),
	[T_CAST] = t ('.', _CAST, COMPOUND_DIR|SUFFIX_CHLD, TTY_OBJ_REF),

	/* object definition */
	[T_BODY_BEGIN] = t ('{', _BODY_BEGIN, MATCH, TTY_OBJ_DEF),
	[T_BODY_END] = t ('}', _BODY_END, MATCH, TTY_OBJ_DEF),
	[T_ASSIGN] = t (':', _ASSIGN, COMPOUND_DIR|SUFFIX_CHLD, TTY_OBJ_DEF),

	/* expression control */
	[T_EXPR_END] = t (';', _EXPR_END, AS_IS|SUFFIX_NOC2, TTY_EXPR),
	[T_SELF] = t ('^', _SELF, COMPOUND_DIR, TTY_EXPR),

	/* misc syntax */
	[T_CHAR] = t ('\'', _SCHAR, MATCH, TTY_SYN),
	[T_STRING] = t ('"', _DCHAR, MATCH, TTY_SYN),
	[T_COMMENT] = t ('#', _COMMENT, AS_IS, TTY_SYN),
	[T_LIT] = t ('$', _LIT, COMPOUND_DIR|SUFFIX_NOC1, TTY_SYN),

	/* math operation */
	[T_MATH_PLUS] = t ('+', _MATH_PLUS, MASK|COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_CHLD, TTY_MATH_OP),
	[T_MATH_TIMES] = t ('*', _MATH_TIMES, COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_CHLD, TTY_MATH_OP),
	[T_MATH_MINUS] = t ('-', _MATH_MINUS, MASK|COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_CHLD, TTY_MATH_OP),

	/* bool comparison */
	[T_BOOL_EQ] = t ('=', _BOOL_EQ, COMPOUND_INDIR|SUFFIX_CHLD, TTY_BOOL_CMP),
	[T_BOOL_LT] = t ('<', _BOOL_LT, MATCH|COMPOUND_DIR|COMPOUND_INDIR|MASK|SUFFIX_CHLD, TTY_BOOL_CMP),
	[T_BOOL_GT] = t ('>', _BOOL_GT, MATCH|COMPOUND_DIR|COMPOUND_INDIR|MASK|SUFFIX_CHLD, TTY_BOOL_CMP),

	/* bool operation */
	[T_BOOL_NEG] = t ('!', _BOOL_NEG, MASK|COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_NOC1, TTY_BOOL_OP),

	/* bitwise operation */
	[T_BIT_NEG] = t ('~', _BIT_NEG, AS_IS|SUFFIX_NOC1, TTY_BITWISE_OP),
	[T_BIT_AND] = t ('&', _BIT_AND, COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_CHLD, TTY_BITWISE_OP),
	[T_BIT_OR] = t ('|', _BIT_OR, COMPOUND_DIR|COMPOUND_INDIR|SUFFIX_CHLD, TTY_BITWISE_OP),

	/* piping */
	[T_PIPE] = t ('%', _PIPE, COMPOUND_DIR|SUFFIX_CHLD, TTY_PIPE),

	/* conditional branching */
	[T_IF] = t ('?', _IF, COMPOUND_DIR|MASK|SUFFIX_NOC2, TTY_COND),

};

const uint keyword_manifest_len = BYTES (keyword_manifest);
const uint token_manifest_len = BYTES (token_manifest);
