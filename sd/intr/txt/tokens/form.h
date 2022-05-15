/**
 * @file form.h
 *
 * @brief token forms for plain-text SD source code
 *
 * This file contains definition of token
 * forms for plain-text SD source code,
 * such as interfaces for
 *   - compounding
 *   - matching
 *   - masking
 *   - suffixing
 */

#ifndef LOCK_LANG_TXT
#  define LOCK_LANG_TXT ///< lock: standard lock

#  include <sd/lang/lang.h>

#  include <sd/utils/utils.h>

/// @brief virtual interface
/// interface for:
///   - token compounding "<<"       (not necessarily the same token, for instance: '!=')
///   - token matching    "{ ... }"  (open and close are separate)
///   - token masking     "+"        (as in plus operator / unary plus operator)
///   - token suffixing   "1++"      (as in [ 'A*B', '*AB', 'AB*' ])
enum vty {
	AS_IS = BIT (0),        ///< such as: ';'
	COMPOUND = BIT (1),     ///< such as: '%%'
	MASK = BIT (2),         ///< such as: '+'
	MATCH = BIT (3),        ///< such as: '['
	SUFFIX_NOC1 = BIT (4),  ///< such as: '+1'
	SUFFIX_CHLD = BIT (5),  ///< such as: '1+1'
	SUFFIX_NOC2 = BIT (6),  ///< such as: '1+'
	__PAD__     = BIT (7),  ///< padding bit
};

/// @brief @p vty bit field getter
#  define tattr(token,attr) token & (~attr)

/// @brief plain-text keyword interface
typedef struct _kw {
	char* kw;
	Kwid id;
	Kwty ty;
} _Kw;

/// @brief plain-text token interface
typedef struct _t {
	char t;
	Tid id;
	Vty vty;
	Tty ty;
} _T;

#endif
