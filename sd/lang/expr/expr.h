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

#  include <sd/utils/macros.h>

// TODO: make `op` also have AST operations
//       (function argument, function body, ...)
/// @brief SDVM operators
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
	OP_FLOWLOOP,   ///< such as: '??'
	
	// -- macro -- //
	OP_MACCONST,   ///< such as: '$$'
	OP_MACFUNC,    ///< such as: '$()'
	OP_MACLITSYN,  ///< such as: '$<>$'

	// -- syntax sugar -- //
	OP_FAUX,       ///< such as: '$'

};

typedef enum op Op;

/// @brief bit size + bit interpretation
enum bits {
	bits_8,
	bits_16,
	bits_32,
	bits_64,

	bits_addr,
};

/// @brief data qualifier
/// @note all numerical types are
///       unsigned by default. Floats
///       override the @p qual_signed
///       flag, so do arrays
enum qual {
	qual_const = BIT (0),   ///< toggle: const, mut
	qual_signed = BIT (1),  ///< toggle: signed, unsigned (int-like only)
	qual_static = BIT (2),  ///< toggle: static, auto (heap/stack)
	qual_here = BIT (3),    ///< toggle: local, global (module-wise)
	qual_scope = BIT (4),   ///< toggle: local, global (object-wise)
	qual_array = BIT (5),   ///< toggle: array, object
	qual_decimal = BIT (6), ///< toggle: numerical, float/double
	qual_toobig = BIT (7),  ///< toggle: address overflow
};

#  define gqual(byte,qual) (byte) & (~qual) ///< macro: get @p qual from @p byte as a bitmap

typedef enum bits bits;
typedef enum qual qual;

#endif

#ifndef LOCK_EXPRFN
#  define LOCK_EXPRFN ///< lock: lock stack expression structure
struct expr {
	addr e1; /* heap/stack (l) or tab/register (e) */
	addr e2; /* heap/stack (l) or tab/register (e) */
	u32 op;
};

void expr_exec (void);
#endif
