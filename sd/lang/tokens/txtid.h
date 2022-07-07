/**
 * @file txtid.h
 *
 * @brief SD semantics
 *
 * This file contains semantical
 * object definition of SD
 * drivers
 */

#ifndef LOCK_CORE_SEMANTICS
#  define LOCK_CORE_SEMANTICS ///< lock: standard lock

#  include "utils/types/shared.h"

/// @brief keywords
/// these are what gets sorted at compile time
/// as seen in `txt.c`
enum keyword {
	KW_ASYNC,
	KW_AS,
	KW_BOOL,
	KW_BRANCH,
	KW_CONST,
	KW_END,
	KW_ENUM,
	KW_FALSE,
	KW_GOTO,
	KW_HERE,
	KW_IMPL,
	KW_IMPORT,
	KW_ITER,
	KW_JUMP,
	KW_LABEL,
	KW_LET,
	KW_NIL,
	KW_PEEK,
	KW_PROC,
	KW_RES,
	KW_RET,
	KW_RM,
	KW_SCOPE,
	KW_SIGNED,
	KW_STATIC,
	KW_SYNC,
	KW_TAG,
	KW_THIS,
	KW_TRUE,
	KW_TYPE,
	KW_UNSIGNED,
	KW_UNWRAP,
	KW_WRAP,
};

typedef enum keyword Kw;

/// @brief tokens
/// the elements indexed by this enum
/// are ascii only, so this is sorted
/// merely by numeric value
enum token {
	T_BOOL_NEG,
	T_STRING,
	T_COMMENT,
	T_LIT,
	T_MATH_MOD,
	T_BIT_AND,
	T_CHAR,
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
	T_BOOL_LT,
	T_BOOL_EQ,
	T_BOOL_GT,
	T_REF,
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
