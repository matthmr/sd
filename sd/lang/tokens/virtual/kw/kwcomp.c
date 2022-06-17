/**
 * @file kwcomp.c
 *
 * @brief virtual compound keyword definition
 *
 * This file contains virtual compound
 * keyword definition
 */

#include <sd/lang/tokens/virtual/kw/gen/kwid.h>
#include <sd/lang/tokens/virtual/kw/kwcomp.h>

/// @brief virtual compound keyword manifest, identified by sign
static const vkwid _sign[] = {
	_CHAR,
	_SHORT,
	_INT,
	_LONG,
};

/// @brief virtual compound keyword manifest, identified by sign
static const vkwid _float[] = {
	_FLOAT,
	_DOUBLE,
};

/// @brief virtual compound keyword manifest, identified by type
/// @note this assumes that every type is followed by
///       its bitwise length (e.g `i32`, `f64`)
const vkwid_comp vkeyword_manifest_comp = {
	._sign = (vkwid*) _sign,
	._float = (vkwid*) _float,
};
