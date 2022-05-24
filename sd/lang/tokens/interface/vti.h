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
	SUFFIX_IRR = BIT (7),   ///< such as: '{'
};

/// @brief @p vty bit field getter
#  define tattr(token,attr) (token) & (~attr)

typedef enum vty Vty;

#endif
