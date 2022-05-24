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

// -- vtid_mask* indexer -- //
#  define norm_mask_txt(x) (x - _BOOL_LT)

#  include <sd/lang/tokens/virtual/gen/id.h>

// -- virtual mask -- //
struct vtid_mask_txt {
	const _vti common;
};

typedef struct vtid_mask_txt vtid_mask_txt;
typedef struct vtid_mask_txt vtid_mask_mask;
typedef struct vtid_mask_txt vtid_mask_comp;

// -- mask interface -- //
struct vtid_mask {
	const vtid_mask_txt* txt;
	const vtid_mask_mask* mask;
	const vtid_mask_comp* comp;
};

typedef struct vtid_mask vtid_mask;
extern const vtid_mask vtoken_manifest_mask;

#endif
