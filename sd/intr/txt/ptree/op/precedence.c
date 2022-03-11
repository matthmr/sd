/**
 * This file contains logic
 * for operator precedence
 */

#include <sd/intr/txt/ptree/op/precedence.h>

#include <sd/lang/expr/expr.h>

const Pre const opptab[] = {
	[OP_DRIVE] = {0, LR}, // '[', ']'

	[OP_MCHILD] = {1, LR},

	[OP_INC] = {2, LR},
	[OP_DEC] = {2, LR},
	[OP_MCAST] = {2, LR},
	[OP_MCALL] = {2, LR},
	[OP_MSUB] = {2, LR},

	[OP_LNOT] = {3, RL},
	[OP_BWNOT] = {3, RL},
	[OP_UPLUS] = {3, RL},
	[OP_UMINUS] = {3, RL},

	[OP_TIMES] = {4, LR},
	[OP_DIV] = {4, LR},
	[OP_MOD] = {4, LR},

	[OP_PLUS] = {5, LR},
	[OP_MINUS] = {5, LR},

	[OP_BWRS] = {5, LR},
	[OP_BWLS] = {5, LR},

	[OP_LLT] = {6, LR},
	[OP_LGT] = {6, LR},
	[OP_LLTEQ] = {6, LR},
	[OP_LGTEQ] = {6, LR},

	[OP_LEQ] = {7, LR},
	[OP_LNEQ] = {7, LR},

	[OP_BWAND] = {8, LR},

	[OP_BWXOR] = {9, LR},

	[OP_BWOR] = {10, LR},

	[OP_LAND] = {11, LR},

	[OP_LOR] = {12, LR},

	[OP_MASS] = {13, RL}, // assign

	[OP_MSEP] = {14, LR},
};
