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

#include <sd/utils/types/shared.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

const _Kw const keyword_manifest[] = {

	/* built-in data types */
	[KW_INT] = { .kw = "int", .ty = KWTY_BUILTIN_TY },
	[KW_UINT] = { .kw = "uint", .ty = KWTY_BUILTIN_TY },
	[KW_FLOAT] = { .kw = "float", .ty = KWTY_BUILTIN_TY },
	[KW_STRING] = { .kw = "string", .ty = KWTY_BUILTIN_TY },
	[KW_ENUM] = { .kw = "enum", .ty = KWTY_BUILTIN_TY },
	[KW_LIST] = { .kw = "list", .ty = KWTY_BUILTIN_TY },
	[KW_MAP] = { .kw = "map", .ty = KWTY_BUILTIN_TY },
	[KW_ITER] = { .kw = "iter", .ty = KWTY_BUILTIN_TY },

	/* qualifiers */
	[KW_CONST] = { .kw = "const", .ty = KWTY_QUAL },
	[KW_STATIC] = { .kw = "static", .ty = KWTY_QUAL },
	[KW_HERE] = { .kw = "here", .ty = KWTY_QUAL },
	[KW_NEW] = { .kw = "new", .ty = KWTY_QUAL },
	[KW_LET] = { .kw = "let", .ty = KWTY_QUAL },
	[KW_PROC] = { .kw = "proc", .ty = KWTY_QUAL },
	[KW_TYPE] = { .kw = "type", .ty = KWTY_QUAL },

	/* built-in objects */
	[KW_NIL] = { .kw = "nil", .ty = KWTY_BUILTIN_OBJ },
	[KW_THIS] = { .kw = "this", .ty = KWTY_BUILTIN_OBJ },

	/* flow control */
	[KW_EXPR] = { .kw = "expr", .ty = KWTY_FLOW },
	[KW_BRANCH] = { .kw = "branch", .ty = KWTY_FLOW },
	[KW_EXPORT] = { .kw = "export", .ty = KWTY_FLOW },
	[KW_ASYNC] = { .kw = "async", .ty = KWTY_FLOW },
	[KW_SYNC] = { .kw = "sync", .ty = KWTY_FLOW },
	[KW_END] = { .kw = "end", .ty = KWTY_FLOW },
	[KW_JUMP] = { .kw = "jump", .ty = KWTY_FLOW },

	/* environment control */
	[KW_ASSIGN] = { .kw = "assign", .ty = KWTY_ENV },
	[KW_IMPORT] = { .kw = "import", .ty = KWTY_ENV },
	[KW_WRAP] = { .kw = "wrap", .ty = KWTY_ENV }

};

const _T const token_manifest[] = {

	/* reference delimiters */
	[T_OBJ_REF_BEGIN] = { .t = '[', .ty = TTY_OBJ_REF_DEL},
	[T_OBJ_REF_END] = { .t = ']', .ty = TTY_OBJ_REF_DEL},
	[T_MOD_REF_BEGIN] = { .t = '<', .ty = TTY_OBJ_REF_DEL},
	[T_MOD_REF_END] = { .t = '>', .ty = TTY_OBJ_REF_DEL},
	[T_OBJ_PROC_APPLY_BEGIN] = { .t = '(', .ty = TTY_OBJ_REF_DEL},
	[T_OBJ_PROC_APPLY_END] = { .t = ')', .ty = TTY_OBJ_REF_DEL},

	/* object reference */
	[T_CHILD] = { .t = '/', .ty = TTY_OBJ_REF},
	[T_KW_REF] = { .t = '#', .ty = TTY_OBJ_REF},
	[T_REF] = { .t = '@', .ty = TTY_OBJ_REF},
	[T_CAST] = { .t = '.', .ty = TTY_OBJ_REF},

	/* object definition */
	[T_OBJ_DEF_BEGIN] = { .t = '{', .ty = TTY_OBJ_DEF},
	[T_OBJ_DEF_END] = { .t = '}', .ty = TTY_OBJ_DEF},
	[T_ASSIGN] = { .t = ':', .ty = TTY_OBJ_DEF},
	[T_ARG_DEF_SEP] = { .t = ',', .ty = TTY_OBJ_DEF},

	/* expression control */
	[T_EXPR_END] = { .t = ';', .ty = TTY_EXPR},

	/* misc syntax */
	[T_STRING] = { .t = '"', .ty = TTY_SYN},
	[T_SSTRING] = { .t = '\'', .ty = TTY_SYN},
	[T_COMMENT] = { .t = '-', .ty = TTY_SYN},
	[T_SELF] = { .t = '^', .ty = TTY_SYN},

};

const uint keyword_manifest_len = sizeof (keyword_manifest) / sizeof (*keyword_manifest);
const uint token_manifest_len = sizeof (token_manifest) / sizeof (*token_manifest);
