/**
 * This file contains logic
 * for operator precedence
 */

#ifndef LOCK_OPPRE
#  define LOCK_OPPRE

#  include <sd/utils/types/shared.h>

// -- ASSOCIATIVITY VALUES -- //
#  define LR 0
#  define RL 1

struct precedence {
	bool pre;
	bool ass;
};

typedef struct precedence Pre;

extern const Pre const opptab[];

#endif
