/**
 * @file match.c
 *
 * @brief virtual match token definition
 *
 * This file contains virtual match
 * token interfaces
 */

/*
 * here we use the fact that match tokens
 * generally have matchees that don't
 * have any virtual tokens themselves
 */

#include <sd/lang/tokens/virtual/gen/id.h>
#include <sd/lang/tokens/virtual/match.h>
#include <sd/lang/tokens/gen/txtmaps.h>

#define match(x,y) {.with = x, .ty = y} ///< @brief virtual match token identification interface

/// @brief virtual match token manifest, identified by text
const vtid_match_txt txt[] = {
	[lower_match_txt (_OBJ_BEGIN)] = match ('[', MATCHER),
	[lower_match_txt (_OBJ_END)] = match (']', MATCHEE),

	[lower_match_txt (_PROC_BEGIN)] = match ('(', MATCHER),
	[lower_match_txt (_PROC_END)] = match (')', MATCHEE),

	[lower_match_txt (_ARR_BEGIN)] = match ('<', MATCHER),
	[lower_match_txt (_ARR_END)] = match ('>', MATCHEE),

	[lower_match_txt (_BODY_BEGIN)] = match ('{', MATCHER),
	[lower_match_txt (_BODY_END)] = match ('}', MATCHEE),

	[lower_match_txt (_SCHAR)] = match ('\'', MATCHER|MATCHEE),
	[lower_match_txt (_DCHAR)] = match ('"', MATCHER|MATCHEE),
};

/// @brief virtual match token manifest, identified by a mask
const vtid_match_txt mask[] = {
	[lower_match_mask (_MOD_BEGIN)] = match ('<', MATCHER),
	[lower_match_mask (_MOD_END)] = match ('>', MATCHEE),
};

/// @brief virtual match token manifest
const vtid_match vtoken_manifest_match = {
	.txt = (vtid_match_txt*)txt,
	.mask = (vtid_match_mask*)mask,
	.comp = (vtid_match_comp*)0, // so far, there are no compound matches that AREN'T also procedurally generated
};
