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

#  include <sd/utils/utils.h>

// SD operators
enum op {

	OP_NULL=-1,    // PLACEHOLDER

	//  -- math -- //
	OP_MATHPLUS,   // '+'
	OP_MATHMINUS,  // '-'
	OP_MATHDIV,    // '//'
	OP_MATHTIMES,  // '*'
	OP_MATHMOD,    // '%'

	//  -- unary math -- //
	OP_UMATHPLUS,  // '+'
	OP_UMATHMINUS, // '-'
	OP_UMATHINC,   // '++'
	OP_UMATHDEC,   // '--'

	// -- bool -- //
	OP_LOGAND,     // '&&'
	OP_LOGOR,      // '||'
	OP_LOGNOT,     // '!'
	OP_LOGGT,      // '>'
	OP_LOGLT,      // '<'
	OP_LOGEQ,      // '='
	OP_LOGNEQ,     // '!='
	OP_LOGLTEQ,    // '<='
	OP_LOGGTEQ,    // '>='

	// -- bitwise -- //
	OP_BITWAND,    // '&'
	OP_BITWOR,     // '|'
	OP_BITWXOR,    // '^'
	OP_BITWNOT,    // '~'
	OP_BITWRS,     // '>>'
	OP_BITWLS,     // '<<'
	
	// -- mem -- //
	OP_MEMCALL,    // '(' and ')'
	OP_MEMCAST,    // '.'
	OP_MEMCHILD,   // '/'
	OP_MEMASS,     // ':'
	OP_SEMMUB,     // '<' and '>'
	OP_MEMSEP,     // ','

	// -- flow -- //
	OP_FLOWEXPR,   // '?'
	OP_FLOWLOOP,   // '!'
	
	// -- macro -- //
	OP_MACCONST,   // '$$'
	OP_MACFUNC,    // '$()'
	OP_MACLITSYN,  // '$<' and '>$'

	// -- syntax sugar -- //
	OP_FAUX,       // '$'
	OP_CAST,       // '%%'

};

typedef enum op Op;

// bit size + bit interpretation
//   * distinguish `int` from `char` on
//     size only, not on interpretation
enum bits {

	// 8 bits
	bits_8,

	// 16 bits
	bits_16,

	// 32 bits
	bits_32,
	bits_32f,  // intr<float>
	#if ADDR_BITS == 32
	bits_addr, // intr<addr>
	#endif

	bits_64,
	bits_64f,  // intr<double>
	#if ADDR_BITS == 64
	bits_addr, // intr<addr>
	#endif
};

enum qual {
	qual_const = BIT (1),
	qual_signed = BIT (2), // toggle : <signed,unsigned>
	qual_static = BIT (3),
	qual_here = BIT (4),
	qual_scope = BIT (5),
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
