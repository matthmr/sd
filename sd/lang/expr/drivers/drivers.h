/**
 * This file contains
 * expression drivers
 */

#ifndef LOCK_DRIVERS
#  define LOCK_DRIVERS

#  include <sd/lang/expr/expr.h>

enum drivers_manifest {
	DRIVER_DRIVE=1,
	DRIVER_NULL,

	DRIVER_UWORD,
	DRIVER_UWORDL,
	DRIVER_LITERAL,
	DRIVER_CALL,
	DRIVER_KEYWORD_IMEDDIATE, // jump, ret, sync, ...

	DRIVER_LET,
	DRIVER_PROC,

	DRIVER_EXPR,
	DRIVER_SYNC,
	DRIVER_ITER,
	DRIVER_BRANCH,

	DRIVER_EXPR2,
	DRIVER_EXPR1,
};

struct driver {
	enum drivers_manifest manifest;

	bits attr_bits;
	qual attr_qual;
};

typedef struct driver Driver;

#endif
