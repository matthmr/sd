/**
 * @file vti.h
 *
 * @brief token virtualisation interface
 *
 * This file contains global interfaces
 * for tokens (and virtual tokens) that
 * virtualise
 */

#ifndef LOCK_VIRTUAL_INTERFACE
#  define LOCK_VIRTUAL_INTERFACE ///< lock: standard lock

#  include <sd/lang/tokens/groups.h>

#  include <sd/utils/utils.h>

// TODO: maybe `AS_IS` can go away an `SUFFIX_IRR` can come back?
/// @brief virtual interface
/// interface for:
///   - token compounding "<<"       (not necessarily the same token, for instance: '!=')
///   - token matching    "{ ... }"  (open and close are separate)
///   - token masking     "+"        (as in plus operator / unary plus operator)
///   - token suffixing   "1++"      (as in [ 'A*B', '*AB', 'AB*' ])
enum vty {
	AS_IS = BIT (0),           ///< such as: ';'
	COMPOUND_DIR = BIT (1),    ///< such as: '%%'
	COMPOUND_INDIR = BIT (2),  ///< such as: '+:'
	MASK = BIT (3),            ///< such as: '+'
	MATCH = BIT (4),           ///< such as: '['
	SUFFIX_NOC1 = BIT (5),     ///< such as: '+1'
	SUFFIX_CHLD = BIT (6),     ///< such as: '1+1'
	SUFFIX_NOC2 = BIT (7),     ///< such as: '1+'
};

typedef enum vty Vty;

#endif

#ifndef LOCK_VIRTUAL_INTERFACE_STRUCT
#  define LOCK_VIRTUAL_INTERFACE_STRUCT ///< lock: lock `_vti` struct

/// @brief virtual token common interface; similar to Vty
typedef struct _vt_common {
	int id; // int promotes itself to the appropiate enum
	Vty vty;
	Tty ty;
} _vti;

#endif

#ifndef LOCK_VIRTUAL_INTERFACE_GETTER
#  define LOCK_VIRTUAL_INTERFACE_GETTER ///< lock: lock getter macro

/// @brief vty bit field getter
#  define tattr(t,a) (t) & (~a)

#endif
