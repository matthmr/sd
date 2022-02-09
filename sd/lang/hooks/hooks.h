/**
 * This file contains format
 * agnostic hooks */

#ifndef LOCK_HOOKS
#  define LOCK_HOOKS

struct object_ctxt {
	bool tabdef_let: 1;
	bool tabdef_proc: 1;
	bool tabdef_type: 1;
	bool tabdef: 1;
	bool PADDING: 4;
};

struct runtime_ctxt {
	struct object_ctxt obj;
	bool obj_call;
	bool obj_tabdef;
};

struct stream_ctxt {
	bool cmt;
	bool str;
};

#endif

#ifndef LOCK_PARSER_CALLBACK
#  define LOCK_PARSER_CALLBACK

void newline (void); /* TODO: that should take a global context variable */

#endif
