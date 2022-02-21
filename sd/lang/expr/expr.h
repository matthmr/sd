/**
 * This files contains utils
 * for making the parse tree
 * for plain-text files
 */

#ifndef LOCK_EXPR
#  define LOCK_EXPR

#  include <sd/utils/types/shared.h>

// -- CPU-like -- //
//  -- math-like -- //
#  define OP_PLUS 0x0000
#  define OP_MINUS 0x0001
#  define OP_DIV 0x0002
#  define OP_TIMES 0x0003
#  define OP_MOD 0x0004

//  -- unary math -- //
#  define OP_UMINUS 0x0005
#  define OP_UPLUS 0x0006

#  define OP_LAND 0x0007
#  define OP_LOR 0x0008
#  define OP_LNOT 0x0009
#  define OP_LGT 0x000a
#  define OP_LLT 0x000b
#  define OP_LEQ 0x000c

#  define OP_BWAND 0x000d
#  define OP_BWOR 0x000e
#  define OP_BWXOR 0x000f
#  define OP_BWNOT 0x0010

#  define OP_BWRS 0x0010
#  define OP_BWLS 0x0011

// -- object-like -- //
#  define OP_CALL 0x0012
#  define OP_CAST 0x0013
#  define OP_CHILD 0x0014

// -- literal -- //
#  define OP_LITERAL 0x0015
#  define OP_DRIVE 0x0016

typedef byte op;

enum sync {
	SYNC_OBJ,
	SYNC_PROC,
};

enum len {
	BYTES_a8,
	BYTES_a16,
	BYTES_a32,
	BYTES_b32,
	BYTES_a64,
	BYTES_ADDR,
	BYTES_ENUM,
	BYTES_MAP,
};

enum qual {
	QUAL_CONST,
	QUAL_UNSIGNED,
	QUAL_STATIC,
};

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
#endif
