/**
 * This file contains bytecode
 * definition of core
 * objects in SD
 */

#ifndef LOCK_CORE_LANG_BYTECODE
#  define LOCK_CORE_LANG_BYTECODE

#  include <sd/utils/types/shared.h>

/* these are what gets sorted at compile time
 * as seen in <sd/lang/tokens.h>
 */
enum keyword {
	KW_ASSIGN,
	KW_ASYNC,
	KW_BRANCH,
	KW_CONST,
	KW_EXPORT,
	KW_EXPR,
	KW_ENUM,
	KW_END,
	KW_FLOAT,
	KW_HERE,
	KW_IMPORT,
	KW_ITER,
	KW_INT,
	KW_JUMP,
	KW_LIST,
	KW_LET,
	KW_MAP,
	KW_NIL,
	KW_NEW,
	KW_PROC,
	KW_STRING,
	KW_STATIC,
	KW_SYNC,
	KW_THIS,
	KW_TYPE,
	KW_UINT,
	KW_WRAP
};

typedef enum keyword Kw;

enum token {
	T_ASSIGN,
	T_CHILD,
	T_REF,
	T_KW_REF,
	T_EXPR_END,
	T_ARG_DEF_SEP,
	T_OBJ_REF_BEGIN,
	T_OBJ_REF_END,
	T_OBJ_DEF_BEGIN,
	T_OBJ_DEF_END,
	T_MOD_REF_BEGIN,
	T_MOD_REF_END,
	T_OBJ_PROC_APPLY_BEGIN,
	T_OBJ_PROC_APPLY_END,
	T_STRING,
	T_SSTRING,
	T_COMMENT,
	T_SELF
};

typedef enum token T;

#endif
