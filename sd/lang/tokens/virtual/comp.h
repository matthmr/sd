/**
 * @file comp.h
 *
 * @brief virtual compound token definition
 *
 * This file contains virtual compound
 * token interfaces
 */

#ifndef LOCK_VIRTUAL_COMPOUND
#  define LOCK_VIRTUAL_COMPOUND ///< lock: standard lock

#  include <sd/lang/tokens/virtual/gen/id.h>

struct vtid_comp_txt {
	const char with;
	const _vti common;
};

struct vtid_comp_mask {
	const _vti common
}

typedef struct vtid_comp_txt vtid_comp_txt;
typedef struct vtid_comp_mask vtid_comp_mask;
typedef struct vtid_comp_comp vtid_comp_comp;

struct vtid_comp {
	const vtid_comp_txt* txt;
	const vtid_comp_mask* mask;
	const vtid_comp_comp* comp;
};

typedef struct vtid_comp vtid_comp;
extern const vtid_comp vtoken_manifest_comp;

#endif
