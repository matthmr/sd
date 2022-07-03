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

// manifest macros
#  define __as_char__(x,y,z,w) \
{ \
	._ = { \
		.as_char = x, \
	}, \
	.common = { \
		.action = y, \
		.am = z, \
		.sep = w, \
	}\
}
#  define __as_string__(x,y,z,w) \
{ \
	._ = { \
		.as_string = x, \
	}, \
	.common = { \
		.action = y, \
		.am = z, \
		.sep = w, \
	}\
}

#  define SINGLE(...) \
	.flag_single = {\
		.this = __VA_ARGS__, \
		.len = (__bytes__ (__VA_ARGS__)) - 1\
	}
#  define DOUBLE(...) \
	.flag_double = {\
		.this = __VA_ARGS__, \
		.len = (__bytes__ (__VA_ARGS__)) - 1\
	}

#  define DEFINE '='

/// @brief arg parser exit status
enum astatus {
	ARG_ERR = -1, ///< @brief default error; kill the program; may display a generic error message
	ARG_OK = 0, ///< @brief default success; enter the main loop
	ARG_INFO, ///< @brief dry run; skip main loop
	ARG_VERR, ///< @brief parser error; specify what kind of error; kill the program
};

typedef enum astatus Astatus;

// TODO: some arguments may literally compound like `sd -si file.sd',
//       only `flag_single' compound
/// @brief arg flag amount bit field
enum flag_amount {
	NONE = BIT (0), ///< @brief placeholder
	ONE = BIT (1), ///< @brief one value
	MUL = BIT (2), ///< @brief multiple values
	VAL = BIT (3), ///< @brief `sep`-separated value(s)
	COMP = BIT (4), ///< @brief `comp`-compound value(s)
};

typedef enum flag_amount FlagAmount;

/// @brief common arg parsing struct
/// The flag layout assumes a couple things:
///   - `Flag::sid` will always have one character
///   - `Flag::comp` will always be single-dashed
struct flag_common {
	const int action; ///< @brief flag action; promotes to enum
	const FlagAmount am; ///< @brief flag value amount
	const char sep; ///< @brief value separator; left empty assumes that the value
	                /// is on another var; it uses implicit promises
};

typedef struct flag_common FlagCommon;

// TODO: implement this
typedef char FlagComp;

// `struct flag`
union _flag {
	const char as_char;
	const char *as_string;
};

struct flag {
	const union _flag _;
	const FlagCommon common;
};

typedef struct flag Flag;

struct size_manifest {
	const Flag *this;
	const uint len;
};

typedef struct size_manifest SizeManifest;

/// @brief flag manifest interface
struct flag_manifest {

	// as single char
	const SizeManifest flag_single; ///< @note this flag can compound IF AND ONLY IF
	                                ///< it has no value being passed into it
	const SizeManifest flag_comp;

	// as string
	const SizeManifest flag_double;
	const SizeManifest flag_singlelong;
};

typedef struct flag_manifest FlagManifest;

// edge-case handlers
typedef Astatus (*Default) (char*, char**),
                (*SingleDash) (char*, char**),
                (*DoubleDash) (char*, char**);

typedef Default FlagAction;

// flag manifests
extern const FlagManifest flag_manifest;

// action manifests
extern const FlagAction flagaction_manifest[];

extern const Default defarg;
extern const SingleDash sdash;
extern const DoubleDash ddash;

// `parseargs` internal exit status
#  define NOTFOUND '\0'
#  define FOUND '\1'

Astatus promise (void);
Astatus parseargs (const char*, char*, char**);

#endif
