/**
 * This file contains all the internal logic
 * and syntax for the sd language. It is
 * format-agnostic, which means that this
 * source is included into different parsers
 * for their respective formats
 * (binary or plain-text)
 */

#ifndef LOCK_LANG
#  define LOCK_LANG

#  include "langutils.h"

void* resolute_obj (Obj);

#endif
