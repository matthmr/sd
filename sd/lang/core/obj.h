/**
 * This file contains bytecode
 * definition of objects in SD
 */

#ifndef LOCK_CORE_LANG_BYTECODE
#  define LOCK_CORE_LANG_BYTECODE

#  include <sd/utils/types/shared.h>

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

typedef enum token T;

#endif
