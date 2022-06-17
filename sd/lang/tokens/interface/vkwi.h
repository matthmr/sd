/**
 * @file vkwi.h
 *
 * @brief keyword virtualisation interface
 *
 * This file contains global interfaces
 * for keywords (and virtual keywords) that
 * virtualise
 */

#ifndef LOCK_VIRTUAL_KWINTERFACE
#  define LOCK_VIRTUAL_KWINTERFACE ///< lock: standard lock

#  include <sd/lang/tokens/virtual/kw/gen/kwid.h>
#  include <sd/lang/tokens/groups.h>

/// @brief common interface for virtual keywords
#  define __kcommon__(_kwid, _kwty) \
{ \
	.id = _kwid, \
	.ty = _kwty, \
}

typedef const char pair[2];
typedef const char txtbit[4];

// NOTE: this sparses memory but honestly this
// is so small it should even matter even in the
// most memory-lacking embedded systems

/// @note this is only valid if the keyword has
///       two or less ways of being implied via
///       a literal suffix
static const pair suffix_ty[] = {
	[_LONG] = {'L', 'l'},
	[__UNSIGNED] = {'U', 'u'},

	[_FLOAT] = {'F', 'f'},
	[_DOUBLE] = {'D', 'd'},
};

/// @brief keyword compound prefix manifest
static const char kwprefix[] = {
	[__SIGNED] = 'i',
	[__UNSIGNED] = 'u',

	[_FLOAT] = 'f',
};

/// @note this is only valid up to 512 bit variables.
///       anything bigger than that becomes an array
static const txtbit suffix_bits[] = {
	[_CHAR] = {'8'},
	[_SHORT] = {'1', '6'},
	[_INT] = {'3', '2'},
	[_LONG] = {'6', '4'},

	[_FLOAT] = {'3', '2'},
	[_DOUBLE] = {'6', '4'},
};

struct _kw_common {
	// `int' promotes itself to the appropiate enum;
	const int id;

	const Kwty ty;
};

typedef struct _kw_common _Kw_common;

#endif
