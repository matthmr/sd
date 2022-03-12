/**
 * This file contains logic
 * for operator precedence
 */

#ifndef LOCK_OPPRE
#  define LOCK_OPPRE

#  include <sd/utils/types/shared.h>

#  define prec(x) opptab[x].prec
#  define ass(x) opptab[x].ass

// -- ASSOCIATIVITY VALUES -- //
#  define LR 0
#  define RL 1

struct precedence {
	uint prec;
	bool ass;
};

typedef struct precedence Prec;

extern const Prec const opptab[];

#endif
