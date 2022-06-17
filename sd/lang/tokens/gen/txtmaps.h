/**
 * @file txtmaps.h
 *
 * @brief basic keyword and token definitions
 *
 * This file contains generic type definitions
 * for utils for tokens and keywords identification
 */

#ifndef LOCK_TXTMAPS_KW
#  define LOCK_TXTMAPS_KW ///< lock: lock keywords

// TODO: overwrite `T_` tokens with these as bytecode
/// @brief keyword identification
enum kwid {

	/* built-in data types */
	_BOOL = 0x0001,

	/* qualifiers */
	_CONST = 0x0002,
	_STATIC = 0x0003,
	_UNSIGNED = 0x0004,
	_SCOPE = 0x0005,
	_HERE = 0x0006,

	/* modifiers */
	_ENUM = 0x0007,
	_SIGNED = 0x0008,

	/* object definition */
	_RM = 0x0009,
	_TYPE = 0x000a,
	_TAG = 0x000b,
	_LET = 0x000c,
	_PROC = 0x000d,

	/* scope control */
	_IMPORT = 0x000e,
	_IMPL = 0x000f,
	_UNWRAP = 0x0010,
	_WRAP = 0x0011,

	/* built-in objects */
	_NIL = 0x0012,
	_TRUE = 0x0013,
	_FALSE = 0x0014,
	_THIS = 0x0015,

	/* flow control */
	_ASYNC = 0x0016,
	_SYNC = 0x0017,
	_END = 0x0018,
	_JUMP = 0x0019,
	_RET = 0x001a,
	_GOTO = 0x001b,
	_BRANCH = 0x001c,
	_PEEK = 0x001d,
	_LABEL = 0x001e,

	/* literal syntax */
	_AS = 0x001f,
	_RES = 0x0020,

	/* loops */
	_ITER = 0x0021,

};

typedef enum kwid Kwid;

#ifndef _KWID_BOUND
#  define _KWID_BOUND _ITER ///< lock: lock @p _KWID_BOUND, the upper bound for character tokens
#endif

#endif

#ifndef LOCK_TXTMAPS_T
#  define LOCK_TXTMAPS_T ///< lock: lock tokens

#  define tid_append(x) _KWID_BOUND+x

/// @brief token identification
/// This does **not** include virtual tokens.
/// All tokens here can be identified by a **single character**
/// @note `SCHAR` is used instead of `char` to avoid
///       name collision with `Kwid`'s `char`, so
///       that makes `_STRING` `_DCHAR`
enum tid {

	/* reference delimiters */
	_OBJ_BEGIN = tid_append (0x001),
	_OBJ_END = tid_append (0x0002),
	_BOOL_LT = tid_append (0x0003),
	_BOOL_GT = tid_append (0x0004),
	_PROC_BEGIN = tid_append (0x0005),
	_PROC_END = tid_append (0x0006),
	_SEP = tid_append (0x0007),

	/* object reference */
	_CHILD = tid_append (0x0008),
	_REF = tid_append (0x0009),
	_CAST = tid_append (0x000a),

	/* object definition */
	_BODY_BEGIN = tid_append (0x000b),
	_BODY_END = tid_append (0x000c),
	_ASSIGN = tid_append (0x000d),

	/* expression control */
	_EXPR_END = tid_append (0x000e),
	_SELF = tid_append (0x000f),

	/* misc syntax */
	_DCHAR = tid_append (0x0010),
	_COMMENT = tid_append (0x0011),
	_LIT = tid_append (0x0012),
	_SCHAR = tid_append (0x0013),

	/* math operation */
	_MATH_PLUS = tid_append (0x0014),
	_MATH_TIMES = tid_append (0x0015),
	_MATH_MINUS = tid_append (0x0016),

	/* bool comparison */
	_BOOL_EQ = tid_append (0x0017),

	/* bool operation */
	_BOOL_NEG = tid_append (0x0018),

	/* bitwise operation */
	_BIT_NEG = tid_append (0x0019),
	_BIT_AND = tid_append (0x001a),
	_BIT_OR = tid_append (0x001b),

	/* piping */
	_PIPE = tid_append (0x001c),

	/* conditional branching */
	_IF = tid_append (0x001d),

};

typedef enum tid Tid;
#endif

#ifndef LOCK_TXTMAPS_BOUND
#  define LOCK_TXTMAPS_BOUND ///< lock: lock @p _TID_BOUND, the upper bound
                             ///        for virtual tokens
#  define _TID_BOUND _IF
#endif
