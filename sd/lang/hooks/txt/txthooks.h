/**
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#define LOCK_LANG_OBJ

#include <sd/utils/types/shared.h>
#include <sd/lang/lang.h>

#ifndef LOCK_AHOOKS
#  define LOCK_AHOOKS

#  undef LOCK_HOOKS
#  define LOCK_PARSER_CALLBACK

#  include <sd/lang/hooks/hooks.h>

#  undef LOCK_HOOKS
#  undef LOCK_PARSER_CALLBACK

extern struct stream_ctxt gs_ctxt;
extern struct runtime_ctxt gr_ctxt;
extern bool lock_stream;

#  define lstream(X) (X); H_LOCK (lock_stream)
#  define rstream(X) (X); H_RESET (lock_stream)

typedef void (*_at_handler)(txt_T);
typedef void (*_akw_handler)(txt_Kw);

extern _at_handler at_handler[];
extern _akw_handler akw_handler[];

#  define at_hook(x) (*at_handler[x.ty]) (x)
#  define akw_hook(x) (*akw_handler[x.ty]) (x)

#endif
