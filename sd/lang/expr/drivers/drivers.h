/**
 * This file contains
 * expression drivers
 */

#ifndef LOCK_DRIVERS
#  define LOCK_DRIVERS

#  include <sd/lang/expr/expr.h>

// TODO: what in the fuck is this supposed to represent?
enum drivers_manifest {

	DRIVER_NULL=-1,

	DRIVER_UWORD,    // u: user
	DRIVER_UWORDF,   // uword faux: enum names, branch names
	DRIVER_UWORDT,   // uword template: type names
	DRIVER_MACRO,
	DRIVER_LITERAL,
	DRIVER_CALL,
	DRIVER_KW_IMM,   // jump, ret, end, sync, sync, 

	DRIVER_IMPL,

	DRIVER_LET,      // inherit
	DRIVER_PROC,     // inherit
	DRIVER_RM,
	DRIVER_TYPE,
	DRIVER_TAG,

	DRIVER_EXPR,
	DRIVER_SYNC,
	DRIVER_ITER,
	DRIVER_BRANCH,
	DRIVER_TAB,
	DRIVER_UNARY,

};

typedef enum drivers_manifest manifest;

// `struct driver.tag`
enum tag {
	AS_POINTER,
	AS_INLINE,
};

// `struct driver`
//    - driver.attr_bits tags this union
union drivee {
	d_addr as64;
	d_addrl as32;
	float as32f;
	double as64f;
};

typedef union drivee drivee;
typedef enum tag tag;

struct driver {
	manifest manifest;
	drivee drivee;

	bits attr_bits; // bit length
	qual attr_qual; // storage class

	tag tag; // tag for `driver.drivee`
};

typedef struct driver Driver;

manifest map_to_driver (int);

#endif
