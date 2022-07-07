/**
 * @file vti.h
 *
 * @brief token virtualisation interface
 *
 * This file contains global interfaces
 * for tokens (and virtual tokens) that
 * virtualise
 */

#ifndef LOCK_VIRTUAL_TINTERFACE
#  define LOCK_VIRTUAL_TINTERFACE ///< lock: standard lock

#  include <sd/lang/tokens/groups.h>

#  include "utils/types/shared.h"
#  include "utils/macros.h"

/// @brief common interface for virtual tokens
#  define __common__(_cid, _cty, _cprec, _cass, _cvt, _csfix) \
{\
	.id = _cid, \
	.ty = _cty, \
	.vt = _cvt, \
	.prec = { \
		.this = _cprec, \
		.ass = _cass, \
	}, \
	.sfix = _csfix, \
}

/// @brief virtual interface
/// interface for:
///   - token compounding "<<"       (not necessarily the same token, for instance: '!=')
///   - token matching    "{ ... }"  (open and close are separate)
///   - token masking     "+"        (as in plus operator / unary plus operator)
enum vtty {
	AS_IS = 0,
	COMPOUND = BIT (0),    ///< such as: '%%'
	MASK = BIT (1),        ///< such as: '+'
	MATCH = BIT (2),       ///< such as: '['
};

typedef enum vtty Vtty;

/// @brief virtual interface
/// interface for:
///   - token suffixing   "1++"      (as in [ 'A*B', '*AB', 'AB*' ])
enum sfix {
	SUFFIX_NOC1 = BIT (0),     ///< such as: '+1'
	SUFFIX_NOC2 = BIT (1),     ///< such as: '1+'
	SUFFIX_CHLD = BIT (2),     ///< such as: '1+1'
	SUFFIX_OPEN = BIT (3),     ///< such as: '['
	SUFFIX_CLOSE = BIT (4),    ///< such as: ']'
	SUFFIX_IRR = BIT (5),      ///< such as: ';'
};

typedef enum sfix Sfix;

#endif

#ifndef LOCK_VIRTUAL_TINTERFACE_STRUCT
#  define LOCK_VIRTUAL_TINTERFACE_STRUCT ///< lock: lock `_vti` struct

#  define LEFTRIGHT '\0'
#  define RIGHTLEFT '\1'
#  define ASS_IRR '\0'

#  define PREC_IRR -1u /// @note this is true as long as there is no operation with 4294967295th precendence
#  define PREC_INF 0u

struct _t_common_prec {
	const char ass;
	const uint this;
};

typedef struct _t_common_prec Prec;

/// @brief virtual token common interface; similar to Vty
struct _t_common {
	// `int' promotes itself to the appropiate enum;
	const int id;
	const int vt;

	const Prec prec;
	const Tty ty;
	const Sfix sfix;
};

typedef struct _t_common _T_common;

#endif
