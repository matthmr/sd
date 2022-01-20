/**
 * This file contains bytecode
 * definition of core
 * objects in SD
 */

#ifndef LOCK_CORE_LANG_BYTECODE
#  define LOCK_CORE_LANG_BYTECODE

#  include <sd/utils/types/shared.h>

/* these are what get sorted at compile time
 * as seen in <sd/lang/tokens.h>
 */
enum keyword {
	KW_ASSIGN,
	KW_ASYNC,
	KW_BRANCH,
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
	KW_NIL,
	KW_NEW,
	KW_OBJECT,
	KW_PROC,
	KW_ROOT,
	KW_STRING,
	KW_STATIC,
	KW_SYNC,
	KW_THIS,
	KW_UINT,
	KW_VAR,
	KW_WRAP
};

typedef enum keyword Kw;

enum token {
	T_ASSIGN,
	T_CHILD,
	T_REF,
	T_KW_REF,
	T_EXPR_END,
	T_OBJ_PROCDEF_BEGIN,
	T_OBJ_PROCDEF_END,
	T_OBJ_RES_BEGIN,
	T_OBJ_RES_END,
	T_OBJ_PROCRES_BEGIN,
	T_OBJ_PROCRES_END,
	T_STRING,
	T_COMMENT,
	T_SELF,
	T_DOLLAR,
	T_GEN_ESC
};

typedef enum token T;

#endif
