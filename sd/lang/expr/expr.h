/**
 * This file contains utils
 * for making a generic
 * parse tree on demand
 */

#ifndef LOCK_EXPR
#  define LOCK_EXPR

#  define LOCK_VM
#  include <sd/utils/types/shared.h>
#  include <sd/lang/vm/vm.h>
#  undef LOCK_VM

//  -- math -- //
#  define OP_PLUS 0x00
#  define OP_MINUS 0x01
#  define OP_DIV 0x02
#  define OP_TIMES 0x03
#  define OP_MOD 0x04

//  -- unary math -- //
#  define OP_UMINUS 0x05
#  define OP_UPLUS 0x06
#  define OP_INC 0x07
#  define OP_DEC 0x08

// -- bool -- //
#  define OP_LAND 0x09
#  define OP_LOR 0x0a
#  define OP_LNOT 0x0b
#  define OP_LGT 0x0c
#  define OP_LLT 0x0d
#  define OP_LEQ 0x0e
#  define OP_LNEQ 0x0f
#  define OP_LLTEQ 0x10
#  define OP_LGTEQ 0x11

// -- bitwise -- //
#  define OP_BWAND 0x12
#  define OP_BWOR 0x13
#  define OP_BWXOR 0x14
#  define OP_BWNOT 0x15
#  define OP_BWRS 0x16
#  define OP_BWLS 0x17

// -- mem -- //
#  define OP_MCALL 0x18
#  define OP_MCAST 0x19
#  define OP_MCHILD 0x1a
#  define OP_MASS 0x1b
#  define OP_MSUB 0x1c
#  define OP_MSEP 0x1d

// -- literal -- //
#  define OP_DRIVE 0x1e // aka `OP_SELF`: resolutes expressions
#  define OP_LITERAL 0x1f

typedef byte Op;

enum bits {
	bits_8c = 8, // char

	bits_16i = 16, // short

	bits_32i = 32, // int
	bits_32f = 33, // float
	bits_enum = 34, // int
	bits_map = 35, // int

	bits_64l = 64, // long
	bits_64d = 65, // double

	#if ADDR_BITS == 64
	bits_addr = 66, // void*
	#else
	bits_addr = 36, // void*
	#endif

};

enum qual {
	qual_def,
	qual_const,
	qual_unsigned,
	qual_static,
	qual_long,
	qual_short,
};

typedef enum bits bits;
typedef enum qual qual;

#endif

#ifndef LOCK_EXPRFN
#  define LOCK_EXPRFN
struct expr {
	addr e1; /* heap/stack (l) or tab/register (e) */
	addr e2; /* heap/stack (l) or tab/register (e) */
	u32 op;
	// u8 ty;
};

void expr_exec (void);
#endif
