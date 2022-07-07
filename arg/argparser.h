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
#  define __as_char__(x,i,y,z,w,c) \
{ \
	._ = { \
		.as_char = x, \
	}, \
	.common = { \
		.id = i, \
		.action = y, \
		.am = z, \
		.sep = w, \
		.comp = (CompSizeManifest*)c, \
	}, \
}
#  define __as_string__(x,i,y,z,w,c) \
{ \
	._ = { \
		.as_string = x, \
	}, \
	.common = { \
		.id = i, \
		.action = y, \
		.am = z, \
		.sep = w, \
		.comp = c, \
	}\
}
#  define __as_comp__(x,y,i,z,w) \
{ \
	.flag = { \
		._ = { \
			.as_string = x, \
		}, \
		.common = { \
			.id = i, \
			.action = ACTION_NULL, \
			.am = w, \
			.sep = w, \
			.comp = NULL , \
		}\
	}, \
	.alt = y, \
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
	                     ///< (the main interface)
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
	const char *alt; // generally negation, as in ('X', 'noX')
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

typedef Astatus (*Default) (char*),
                (*SingleDash) (char*),
                (*DoubleDash) (char*);

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

/// @brief default arg callback interface
struct arg_callback {
	FlagAmount am;
	Flag *flag;
};

typedef struct arg_callback ArgCallback;

/// @brief `argparser.c` callback
extern ArgCallback CALLBACK[2];

// `parseargs` internal exit status
#  define NOTFOUND '\0'
#  define FOUND '\1'
#  define ARGMORE '\2'

Astatus promise (const Flag*, char*);
Astatus parseargs (const char*, char*);
Astatus check (void);

#endif
