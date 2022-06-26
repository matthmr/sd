/*
 *
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

#  define MADEBY(x,y) "\nMade by " x " (" y ")\n"
#  define DESCRIPTION(x) x "\n"

enum arg {
	ARG_ERR = -1, //< @brief default error; kill the program
	ARG_OK = 0, //< @brief default success; enter the main loop
	ARG_INFO, //< @brief dry run; skip main loop
};

typedef enum arg arg;

struct flag_common {
	char sid;
	char[] did;
};

typedef struct flag_common common;

struct flag_value {
	common _;
};

struct flag_it {
	common _;
};

struct inc_flag {
	common _;
};

/// @brief flag action interface
/// this struct has only one field
/// that is a function that takes no
/// arguments and returns an arg
/// status. to pass in arguments, use
/// a static local variable
struct flag_action {
	arg (*_) (void);
};

typedef struct flag_value FlagVal;
typedef struct flag_it FlagIt;
typedef struct inc_flag IncFlag;
typedef struct flag_action FlagAction;

#endif
