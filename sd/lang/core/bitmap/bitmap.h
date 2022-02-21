/**
 * This file contains definitions
 * for bitmaps of SD bytecode:
 *  >  NORMAL BYTE
 *  >  TYPE BYTE
 */

#ifndef LOCK_BITMAP
#  define LOCK_BITMAP

typedef char bit;

struct sd_byte_normal {
	bit big: 1;
	bit ty: 2;
	bit ogid: 5;
};

struct sd_byte_type {
	bit sign: 1;
	bit bits_addr: 1;
	bit bits_float: 1;
	bit bits_undef: 1;
	bit bits_64: 1;
	bit bits_32: 1;
	bit bits_16: 1;
	bit bits_8: 1;
};

typedef struct sd_byte_normal Normal;
typedef struct sd_byte_type Type;

#  define NORMAL (Normal)
#  define TYPE (Type)

#ifndef LOCK_BITMAP
