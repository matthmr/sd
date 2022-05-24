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

// -- vtid_comp* indexer -- //
#  define norm_comp_txt_dir(x) (x - _BOOL_LT)
#  define norm_comp_txt_indir(x) (x - _BOOL_LT)
#  define norm_comp_comp(x) (x - _IF)

#  include <sd/lang/tokens/interface/vti.h>

// `struct vtid_comp_txt`
struct vtid_comp_txt_xdir {
	const unsigned char with;
	const _vti common;
};

typedef struct vtid_comp_txt_xdir vtid_comp_txt_dir;
typedef struct vtid_comp_txt_xdir vtid_comp_txt_indir;

// -- virtual compound -- //
struct vtid_comp_txt {
	const vtid_comp_txt_dir* direct;
	const vtid_comp_txt_indir* indirect;
};

struct vtid_comp_mask {
	const _vti common;
};

struct vtid_comp_comp {
	const unsigned char with;
	const _vti common;
};

typedef struct vtid_comp_txt vtid_comp_txt;
typedef struct vtid_comp_mask vtid_comp_mask;
typedef struct vtid_comp_comp vtid_comp_comp;

// -- compound interface -- //
struct vtid_comp {
	const vtid_comp_txt* txt;
	const vtid_comp_mask* mask;
	const vtid_comp_comp* comp;
};

typedef struct vtid_comp vtid_comp;
extern const vtid_comp vtoken_manifest_comp;

#endif
