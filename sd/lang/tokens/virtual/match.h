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

// vtid_match::ty types
#  define MATCHER 1u << 1
#  define MATCHEE 1u << 2
#  define token(x) (x)
#  ifndef is
#    define is(y) & ~(y)
#  endif

typedef unsigned char mty;

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

struct vtid_match {
	vtid_match_txt* txt;
	vtid_match_mask* mask;
	vtid_match_comp* comp;
};

typedef struct vtid_match vtid_match;
extern const vtid_match vtoken_manifest_match;

#endif
