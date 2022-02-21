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

struct resolve_ctxt {
	bool on_call: 1;
	bool on_precedence: 1;
	bool on_definition: 1;
	bool __PAD: 5;
};

struct mem_ctxt {
	bool assign: 1;
	bool assign_arg: 1;
	bool assign_proto: 1;
	bool __PAD: 5;
};

struct data_type {
	bool _int: 1;
	bool _float: 1;
	bool _char: 1;
	bool _long: 1;
	bool _short: 1;
	bool _array: 1;
	bool _sign: 1;
	bool __PAD: 1;
};

struct stream_ctxt {
	bool cmt: 1;
	bool str: 1;
	bool literal: 1;
	bool expect_double: 1;
	bool __PAD: 4;

	uint base;
};

extern struct stream_ctxt gs_ctxt;
extern bool lock_stream;

static struct mem_ctxt new_mem_ctxt (void);
static struct data_type new_data_ctxt (void);

#  define lstream(X) (X); H_LOCK (lock_stream)
#  define rstream(X) (X); H_RESET (lock_stream)

typedef void (*_at_handler)(_T);
typedef void (*_akw_handler)(_Kw);

extern _at_handler at_handler[];
extern _akw_handler akw_handler[];

#  define at_hook(x) (*at_handler[x.ty]) (x)
#  define akw_hook(x) (*akw_handler[x.ty]) (x)

#endif
