/**
 * This file contains all syntax for the SD
 * language. It is format-agnostic, meaning
 * this source is included into different
 * parsers for their respective formats
 */

#ifndef LOCK_LANG
#  define LOCK_LANG

typedef unsigned short id;

enum kwty {
	KWTY_BUILTIN_OBJ,
	KWTY_BUILTIN_TY,
	KWTY_OBJ_DEF,
	KWTY_QUAL,
	KWTY_FLOW,
	KWTY_LOOP,
	KWTY_ENV,
	KWTY_ACC,
};

enum tty {
	TTY_OBJ_REF_DEL,
	TTY_BITWISE_OP,
	TTY_BOOL_CMP,
	TTY_OBJ_REF,
	TTY_OBJ_DEF,
	TTY_MATH_OP,
	TTY_BOOL_OP,
	TTY_EXPR,
	TTY_SYN,
};

enum pt {
	T_CHAR = 1,
	T_INT,
	T_FLOAT,
	T_ENUM,
	T_ARRAY,
	T_MAP,
};

enum ptq {
	Q_HB_SIGNED = 1,
	Q_HB_UNSIGNED // TODO: bit fields
};

typedef enum kwty Kwty;
typedef enum tty Tty;

#endif

#ifndef LOCK_LANG_TXT
#  define LOCK_LANG_TXT

typedef struct _kw {
	char* kw;
	id id;
	Kwty ty;
} _Kw;


typedef struct _t {
	char t;
	Tty ty;
} _T;

#endif
