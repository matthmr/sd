/**
 * This file contains logic
 * for operator precedence
 */

#include <sd/intr/txt/ptree/op/precedence.h>

#include <sd/lang/expr/expr.h>

// * Lower precedence (close to zero)
// means it's resoluted first as in:
//        [HIGH]       -->     +   (6)
//   [LOW]      [LOW]  -->   *   * (5)
const Prec opptab[] = {
	[OP_CAST] = {1, LR},

	[OP_MEMCHILD] = {2, LR},
	[OP_MEMCALL] = {2, LR},

	[OP_UMATHINC] = {3, LR},
	[OP_UMATHDEC] = {3, LR},
	[OP_MEMCAST] = {3, LR},

	[OP_LOGNOT] = {4, RL},
	[OP_BITWNOT] = {4, RL},
	[OP_UMATHPLUS] = {4, RL},
	[OP_UMATHMINUS] = {4, RL},

	[OP_MATHTIMES] = {5, LR},
	[OP_MATHDIV] = {5, LR},
	[OP_MATHMOD] = {5, LR},

	[OP_MATHPLUS] = {6, LR},
	[OP_MATHMINUS] = {6, LR},

	[OP_BITWRS] = {6, LR},
	[OP_BITWLS] = {6, LR},

	[OP_LOGLT] = {7, LR},
	[OP_LOGGT] = {7, LR},
	[OP_LOGLTEQ] = {7, LR},
	[OP_LOGGTEQ] = {7, LR},

	[OP_LOGEQ] = {8, LR},
	[OP_LOGNEQ] = {8, LR},

	[OP_BITWAND] = {9, LR},

	[OP_BITWXOR] = {10, LR},

	[OP_BITWOR] = {11, LR},

	[OP_LOGAND] = {12, LR},

	[OP_LOGOR] = {13, LR},

	[OP_MEMASS] = {14, RL}, // assign

	[OP_MEMSEP] = {15, LR}, // separator

	[OP_FLOWEXPR] = {16, LR},
	[OP_FLOWLOOP] = {16, LR},
};
