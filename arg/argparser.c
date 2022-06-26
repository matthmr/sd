/*
 *
 * @file argparser.c
 *
 * @brief common argument parser implementation
 *
 * This file contains a common argparsing
 * interface for programs that receive
 * CLI arguments
 */

#include "argparser.h"

/// @brief main argument parser
/// @parem cargc caller provided `argc`
/// @parem cargv caller provided `argv`
arg parseargs (int cargc, char** cargv) {

	caller_setup ();

	ok: return ARG_OK;
}
