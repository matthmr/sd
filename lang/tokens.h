/**
 * This file contains all the arrays
 * for all keywords and tokens of
 * the standard sd language sorted
 * by ranking following:
 *
 *   1. alphabetic - repetition - size
 *      aabc
 *      aa
 *      bbcd
 *      bb
 *
 *   2. alphabetic - plain - size
 *      abcd
 *      bcde
 *      cdef
 *
 * They are sorted at compile-time and
 * a simple algorithm gets the type of
 * manifest.
 */

#ifndef LOCK_TOKENS_KWORDS
#  define LOCK_TOKENS_KWORDS
static const char* Keyword_manifest[] = {
	"assign",
	"async",
	"child",
	"const",
	"cast",
	"export",
	"expr",
	"enum",
	"end",
	"float",
	"here",
	"import",
	"int",
	"jump",
	"list",
	"literal",
	"map",
	"null",
	"new",
	"object",
	"parent",
	"proc",
	"string",
	"static",
	"sync",
	"this",
	"var",
	"wrap",
};

#endif

#ifndef LOCK_TOKENS_HEADER
#  define LOCK_TOKENS_HEADER
// TODO: push this variable to another translation unit
enum token {
	ASSIGN,
	CHILD,
	REF,
	EXPR_END,
	OBJ_BEGIN_ASCII,
	OBJ_END_ASCII,
	OBJ_REF_BEGIN_ASCII,
	OBJ_REF_END_ASCII,
	STRING,
	COMMENT,
	GEN_ESC
};

static const char Token_manifest[] = {
	[ASSIGN] = ':',
	[CHILD] = '/',
	[REF] = '@',
	[EXPR_END] = ';',
	[OBJ_BEGIN_ASCII] = '{',
	[OBJ_END_ASCII] = '}',
	[OBJ_REF_BEGIN_ASCII] = '[',
	[OBJ_REF_END_ASCII] = ']',
	[STRING] = '"',
	[COMMENT] = '%',
	[GEN_ESC] '\\'
};
#endif

#ifndef LOCK_TOKEN_MANIFEST
#  define LOCK_TOKEN_MANIFEST

#  include "../utils/sharedtypes.h"

static const unsigned int Keyword_manifest_len =
	sizeof (Keyword_manifest) / sizeof (*Keyword_manifest);
static const unsigned int Token_manifest_len =
	sizeof (Token_manifest) / sizeof (*Token_manifest);
#endif
