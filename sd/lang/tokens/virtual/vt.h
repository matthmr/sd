/**
 * @file vt.h
 *
 * @brief virtual token definition
 *
 * This file contains virtual
 * tokens bundled up using
 * a defined interface
 */

#ifndef LOCK_VIRTUAL
#  define LOCK_VIRTUAL ///< lock: standard lock

#  include <sd/lang/tokens/virtual/gen/tid.h>

#  include <sd/utils/types/shared.h>
#  include <sd/utils/macros.h>

// manifest nesters
#  define NEST &(struct _vt)
#  define VIRT (struct _vt)
#  define NONEST { 0 }
#  define NOVIRT (struct _vt)
#  define ENDALL { .this = { .vty = VNONE }, .next = (struct _vt*)0 }

#  define DONE (struct _vt*)
#  define ALL(...) \
{ \
	.this = (struct _vt_virtual) {0}, \
	.next = (struct _vt*)&(struct _vt[]) { __VA_ARGS__ }, \
}

// virtual token compile-time definition interface
#  define __comp__(_with, _cid, _cty, _cprec, _cass, _cvt, _csfix, _vop, _vnext) \
{\
	.this = { \
		.vty = VCOMP, \
		._ = { \
			.comp = { \
				.with = _with, \
				._ = __common__ (_cid, _cty, _cprec, _cass, _cvt, _csfix), \
			}, \
		}, \
	}, \
	.next = _vop _vnext, \
}

#  define __match__(_matchty, _cid, _cty, _cprec, _cass, _cvt, _csfix, _vop, _vnext) \
{ \
	.this = { \
		.vty = VMATCH, \
		._ = { \
			.match = { \
				.ty = _matchty, \
				._ = __common__ (_cid, _cty, _cprec, _cass, _cvt, _csfix), \
			}, \
		}, \
	}, \
	.next = _vop _vnext, \
}

#  define __mask__(_cid, _cty, _cprec, _cass, _cvt, _csfix, _vop, _vnext) \
{ \
	.this = { \
		.vty = VMASK, \
		._ = { \
			.mask = { \
				._ = __common__ (_cid, _cty, _cprec, _cass, _cvt, _csfix), \
			}, \
		}, \
	}, \
	.next = _vop _vnext, \
}

// `struct _vt`
enum vty {
	VNONE = 0,
	VMATCH = BIT (0),
	VCOMP = BIT (1),
	VMASK = BIT (2),
};

// `union __vt_virtual`
struct vt_comp {
	const int with;
	const _T_common _;
};

// `struct vt_match`
#define V_MMATCHER '\0'
#define V_MMATCHEE '\1'
#define V_MSELF '\2'

// `union __vt_struct`
struct vt_match {
	const char ty;
	const _T_common _;
};

// `union __vt_struct`
struct vt_mask {
	const _T_common _;
};

/// @note the union give a ~54%
/// decrease in memory than all
/// its fields
// `struct _vt_virtual`
union __vt_virtual {
	const struct vt_mask mask;
	const struct vt_comp comp;
	const struct vt_match match;
};

// `struct _vt`
struct _vt_virtual {
	const union __vt_virtual _;
	const enum vty vty;
};

/// @brief virtual token interface bundle, with support for
/// pointer-cast nesting *or* linked list nesting
struct _vt {
	const struct _vt_virtual this;
	const struct _vt* next;
};

typedef struct _vt _vT;

#endif
