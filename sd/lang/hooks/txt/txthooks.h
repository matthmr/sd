/**
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#ifndef LOCK_AHOOKS
#  define LOCK_AHOOKS

#include <sd/utils/types/shared.h>
#include <sd/lang/lang.h>

struct stream_ctxt {
	bool cmt: 1;
	bool str: 1;
	bool literal: 1;
	bool expect_compound: 1;
	bool __PAD: 4;

	uint base;
};

extern struct stream_ctxt gs_ctxt;

extern bool lock_stream;

#  define lstream(X) (X); H_LOCK (lock_stream)
#  define rstream(X) (X); H_RESET (lock_stream)

typedef void (*_at_handler)(_T);
typedef void (*_akw_handler)(_Kw);

extern const _at_handler at_handler[];
extern const _akw_handler akw_handler[];

#  define at_hook(x) at_handler[x.ty] (x)
#  define akw_hook(x) akw_handler[x.ty] (x)

#endif
