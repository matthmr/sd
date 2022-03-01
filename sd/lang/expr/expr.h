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

// -- bool -- //
#  define OP_LAND 0x07
#  define OP_LOR 0x08
#  define OP_LNOT 0x09
#  define OP_LGT 0x0a
#  define OP_LLT 0x0b
#  define OP_LEQ 0x0c

// -- bitwise -- //
#  define OP_BWAND 0x0d
#  define OP_BWOR 0x0e
#  define OP_BWXOR 0x0f
#  define OP_BWNOT 0x10
#  define OP_BWRS 0x10
#  define OP_BWLS 0x11

// -- mem -- //
#  define OP_CALL 0x12
#  define OP_CAST 0x13
#  define OP_CHILD 0x14

// -- literal -- //
#  define OP_LITERAL 0x15
#  define OP_DRIVE 0x16 // aka `OP_SELF`: resolutes expressions

typedef byte op;

enum sync {
	SYNC_OBJ,
	SYNC_PROC,
};

enum bits {
	bits_8c = 8, // char

	bits_16i = 16, // short

	bits_32i = 32, // int
	bits_32f = 33, // float
	bits_enum = 34, // int
	bits_map = 35, // int

	bits_64l = 64, // long
	bits_64d = 65, // double

	#if ADDR_BITS == 32
		bits_addr = 36, // void*
	#elif ADDR_BITS == 64
		bits_addr = 66, // void*
	#endif

};

enum qual {
	QUAL_CONST,
	QUAL_UNSIGNED,
	QUAL_STATIC,
};

typedef enum bits bits;
typedef enum qual qual;

#  ifndef LOCK_EXPRFN
#    define LOCK_EXPRFN
struct expr {
	addr e1; // heap
	addr e2; // heap
	u32 op;
	u8 ty;
};

typedef struct expr Expr;

extern Expr g_expr;

void expr_add64 (u64);
void expr_add32 (u32);
void expr_add16 (u16);
void expr_add8 (u8);

void expr_expect (enum sync);
void expr_exec (void);
#  endif

#endif
