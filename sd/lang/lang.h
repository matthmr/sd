/**
 * This file contains all the internal logic
 * and syntax for the sd language. It is
 * format-agnostic, which means that this
 * source is included into different parsers
 * for their respective formats
 * (binary or plain-text)
 */

#ifndef LOCK_LANG
#  define LOCK_LANG

#  include <sd/lang/langutils.h>

enum kwty {
	KWTY_BUILTIN_TY,
	KWTY_QUAL,
	KWTY_BUILTIN_OBJ,
	KWTY_FLOW,
	KWTY_ENV
};

typedef enum kwty Kwty;

struct _kw {
	Kwty ty;
	char* kw;
};

typedef struct _kw _Kw;

enum tty {
	TTY_OBJ_REF_DEL,
	TTY_OBJ_REF,
	TTY_OBJ_DEF,
	TTY_EXPR,
	TTY_SYN
};

typedef enum tty Tty;

struct _T {
	Tty ty;
	char t;
};

typedef struct _T _T;

#endif
