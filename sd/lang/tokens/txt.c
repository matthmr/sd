/**
 * This file contains all the arrays
 * for all keywords and tokens of
 * the standard SD language sorted
 * by ranking following:
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
 *
 * They are sorted at compile-time and
 * a simple algorithm gets the type of
 * manifest.
 *
 * The actual sorting is done on the
 * index at <sd/lang/core/obj.h>.
 */

#include <sd/lang/tokens/utils/txtmaps.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#include <sd/utils/types/shared.h>

const _Kw const keyword_manifest[] = {

	/* built-in data types */
	[KW_INT] = { .kw = "int", .id = _INT, .ty = KWTY_BUILTIN_TY },
	[KW_CHAR] = { .kw = "char", .id = _CHAR, .ty = KWTY_BUILTIN_TY },
	[KW_FLOAT] = { .kw = "float", .id = _FLOAT, .ty = KWTY_BUILTIN_TY },
	[KW_ENUM] = { .kw = "enum", .id = _ENUM, .ty = KWTY_BUILTIN_TY },
	[KW_LIST] = { .kw = "list", .id = _LIST, .ty = KWTY_BUILTIN_TY },
	[KW_MAP] = { .kw = "map", .id = _MAP, .ty = KWTY_BUILTIN_TY },
	[KW_LONG] = { .kw = "long", .id = _LONG, .ty = KWTY_BUILTIN_TY },
	[KW_SHORT] = { .kw = "short", .id = _SHORT, .ty = KWTY_BUILTIN_TY },

	/* qualifiers */
	[KW_CONST] = { .kw = "const", .id = _CONST, .ty = KWTY_QUAL },
	[KW_STATIC] = { .kw = "static", .id = _STATIC, .ty = KWTY_QUAL },
	[KW_UNSIGNED] = { .kw = "unsigned", .id = _UNSIGNED, .ty = KWTY_QUAL },
	[KW_SCOPE] = { .kw = "scope", .id = _SCOPE, .ty = KWTY_QUAL },
	[KW_NEW] = { .kw = "new", .id = _NEW, .ty = KWTY_QUAL },
	[KW_LOCAL] = { .kw = "local", .id = _LOCAL, .ty = KWTY_QUAL },

	/* built-in objects */
	[KW_NIL] = { .kw = "nil", .id = _NIL, .ty = KWTY_BUILTIN_OBJ },
	[KW_THIS] = { .kw = "this", .id = _THIS, .ty = KWTY_BUILTIN_OBJ },

	/* object definition */
	[KW_LET] = { .kw = "let", .id = _LET, .ty = KWTY_OBJ_DEF },
	[KW_PROC] = { .kw = "proc", .id = _PROC, .ty = KWTY_OBJ_DEF },
	[KW_RM] = { .kw = "rm", .id = _RM, .ty = KWTY_OBJ_DEF },

	/* flow control */
	[KW_EXPR] = { .kw = "expr", .id = _EXPR, .ty = KWTY_FLOW },
	[KW_BRANCH] = { .kw = "branch", .id = _BRANCH, .ty = KWTY_FLOW },
	[KW_ASYNC] = { .kw = "async", .id = _ASYNC, .ty = KWTY_FLOW },
	[KW_SYNC] = { .kw = "sync", .id = _SYNC, .ty = KWTY_FLOW },
	[KW_END] = { .kw = "end", .id = _END, .ty = KWTY_FLOW },
	[KW_JUMP] = { .kw = "jump", .id = _JUMP, .ty = KWTY_FLOW },
	[KW_RET] = { .kw = "ret", .id = _RET, .ty = KWTY_FLOW },

	/* environment control */
	[KW_IMPORT] = { .kw = "import", .id = _IMPORT, .ty = KWTY_ENV },
	[KW_WRAP] = { .kw = "wrap", .id = _WRAP, .ty = KWTY_ENV },

	/* accumulatives */
	[KW_MUL] = { .kw = "mul", .id = _MUL, .ty = KWTY_ACC },

	/* loops */
	[KW_ITER] = { .kw = "iter", .id = _ITER, .ty = KWTY_LOOP },

};

const _T const token_manifest[] = {

	/* reference delimiters */
	[T_OBJ_REF_BEGIN] = { .t = '[', .ty = TTY_OBJ_REF_DEL},
	[T_OBJ_REF_END] = { .t = ']', .ty = TTY_OBJ_REF_DEL},
	[T_MOD_REF_BEGIN] = { .t = '<', .ty = TTY_OBJ_REF_DEL}, /* doubles bool comparison and right shift */
	[T_MOD_REF_END] = { .t = '>', .ty = TTY_OBJ_REF_DEL},  /* doubles bool comparison and right shift */
	[T_OBJ_PROC_APPLY_BEGIN] = { .t = '(', .ty = TTY_OBJ_REF_DEL},
	[T_OBJ_PROC_APPLY_END] = { .t = ')', .ty = TTY_OBJ_REF_DEL},
	[T_ARG_DEF_SEP] = { .t = ',', .ty = TTY_OBJ_REF_DEL},

	/* object reference */
	[T_CHILD] = { .t = '/', .ty = TTY_OBJ_REF}, /* doubles division */
	[T_REF] = { .t = '@', .ty = TTY_OBJ_REF},
	[T_CAST] = { .t = '.', .ty = TTY_OBJ_REF}, /* doubles parent */

	/* object definition */
	[T_OBJ_DEF_BEGIN] = { .t = '{', .ty = TTY_OBJ_DEF},
	[T_OBJ_DEF_END] = { .t = '}', .ty = TTY_OBJ_DEF},
	[T_ASSIGN] = { .t = ':', .ty = TTY_OBJ_DEF},

	/* expression control */
	[T_EXPR_END] = { .t = ';', .ty = TTY_EXPR},
	[T_SELF] = { .t = '^', .ty = TTY_EXPR}, /* doubles bitwise XOR */

	/* misc syntax */
	[T_STRING] = { .t = '"', .ty = TTY_SYN},
	[T_COMMENT] = { .t = '#', .ty = TTY_SYN},
	[T_LITERAL] = { .t = '$', .ty = TTY_SYN},

	/* math operation */
	[T_MATH_PLUS] = { .t = '+', .ty = TTY_MATH_OP },
	[T_MATH_TIMES] = { .t = '*', .ty = TTY_MATH_OP },
	[T_MATH_MINUS] = { .t = '-', .ty = TTY_MATH_OP },
	[T_MATH_MOD] = { .t = '%', .ty = TTY_MATH_OP },

	/* bool comparison */
	[T_BOOL_EQ] = { .t = '=', .ty = TTY_BOOL_CMP },

	/* bool operation */
	[T_BOOL_NEG] = { .t = '!', .ty = TTY_BOOL_OP },

	/* bitwise operation */
	[T_BIT_NEG] = { .t = '~', .ty = TTY_BITWISE_OP },
	[T_BIT_AND] = { .t = '&', .ty = TTY_BITWISE_OP },
	[T_BIT_OR] = { .t = '|', .ty = TTY_BITWISE_OP },

};

const uint keyword_manifest_len = sizeof (keyword_manifest) / sizeof (*keyword_manifest);
const uint token_manifest_len = sizeof (token_manifest) / sizeof (*token_manifest);
