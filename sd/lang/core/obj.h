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
	KW_ARRAY,
	KW_ASYNC,
	KW_BRANCH,
	KW_BOOL,
	KW_CONST,
	KW_CHAR,
	KW_EXPR,
	KW_ENUM,
	KW_END,
	KW_FLOAT,
	KW_FALSE,
	KW_GOTO,
	KW_IMPORT,
	KW_ITER,
	KW_INT,
	KW_JUMP,
	KW_LOCAL,
	KW_LONG,
	KW_LET,
	KW_MAP,
	KW_MUL,
	KW_NIL,
	KW_NEW,
	KW_PROC,
	KW_RET,
	KW_RM,
	KW_STATIC,
	KW_SCOPE,
	KW_SHORT,
	KW_SYNC,
	KW_THIS,
	KW_TRUE,
	KW_UNSIGNED,
	KW_WRAP,
};

typedef enum keyword Kw;

/* the elements indexed by this enum
 * are ascii only, so this is sorted
 * merely by numeric value */
enum token {
	T_BOOL_NEG,
	T_STRING,
	T_COMMENT,
	T_LITERAL,
	T_MATH_MOD,
	T_BIT_AND,
	T_OBJ_PROC_APPLY_BEGIN,
	T_OBJ_PROC_APPLY_END,
	T_MATH_TIMES,
	T_MATH_PLUS,
	T_ARG_DEF_SEP,
	T_MATH_MINUS,
	T_CAST,
	T_CHILD,
	T_ASSIGN,
	T_EXPR_END,
	T_MOD_REF_BEGIN,
	T_BOOL_EQ,
	T_MOD_REF_END,
	T_REF,
	T_OBJ_REF_BEGIN,
	T_OBJ_REF_END,
	T_SELF,
	T_OBJ_DEF_BEGIN,
	T_BIT_OR,
	T_OBJ_DEF_END,
	T_BIT_NEG,
};

typedef enum token T;

#endif
