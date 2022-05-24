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

#  include <sd/lang/tokens/virtual/gen/id.h>
#  include <sd/lang/tokens/virtual/match.h>
#  include <sd/lang/tokens/virtual/comp.h>
#  include <sd/lang/tokens/virtual/mask.h>
//  #include <sd/lang/tokens/ctxt/sfix.h>

/// @brief bundles virtualized tokens
///   - _vt::mask masked tokens
///   - _vt::comp compound tokens
///   - _vt::match match tokens
struct _vt {
	const vtid_mask* mask;
	const vtid_comp* comp;
	const vtid_match* match;
};

typedef struct _vt _vT;
extern const _vT vtoken_manifest;

#endif
