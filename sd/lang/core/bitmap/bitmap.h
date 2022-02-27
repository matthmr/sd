/**
 * This file contains definitions
 * for bitmaps of SD bytecode:
 *  >  NORMAL BYTE
 *  >  TYPE BYTE
 */

#ifndef LOCK_BITMAP
#  define LOCK_BITMAP

typedef unsigned char bit;

struct SDO_normal_mask {
	bit big: 1;
	bit ty: 2;
	bit mod: 1;
	bit ogid: 4;
};

struct SDO_type_mask {
	bit sign: 1;
	bit bits_addr: 1;
	bit bits_float: 1;
	bit bits_undef: 1;
	bit bits_64: 1;
	bit bits_32: 1;
	bit bits_16: 1;
	bit bits_8: 1;
};

#  define NORMAL (struct SDO_normal_mask)
#  define TYPE (struct SDO_type_mask)

#  endif
