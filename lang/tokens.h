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

#ifndef LOCK_TOKENS_KWORDS
#  define LOCK_TOKENS_KWORDS
enum keyword {
	KW_ASSIGN,
	KW_ASYNC,
	KW_BRANCH,
	KW_CHILD,
	KW_CONST,
	KW_CAST,
	KW_EXPORT,
	KW_EXPR,
	KW_ENUM,
	KW_END,
	KW_FLOAT,
	KW_HERE,
	KW_IMPORT,
	KW_INT,
	KW_JUMP,
	KW_LIST,
	KW_LITERAL,
	KW_MAP,
	KW_NULL,
	KW_NEW,
	KW_OBJECT,
	KW_PARENT,
	KW_PROC,
	KW_STRING,
	KW_STATIC,
	KW_SYNC,
	KW_THIS,
	KW_VAR,
	KW_WRAP
};

typedef enum keyword Kw;

#  ifndef LOCK_TOKENS_KWORDS_MANIFEST
#    define LOCK_TOKENS_KWORDS_MANIFEST
static const char* Keyword_manifest[] = {
	[KW_ASSIGN] = "assign",
	[KW_ASYNC] = "async",
	[KW_BRANCH] = "branch",
	[KW_CHILD] = "child",
	[KW_CONST] = "const",
	[KW_CAST] = "cast",
	[KW_EXPORT] = "export",
	[KW_EXPR] = "expr",
	[KW_ENUM] = "enum",
	[KW_END] = "end",
	[KW_FLOAT] = "float",
	[KW_HERE] = "here",
	[KW_IMPORT] = "import",
	[KW_INT] = "int",
	[KW_JUMP] = "jump",
	[KW_LIST] = "list",
	[KW_LITERAL] = "literal",
	[KW_MAP] = "map",
	[KW_NULL] = "null",
	[KW_NEW] = "new",
	[KW_OBJECT] = "object",
	[KW_PARENT] = "parent",
	[KW_PROC] = "proc",
	[KW_STRING] = "string",
	[KW_STATIC] = "static",
	[KW_SYNC] = "sync",
	[KW_THIS] = "this",
	[KW_VAR] = "var",
	[KW_WRAP] = "wrap"
};
#  endif
#endif

#ifndef LOCK_TOKENS_HEADER
#  define LOCK_TOKENS_HEADER
// TODO: push this variable to another translation unit
enum token {
	T_ASSIGN,
	T_CHILD,
	T_REF,
	T_KW_REF,
	T_EXPR_END,
	T_OBJ_BEGIN_ASCII,
	T_OBJ_END_ASCII,
	T_OBJ_REF_BEGIN_ASCII,
	T_OBJ_REF_END_ASCII,
	T_PROC_REF_BEGIN_ASCII,
	T_PROC_REF_END_ASCII,
	T_STRING,
	T_COMMENT,
	T_SELF,
	T_DOLLAR,
	T_GEN_ESC
};

typedef enum token Tk;

#  ifndef LOCK_TOKENS_HEADER_MANIFEST
#    define LOCK_TOKENS_HEADER_MANIFEST
static const char Token_manifest[] = {
	[T_ASSIGN] = ':',
	[T_CHILD] = '/',
	[T_KW_REF] = '#',
	[T_REF] = '@',
	[T_EXPR_END] = ';',
	[T_OBJ_BEGIN_ASCII] = '{',
	[T_OBJ_END_ASCII] = '}',
	[T_OBJ_REF_BEGIN_ASCII] = '[',
	[T_OBJ_REF_END_ASCII] = ']',
	[T_PROC_REF_BEGIN_ASCII] = '(',
	[T_PROC_REF_END_ASCII] = ')',
	[T_STRING] = '"',
	[T_COMMENT] = '-',
	[T_SELF] = '^',
	[T_DOLLAR] = '$',
	[T_GEN_ESC] = '\\'
};
#  endif
#endif

#ifndef LOCK_MANIFEST_LEN
#  define LOCK_MANIFEST_LEN

#  include "../utils/types/shared.h"

static const uint Keyword_manifest_len =
	sizeof (Keyword_manifest) / sizeof (*Keyword_manifest);
static const uint Token_manifest_len =
	sizeof (Token_manifest) / sizeof (*Token_manifest);
#endif
