/**
 * @file lang.h
 *
 * @brief SD object grouping
 *
 * This file contains object grouping
 * for better separation of tokens
 * and keywords and for more specific
 * hook usage.
 */

#ifndef LOCK_LANG
#  define LOCK_LANG

#  include <sd/lang/tokens/gen/txtmaps.h>

enum kwty {
	KWTY_BUILTIN_OBJ,
	KWTY_BUILTIN_TY,
	KWTY_OBJ_DEF,
	KWTY_QUAL,
	KWTY_FLOW,
	KWTY_LOOP,
	KWTY_ENV,
	KWTY_ACC,
	KWTY_MOD,
};

enum tty {
	TTY_OBJ_REF,
	TTY_OBJ_DEF,
	TTY_OBJ_REF_DEL,

	TTY_BITWISE_OP,
	TTY_MATH_OP,
	TTY_BOOL_OP,

	TTY_BOOL_CMP,
	TTY_EXPR,
	TTY_SYN,
	TTY_PIPE,
	TTY_COND,
};

typedef enum kwty Kwty;
typedef enum tty Tty;
typedef enum vty Vty;

#endif
