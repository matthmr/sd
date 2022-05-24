/**
 * @file mask.h
 *
 * @brief virtual masked token definition
 *
 * This file contains virtual masked
 * token interfaces
 */

#ifndef LOCK_VIRTUAL_MASK
#  define LOCK_VIRTUAL_MASK ///< lock: standard lock

#  include <sd/lang/tokens/virtual/gen/id.h>

#  define maskget(x) ///< @brief virtal mask token index getter

struct vtid_mask {
	_vti common;
	
};

typedef struct vtid_mask vtid_mask;
extern const vtid_mask vtoken_manifest_mask[];

#endif
