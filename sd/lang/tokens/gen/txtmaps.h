/**
 *
 * @file txtmaps.h
 *
 * @brief Basic keyword and token definitions
 *
 * This file contains generic type definitions
 * for utils for tokens and keywords identification
 */

#ifndef LOCK_TXTMAPS_KW
#  define LOCK_TXTMAPS_KW ///< lock: lock keywords

// TODO: implement `double` data type
/// @brief keyword identification
enum kwid {

	/* built-in data types */
	_INT = 0x0001,
	_CHAR = 0x0002,
	_FLOAT = 0x0003,
	_LONG = 0x0004,
	_SHORT = 0x0005,
	_BOOL = 0x0006,

	/* qualifiers */
	_CONST = 0x0007,
	_STATIC = 0x0008,
	_UNSIGNED = 0x0009,
	_SCOPE = 0x000a,
	_HERE = 0x000b,

	/* modifiers */
	_ENUM = 0x000c,
	_SIGNED = 0x000d,

	/* object definition */
	_RM = 0x000e,
	_TYPE = 0x000f,
	_TAG = 0x0010,
	_LET = 0x0011,
	_PROC = 0x0012,

	/* scope control */
	_IMPORT = 0x0013,
	_IMPL = 0x0014,

	/* built-in objects */
	_NIL = 0x0015,
	_THIS = 0x0016,
	_TRUE = 0x0017,
	_FALSE = 0x0018,

	/* flow control */
	_ASYNC = 0x0019,
	_SYNC = 0x001a,
	_END = 0x001b,
	_JUMP = 0x001c,
	_RET = 0x001d,
	_GOTO = 0x001e,
	// _BRANCH 0x001f,

	/* literal syntax */
	_AS = 0x001f,

	/* loops */
	_ITER = 0x0020,

};

typedef enum kwid Kwid;

#ifndef _KWID_BOUND
#  define _KWID_BOUND _ITER ///< lock: lock @p _KWID_BOUND, the upper bound
                            ///        for character tokens
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
	_MOD_BEGIN = tid_append (0x0003),
	_MOD_END = tid_append (0x0004),
	_PROC_BEGIN = tid_append (0x0005),
	_PROC_END = tid_append (0x0006),
	_SEP = tid_append (0x0007),

	/* object reference */
	_CHILD = tid_append (0x0008),
	_DEREF = tid_append (0x0009),
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
	_LABEL = tid_append (0x0012),
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
