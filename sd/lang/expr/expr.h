/**
 * @file expr.h
 *
 * @brief stack-based & general expressions source
 *
 * This file contains utils
 * for making a generic
 * parse tree on demand
 */

#ifndef LOCK_EXPR
#  define LOCK_EXPR ///< lock: lock operators and bit qualification

#  define LOCK_VM
#  include <sd/utils/types/shared.h>
#  include <sd/lang/vm/vm.h>
#  undef LOCK_VM

#  include <sd/utils/utils.h>

/// @brief SD operators
enum op {

	OP_NULL=-1,    ///< PLACEHOLDER

	// -- math -- //
	OP_MATHPLUS,   ///< such as: '+'
	OP_MATHMINUS,  ///< such as: '-'
	OP_MATHDIV,    ///< such as: '//'
	OP_MATHTIMES,  ///< such as: '*'
	OP_MATHMOD,    ///< such as: '%%'

	// -- unary math -- //
	OP_UMATHPLUS,  ///< such as: '+a'
	OP_UMATHMINUS, ///< such as: '-a'
	OP_UMATHINC,   ///< such as: '++' (postfix only)
	OP_UMATHDEC,   ///< such as: '--' (postfix only)

	// -- bool -- //
	OP_LOGAND,     ///< such as: '&&'
	OP_LOGOR,      ///< such as: '||'
	OP_LOGNOT,     ///< such as: '!'
	OP_LOGGT,      ///< such as: '>'
	OP_LOGLT,      ///< such as: '<'
	OP_LOGEQ,      ///< such as: '='
	OP_LOGNEQ,     ///< such as: '!='
	OP_LOGLTEQ,    ///< such as: '<='
	OP_LOGGTEQ,    ///< such as: '>='

	// -- bitwise -- //
	OP_BITWAND,    ///< such as: '&'
	OP_BITWOR,     ///< such as: '|'
	OP_BITWXOR,    ///< such as: '^^'
	OP_BITWNOT,    ///< such as: '~'
	OP_BITWRS,     ///< such as: '>>'
	OP_BITWLS,     ///< such as: '<<'
	
	// -- mem -- //
	OP_MEMCALL,    ///< such as: '()'
	OP_MEMCAST,    ///< such as: '.'
	OP_MEMCHILD,   ///< such as: '/'
	OP_MEMPIPE,    ///< such as: '%'
	OP_MEMASS,     ///< such as: ':'
	OP_MEMARR,     ///< such as: '<>'
	OP_MEMSEP,     ///< such as: ','

	// -- flow -- //
	OP_FLOWEXPR,   ///< such as: '?'
	OP_FLOWLOOP,   ///< such as: '!'
	
	// -- macro -- //
	OP_MACCONST,   ///< such as: '$$'
	OP_MACFUNC,    ///< such as: '$()'
	OP_MACLITSYN,  ///< such as: '$<>$'

	// -- syntax sugar -- //
	OP_FAUX,       ///< such as: '$'

};

typedef enum op Op;

/// @brief bit size + bit interpretation
/// distinguish `int` from `char` on
/// size only, not on interpretation
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

/// @brief data qualifier
enum qual {
	qual_const = BIT (1),  ///< toggle: const, mut
	qual_signed = BIT (2), ///< toggle: signed, unsigned (int-like only)
	qual_static = BIT (3), ///< toggle: static, auto
	qual_here = BIT (4),   ///< toggle: local, global (module-wise)
	qual_scope = BIT (5),  ///< toggle: local, global (object-wise)
};

typedef enum bits bits;
typedef enum qual qual;

#endif

#ifndef LOCK_EXPRFN
#  define LOCK_EXPRFN ///< lock: lock stack expression structure
struct expr {
	addr e1; /* heap/stack (l) or tab/register (e) */
	addr e2; /* heap/stack (l) or tab/register (e) */
	u32 op;
	// u8 ty;
};

void expr_exec (void);
#endif
