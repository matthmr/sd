/**
 * @file txthooks.h
 *
 * @brief text hook interface
 *
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#ifndef LOCK_AHOOKS
#  define LOCK_AHOOKS

#include <sd/lang/tokens/groups.h>

#include <sd/intr/txt/tokens/form.h>

#include "utils/types/shared.h"

/// @brief fields `cmt`, `str`, `literal`, `exepect_compound` &
///        `exepect_match` are part of a bitfield padded by `__PAD`
struct stream_ctxt {

	bool cmt: 1;
	bool str: 1;
	bool literal: 1;
	bool expect_compound: 1;
	bool expect_match: 1;
	bool __PAD: 3;

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
