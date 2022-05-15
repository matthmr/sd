/**
 * @file precedence.h
 *
 * @brief precedence logic
 *
 * This file contains logic
 * for operator precedence
 */

#ifndef LOCK_OPPRE
#  define LOCK_OPPRE ///< lock: standard lock

#  include <sd/utils/types/shared.h>

#  define prec(x) opptab[x].prec ///< get the precedence of `x`
#  define ass(x) opptab[x].ass ///< get the associativity of `x`

// -- ASSOCIATIVITY VALUES -- //
#  define LR '\0'
#  define RL '\1'

/// @brief precendence & associativity struct
struct precedence {
	uint prec;
	bool ass;
};

typedef struct precedence Prec;
extern const Prec opptab[];

#endif
