/**
 * This file contains the
 * definitions for built-in
 * object hooks
 */

#include <sd/utils/types/shared.h>
#include <sd/lang/core/obj.h>
#include <sd/lang/lang.h>

#ifndef LOCK_AHOOKS
#  define LOCK_AHOOKS

// -- `g_ctxt.str` values -- //
#  define DQSTR 1
#  define SQSTR 2

struct _ctxt {
	/* comment */
	bool cmtl;
	bool cmtb;

	/* string */
	bool str;

	bool expr;
	bool uobj;
};

typedef struct _ctxt Ctxt;
extern Ctxt g_ctxt;

/* this locks the character stream
 * defined in `stream_parse` for
 * things like comments, multiline
 * comments and strings */
extern bool lock_stream;

#  define sstream(X)  (X); H_LOCK (lock_stream)
#  define cstream(X)  (X); H_RESET (lock_stream)

bool ct_close (uint*, char*);
bool s_ignore (uint*, uint, char*);

typedef void (*_at_handler)(_T);
typedef void (*_akw_handler)(_Kw);

extern _at_handler at_handler[];
extern _akw_handler akw_handler[];

void callback (void);

#  define at_hook(X) (*at_handler[X.ty]) (X)
#  define akw_hook(X) (*akw_handler[X.ty]) (X)

#endif

#ifndef LOCK_BHOOKS
#  define LOCK_BHOOKS

/// TODO: bytecode hooks
/// void bkw_hook (_bT);
/// void bt_hook (_bKw);
/// void bu_hook (void);

#endif
