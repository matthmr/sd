/**
 * @file autils.h
 *
 * @brief argument parsing utils
 *
 * This file contains utils for
 * common argparsing
 */

#ifndef LOCK_ARGUTILS
#  define LOCK_ARGUTILS

#  include "utils/verbose/colors.h"
#  include "utils/types/shared.h"
#  include "utils/err/err.h"

// help message macros
#  define MADEBY(x,y) "\nMade by " x " (" y ")\n"
#  define DESCRIPTION(x,y) "\t" x " => " y "\n"

#  define FLAG_VAL(n,x,y,z,w) "\t" n " [--" x ", -" y "] " z " => " w "\n"
#  define FLAG_NOVAL(n,x,y,z) "\t" n " [--" x ", -" y "] => " z "\n"

#  define USAGE(x) "\nUsage:\n" x
#  define MORE(x) "\nInfo:\n\tRead more at " x "\n\n"

// manifest utils
#  define __bytes__(t,...) (sizeof (__VA_ARGS__)) / (sizeof (t))
#  define BLOCK_SIZE 4

#endif
