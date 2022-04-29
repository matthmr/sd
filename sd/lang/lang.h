/**
 * This file contains all syntax for the SD
 * language. It is format-agnostic, meaning
 * this source is included into different
 * parsers for their respective formats
 */

#ifndef LOCK_LANG
#  define LOCK_LANG

// `id` comes from <sd/lang/tokens/gen/txtmaps.h>
typedef unsigned short id;

#  include <sd/utils/utils.h>

// interface for:
//   * token compounding "<<"       (not necessarily the same token '!=')
//   * token matching    "{ ... }"  (open and close are separate)
//   * token masking     "+"        (as in plus operator / unary plus operator)
//   * token suffixing   "1++"      (as in [ 'A*B', '*AB', 'AB*' ])
enum vty {
	AS_IS = BIT (0),

	COMPOUND = BIT (1),    // %
	MASK = BIT (2),        // +

	MATCH_OPEN = BIT (3),  // [
	MATCH_CLOSE = BIT (4), // ]

	PREFIX = BIT (5),      // +1
	INFIX = BIT (6),       // 1 + 1
	SUFFIX = BIT (7),      // 1++
};

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

#ifndef LOCK_LANG_TXT
#  define LOCK_LANG_TXT

typedef struct _kw {
	char* kw;
	id id;
	Kwty ty;
} _Kw;

typedef struct _t {
	char t;
	id id;
	Vty vty;
	Tty ty;
} _T;

#endif
