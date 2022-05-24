/**
 * @file match.h
 *
 * @brief virtual match token definition
 *
 * This file contains virtual match
 * token interfaces
 */

#ifndef LOCK_VIRTUAL_MATCH
#  define LOCK_VIRTUAL_MATCH ///< lock: standard lock

// -- vtid_match* indexer -- //
#  define norm_match_txt(x) (x - _KWID_BOUND)
#  define norm_match_mask(x) (x - _ARR_BEGIN)

/// @brief match type tagger
enum mty {
	MATCHER,   ///< as matcher
	MATCHEE,   ///< as matchee
	MATCHSELF, ///< as matcher and matchee
};

typedef enum mty mty;

// -- virtual match -- //
struct vtid_match_txt {
	const unsigned char with;
	const mty ty;
};

struct vtid_match_mask {
	const unsigned char with;
	const mty ty;
};

struct vtid_match_comp {
	const unsigned char* with;
	const mty ty;
};

typedef struct vtid_match_txt vtid_match_txt;
typedef struct vtid_match_mask vtid_match_mask;
typedef struct vtid_match_comp vtid_match_comp;

// -- match interface -- //
struct vtid_match {
	vtid_match_txt* txt;
	vtid_match_mask* mask;
	vtid_match_comp* comp;
};

typedef struct vtid_match vtid_match;
extern const vtid_match vtoken_manifest_match;

#endif
