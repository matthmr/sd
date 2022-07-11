/*
 * @file argparser.h
 *
 * @brief common argument parser implementation
 *
 * This file contains a common argparsing
 * interface for programs that receive
 * CLI arguments
 */

#ifndef LOCK_ARGPARSER
#  define LOCK_ARGPARSER

#  include "utils/types/shared.h"
#  include "utils/macros.h"
#  include "arg/autils.h"

// manifest item macros
#  define __as_char__(_as_char,_id,_action,_am,_sep,_comp) \
{ \
	._ = { \
		.as_char = _as_char, \
	}, \
	.common = { \
		.id = _id, \
		.action = _action, \
		.am = _am, \
		.sep = _sep, \
		.comp = (CompSizeManifest*)_comp, \
	}, \
}
#  define __as_string__(_as_string,_id,_action,_am,_sep,_comp) \
{ \
	._ = { \
		.as_string = _as_string, \
	}, \
	.common = { \
		.id = _id, \
		.action = _action, \
		.am = _am, \
		.sep = _sep, \
		.comp = (CompSizeManifest*)_comp, \
	}, \
}
#  define __as_comp__(_as_string,_alt,_id,_am,_sep) \
{ \
	.flag = { \
		._ = { \
			.as_string = _as_string, \
		}, \
		.common = { \
			.id = _id, \
			.action = ACTION_NULL, \
			.am = _am, \
			.sep = _sep, \
			.comp = NULL , \
		}\
	}, \
	.alt = _alt, \
}

// manifest definitions macros
#  define SINGLE(...) \
	.flag_single = { \
		.this = __VA_ARGS__, \
		.len = (__bytes__ (Flag, __VA_ARGS__)) - 1\
	}
#  define DOUBLE(...) \
	.flag_double = { \
		.this = __VA_ARGS__, \
		.len = (__bytes__ (Flag, __VA_ARGS__)) - 1\
	}
#  define COMPFLAG(x,y,...) \
	static const CompSizeManifest x = { \
		.this = __VA_ARGS__, \
		.action = y, \
		.len = (__bytes__ (FlagComp, __VA_ARGS__)) - 1, \
	}

#  define DEFINE '=' ///< @brief default argument define token
#  define SEP ',' ///< @brief default argument separator token
#  define ACTION_NULL -1

/// @brief arg parser exit status
enum astatus {
	ARG_ERR = -1, ///< @brief default error; kill the program; may display a generic error message
	ARG_OK = 0, ///< @brief default success; enter the main loop
	ARG_INFO, ///< @brief dry run; skip main loop
	ARG_VERR, ///< @brief parser error; specify what kind of error; kill the program
	ARG_MORE, ///< @brief disambiguate argument; seek next character
};

typedef enum astatus Astatus;

/// @brief arg flag amount bit field
/// @note `NONE`-type flags *will always* be compoundable
/// with *any* other type of flag; the opposite is not true
enum flag_amount {
	NONE = BIT (0), ///< @brief placeholder
	ONE = BIT (1), ///< @brief one value [-a bcd]
	MUL = BIT (2), ///< @brief multiple values [--abcd efgh]
	VAL = BIT (3), ///< @brief `sep`-separated value(s) [-a=b]
	COMP = BIT (4), ///< @brief `comp`-compound value(s) [-ab=c]
	COMPDEF = BIT (5), ///< @brief user defined `comp`-compound value(s) [-aBC]
	NOCOMP = BIT (6), ///< @brief internal use: used to mask the compound manifest
};

typedef enum flag_amount FlagAmount;

/// @brief common arg parsing struct
struct flag_common {
	const int id;        ///< @brief flag id; promotes to enum
	const int action;    ///< @brief flag action; promotes to enum
	const FlagAmount am; ///< @brief flag value amount
	const char sep;      ///< @brief value separator; left empty assumes that the value
	                     ///< is on another var; it uses implicit promises
	const void *comp;    ///< @brief common flag compound; left to type cast set by
	                     ///< `FlagCommon::am == COMP` to `CompSizeManifest`
};

typedef struct flag_common FlagCommon;

// `struct flag`
union _flag {
	const char as_char;
	const char *as_string;
};

typedef union _flag FlagData;

/// @brief common flag interface
struct flag {
	const FlagData _;
	const FlagCommon common;
};

typedef struct flag Flag;

// `struct flag_manifest`
struct size_manifest {
	const Flag *this; // manifest
	const uint len;
};

typedef struct size_manifest SizeManifest;

/// @brief default flag manifest interface,
/// it serves as a labeled array as each field
/// has a pointer to a manifest of its type,
/// it is separates by *dash* type as a flag
///
/// @note @p flag_single can compound both
/// compound single and long single, the
/// latter having the first letter missing
struct flag_manifest {
	const SizeManifest flag_single;
	const SizeManifest flag_double;
};

// compound cast
// `struct size_manifest_single_comp`
struct flag_comp {
	const Flag flag; // manifest element
	const char *alt; // generally negation, as in ('X', 'X-disable')
};

typedef struct flag_comp FlagComp;

// `struct flag_single`
struct comp_size_manifest {
	const FlagComp *this; // manifest
	const int action; // local handler
	const uint len;
};

typedef struct comp_size_manifest CompSizeManifest;

typedef struct flag_manifest FlagManifest;

typedef Astatus (*Default) (int, char*),
                (*SingleDash) (int, char*),
                (*DoubleDash) (int, char*);

typedef Default FlagAction;

// edge-case handlers
extern const Default defarg; // *
extern const SingleDash sdash; // -*
extern const DoubleDash ddash; // --*

// flag manifests
extern const FlagManifest flag_manifest; ///< @brief flag manifest; some implementations
                                         ///< may be caller static

// action manifests
extern const FlagAction flagaction_manifest[]; ///< @brief flag action manifest

extern uint stroffset;  ///< @brief iteration offset WITH RESPECT TO
                        ///< manifest items
extern const char *ARG; ///< @brief the original argument; arguments
                        ///< will get truncated as it iterates

// `ffind` return value
enum parseargs_status {
	NOTFOUND = 0,
	FOUND,
	DISAMSTR,
	DISAMCOMP,
};

typedef enum parseargs_status FFstatus; // ffind -> parse
typedef char FBstatus; // fbound -> ffind

Astatus promise (const Flag*, char*);
Astatus parseargs (const char*, char*);
Astatus check (void);

#endif
