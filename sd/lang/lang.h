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

#  ifndef NULL
#    define NULL (void*) 0x0
#  endif

typedef unsigned short id;

enum kwty {
	KWTY_BUILTIN_OBJ,
	KWTY_BUILTIN_TY,
	KWTY_OBJ_DEF,
	KWTY_QUAL,
	KWTY_FLOW,
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
	T_ARRAY,
};

enum ptq {
	Q_HB_SIGNED = 1,
	Q_HB_UNSIGNED // TODO: bit fields
};

typedef enum kwty Kwty;
typedef enum tty Tty;

struct data {
	enum pt ty;
	enum ptq qual;
	void* data;
};

struct obj {
	struct data data;
	struct obj* pr;
	struct obj* cd;
};

typedef struct obj Obj;

extern Obj g_root;
#endif

#ifndef LOCK_LANG_TXT
#  define LOCK_LANG_TXT

typedef struct _kw {
	Kwty ty;
	id id;
	char* kw;
} txt_Kw;


typedef struct _t {
	Tty ty;
	char t;
} txt_T;

#endif
