/**
 * This file contains virtual
 * tokens: tokens that can be
 * infered or constructed,
 */

#ifndef LOCK_VIRTUAL
#  define LOCK_VIRTUAL

// `struct _vt` ignores `MATCH_OPEN`, `MATCH_CLOSE`, `PREFIX`, `INFIX` & `SUFFIX`
typedef struct _vt {
	unsigned short compound;
	unsigned short mask;
} _vT;

extern const _vT vtoken_manifest[];

#endif
