/**
 * @file match.c
 *
 * @brief virtual match token definition
 *
 * This file contains virtual match
 * token interfaces
 */

#include <sd/lang/tokens/virtual/gen/id.h>
#include <sd/lang/tokens/virtual/match.h>
#include <sd/lang/tokens/gen/txtmaps.h>

#define match(x) { .with = x, .ty = MATCHER } ///< @brief virtual match token identification interface as *matcher*
#define matchee(x) { .with = x, .ty = MATCHEE } ///< @brief virtual match token identification interface as *matchee*
#define match_self(x) { .with = x, .ty = MATCHSELF } ///< @brief virtual match token identification interface as *self match*

/// @brief virtual match token manifest, identified by text
static const vtid_match_txt txt[] = {
	[norm_match_txt (_OBJ_BEGIN)] = match (']'),
	[norm_match_txt (_OBJ_END)] = matchee ('['),
	[norm_match_txt (_PROC_BEGIN)] = match (')'),
	[norm_match_txt (_PROC_END)] = matchee ('('),
	[norm_match_txt (_BODY_BEGIN)] = match ('}'),
	[norm_match_txt (_BODY_END)] = matchee ('{'),
	[norm_match_txt (_SCHAR)] = match_self ('\''),
	[norm_match_txt (_DCHAR)] = match_self ('"'),
};

/// @brief virtual match token manifest, identified by a mask
static const vtid_match_txt mask[] = {
	[norm_match_mask (_MOD_BEGIN)] = match ('<'),
	[norm_match_mask (_MOD_END)] = matchee ('>'),
	[norm_match_mask (_ARR_BEGIN)] = match ('<'),
	[norm_match_mask (_ARR_END)] = matchee ('>'),
};

/// @brief virtual match token manifest
const vtid_match vtoken_manifest_match = {
	.txt = (vtid_match_txt*)txt,
	.mask = (vtid_match_mask*)mask,
	.comp = (vtid_match_comp*)0,
};
