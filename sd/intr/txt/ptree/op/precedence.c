/**
 * @file precedence.c
 *
 * @brief precedence logic
 *
 * This file contains logic
 * for operator precedence
 */

#include <sd/intr/txt/ptree/op/precedence.h>

#include <sd/lang/expr/expr.h>

#define _PREC OP_FLOWLOOP
#define prec_append(x) _PREC+x

/// @brief operator precendence and associativity table
///
/// High precedence (close to zero)
/// means it's resoluted first as in:
///        [LOW]       -->     +   (4)
///   [HIGH]    [HIGH] -->   *   * (3)
///
/// @p op comes from <sd/lang/expr/expr.h>
const Prec opptab[] = {

	[OP_MEMCHILD] = {1, LR},       // '/'

	[OP_UMATHINC] = {2, LR},       // '++'
	[OP_UMATHDEC] = {2, LR},       // '--'
	[OP_MEMCALL] = {2, LR},        // '()'
	[OP_MEMARR] = {2, LR},         // '<>'

	[OP_UMATHPLUS] = {3, RL},      // '+a'
	[OP_UMATHMINUS] = {3, RL},     // '-a'
	[OP_LOGNOT] = {3, RL},         // '!'
	[OP_BITWNOT] = {3, RL},        // '~'

	[OP_MATHTIMES] = {4, LR},      // '*'
	[OP_MATHDIV] = {4, LR},        // '//'
	[OP_MATHMOD] = {4, LR},        // '%%'

	[OP_MATHPLUS] = {5, LR},       // '+'
	[OP_MATHMINUS] = {5, LR},      // '-'

	[OP_BITWRS] = {5, LR},         // '>>'
	[OP_BITWLS] = {5, LR},         // '>>'

	[OP_LOGLT] = {6, LR},          // '<'
	[OP_LOGGT] = {6, LR},          // '>'
	[OP_LOGLTEQ] = {6, LR},        // '<='
	[OP_LOGGTEQ] = {6, LR},        // '>='

	[OP_LOGEQ] = {7, LR},          // '='
	[OP_LOGNEQ] = {7, LR},         // '!='

	[OP_BITWAND] = {8, LR},        // '&'

	[OP_BITWXOR] = {9, LR},        // '^^'

	[OP_BITWOR] = {10, LR},        // '|'

	[OP_LOGAND] = {11, LR},        // '&&'

	[OP_LOGOR] = {12, LR},         // '||'

	[OP_MEMCAST] = {13, LR},       // '.'

	[OP_MEMASS] = {14, RL},        // ':'
	[prec_append(1)] = {14, RL},   // '+:'
	[prec_append(2)] = {14, RL},   // '-:'
	[prec_append(3)] = {14, RL},   // '*:'
	[prec_append(4)] = {14, RL},   // '//:'
	[prec_append(5)] = {14, RL},   // '%%:'
	[prec_append(6)] = {14, RL},   // '<<:'
	[prec_append(7)] = {14, RL},   // '>>:'
	[prec_append(8)] = {14, RL},   // '&:'
	[prec_append(9)] = {14, RL},   // '^^:'
	[prec_append(10)] = {14, RL},  // '|:'
	[prec_append(11)] = {14, RL},  // '=:'
	[prec_append(12)] = {14, RL},  // '!=:'
	[prec_append(13)] = {14, RL},  // '<=:'
	[prec_append(14)] = {14, RL},  // '>=:'
	[prec_append(15)] = {14, RL},  // '||:'
	[prec_append(16)] = {14, RL},  // '&&:'

	[OP_FLOWEXPR] = {15, LR},      // '?'
	[OP_FLOWLOOP] = {15, LR},      // '!'

	[OP_MEMSEP] = {16, LR},        // ','
};
