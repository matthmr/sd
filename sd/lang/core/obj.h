/**
 * This file contains bytecode
 * definition of core
 * objects in SD
 */

#ifndef LOCK_CORE_LANG_BYTECODE
#  define LOCK_CORE_LANG_BYTECODE

#  include <sd/utils/types/shared.h>

/* these are what gets sorted at compile time
 * as seen in <sd/lang/tokens/txt.h>
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

/* the elements indexed by this enum
 * are ascii only, so this is sorted
 * merely by numeric value */
enum token {
	T_STRING,
	T_COMMENT,
	T_OBJ_PROC_APPLY_BEGIN,
	T_OBJ_PROC_APPLY_END,
	T_ARG_DEF_SEP,
	T_CAST,
	T_CHILD,
	T_ASSIGN,
	T_EXPR_END,
	T_MOD_REF_BEGIN,
	T_MOD_REF_END,
	T_REF,
	T_OBJ_REF_BEGIN,
	T_OBJ_REF_END,
	T_SELF,
	T_OBJ_DEF_BEGIN,
	T_OBJ_DEF_END,
};

typedef enum token T;

#endif
