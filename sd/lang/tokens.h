/**
 * This file contains all the arrays
 * for all keywords and tokens of
 * the standard sd language sorted
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
 */

#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#ifndef LOCK_TOKENS_KWORDS
#  define LOCK_TOKENS_KWORDS

#  ifndef LOCK_TOKENS_KWORDS_MANIFEST
#    define LOCK_TOKENS_KWORDS_MANIFEST
static const _Kw keyword_manifest[] = {

	/* built-in data types */
	[KW_INT] = { .kw = "int", .ty = KWTY_BUILT_IN_TY },
	[KW_UINT] = { .kw = "uint", .ty = KWTY_BUILT_IN_TY },
	[KW_FLOAT] = { .kw = "float", .ty = KWTY_BUILT_IN_TY },
	[KW_STRING] = { .kw = "string", .ty = KWTY_BUILT_IN_TY },
	[KW_ENUM] = { .kw = "enum", .ty = KWTY_BUILT_IN_TY },
	[KW_LIST] = { .kw = "list", .ty = KWTY_BUILT_IN_TY },
	[KW_PROC] = { .kw = "proc", .ty = KWTY_BUILT_IN_TY },

	/* qualifiers */
	[KW_CONST] = { .kw = "const", .ty = KWTY_QUAL },
	[KW_STATIC] = { .kw = "static", .ty = KWTY_QUAL },
	[KW_LITERAL] = { .kw = "literal", .ty = KWTY_QUAL },
	[KW_HERE] = { .kw = "here", .ty = KWTY_QUAL },
	[KW_NEW] = { .kw = "new", .ty = KWTY_QUAL },
	[KW_VAR] = { .kw = "var", .ty = KWTY_QUAL },

	/* built-in objects */
	[KW_NIL] = { .kw = "nil", .ty = KWTY_BUILT_IN_OBJ },
	[KW_THIS] = { .kw = "this", .ty = KWTY_BUILT_IN_OBJ },

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
	[KW_ROOT] = { .kw = "root", .ty = KWTY_ENV },
	[KW_IMPORT] = { .kw = "import", .ty = KWTY_ENV },
	[KW_CAST] = { .kw = "cast", .ty = KWTY_ENV },
	[KW_WRAP] = { .kw = "wrap", .ty = KWTY_ENV }

};
#  endif
#endif

#ifndef LOCK_TOKENS_HEADER
#  define LOCK_TOKENS_HEADER

#  ifndef LOCK_TOKENS_HEADER_MANIFEST
#    define LOCK_TOKENS_HEADER_MANIFEST
static const _T token_manifest[] = {

	/* object reference */
	[T_OBJ_RES_BEGIN] = { .t = '[', .ty = TTY_REF},
	[T_OBJ_RES_END] = { .t = ']', .ty = TTY_REF},
	[T_OBJ_PROCRES_BEGIN] = { .t = '(', .ty = TTY_REF},
	[T_OBJ_PROCRES_END] = { .t = ')', .ty = TTY_REF},
	[T_CHILD] = { .t = '/', .ty = TTY_REF},
	[T_KW_REF] = { .t = '#', .ty = TTY_REF},

	/* object definition */
	[T_OBJ_PROCDEF_BEGIN] = { .t = '{', .ty = TTY_DEF},
	[T_OBJ_PROCDEF_END] = { .t = '}', .ty = TTY_DEF},
	[T_ASSIGN] = { .t = ':', .ty = TTY_DEF},

	/* expression control */
	[T_EXPR_END] = { .t = ';', .ty = TTY_EXPR},

	/* misc syntax */
	[T_STRING] = { .t = '"', .ty = TTY_SYN},
	[T_COMMENT] = { .t = '-', .ty = TTY_SYN},
	[T_SELF] = { .t = '^', .ty = TTY_SYN},
	[T_DOLLAR] = { .t = '$', .ty = TTY_SYN},
	[T_GEN_ESC] = { .t = '\\', .ty = TTY_SYN}

};
#  endif
#endif

#ifndef LOCK_MANIFEST_LEN
#  define LOCK_MANIFEST_LEN

#  include <sd/utils/types/shared.h>

static const uint keyword_manifest_len =
	sizeof (keyword_manifest) / sizeof (*keyword_manifest);

static const uint token_manifest_len =
	sizeof (token_manifest) / sizeof (*token_manifest);
#endif
