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

/// @brief virtual compound direct token index getter
#  define compgetter(x) 

typedef unsigned short vtid_comp_direct;

struct vtid_comp_indirect {
	short against;
	short make;
};

typedef struct vtid_comp_indirect vtid_comp_indirect[];

struct vtid_comp {
	vtid_comp_direct* direct;
	vtid_comp_indirect* indirect;
};

typedef struct vtid_comp vtid_comp;
extern const vtid_comp vtoken_manifest_comp;

#endif
