/**
 * @file kwcomp.h
 *
 * @brief virtual compound keyword definition
 *
 * This file contains virtual compound
 * keyword definition
 */

#ifndef LOCK_KWCOMP ///< lock: standard lock
#  define LOCK_KWCOMP

#include <sd/lang/tokens/virtual/kw/gen/kwid.h>

struct vkwid_comp {
	const vkwid* _sign;
	const vkwid* _float;
};

typedef struct vkwid_comp vkwid_comp;
extern const vkwid_comp vkeyword_manifest_comp;

#endif
