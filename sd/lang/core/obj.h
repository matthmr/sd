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
	KW_AS,
	KW_ASYNC,
	KW_BOOL,
	KW_CONST,
	KW_CHAR,
	KW_END,
	KW_ENUM,
	KW_FALSE,
	KW_FLOAT,
	KW_GOTO,
	KW_HERE,
	KW_IMPL,
	KW_IMPORT,
	KW_INT,
	KW_ITER,
	KW_JUMP,
	KW_LONG,
	KW_NIL,
	KW_RET,
	KW_RM,
	KW_SCOPE,
	KW_SHORT,
	KW_SIGNED,
	KW_STATIC,
	KW_SYNC,
	KW_TAG,
	KW_THIS,
	KW_TRUE,
	KW_TYPE,
	KW_UNSIGNED,
};

typedef enum keyword Kw;

/* the elements indexed by this enum
 * are ascii only, so this is sorted
 * merely by numeric value */
enum token {
	T_BOOL_NEG,
	T_STRING,
	T_COMMENT,
	T_LABEL,
	T_MATH_MOD,
	T_BIT_AND,
	T_PROC_BEGIN,
	T_PROC_END,
	T_MATH_TIMES,
	T_MATH_PLUS,
	T_SEP,
	T_MATH_MINUS,
	T_CAST,
	T_CHILD,
	T_ASSIGN,
	T_PIPE,
	T_EXPR_END,
	T_MOD_BEGIN,
	T_BOOL_EQ,
	T_MOD_END,
	T_DEREF,
	T_OBJ_BEGIN,
	T_OBJ_END,
	T_SELF,
	T_BODY_BEGIN,
	T_BODY_END,
	T_BIT_OR,
	T_BIT_NEG,
	T_IF,
};

typedef enum token T;

#endif
