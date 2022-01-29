/**
 * This file contains the
 * definitions for built-in
 * object hooks found in plain-
 * text form
 */

#include <sd/utils/types/shared.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#ifndef LOCK_AHOOKS
#  define LOCK_AHOOKS


struct txt_ctxt {
	bool cmt;
	bool str;
};

typedef struct txt_ctxt txt_Ctxt;

extern txt_Ctxt g_ctxt;
extern bool lock_stream;

#  define lstream(X) (X); H_LOCK (lock_stream)
#  define rstream(X) (X); H_RESET (lock_stream)

typedef void (*_at_handler)(_T);
typedef void (*_akw_handler)(_Kw);

extern _at_handler at_handler[];
extern _akw_handler akw_handler[];

void au_hook (char*);

#  define at_hook(x) (*at_handler[x.ty]) (x)
#  define akw_hook(x) (*akw_handler[x.ty]) (x)

#endif
