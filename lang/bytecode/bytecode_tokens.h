/**
 * This file contains all the bytecode
 * for the tokens, object construction
 * and control flow for the SD language
 */

#ifndef LOCK_BYTECODE_TOKENS
#  define LOCK_BYTECODE_TOKENS

enum delimiter {
	OBJ_BEGIN,
	OBJ_END,

	DATA_BEGIN,
	DATA_END
};

typedef unsigned char Bytecode;

static const Bytecode Delimiter[] = {
	[OBJ_BEGIN] = 0b0,
	[OBJ_END] = 0b1,

	[DATA_BEGIN] = 0b0,
	[DATA_END] = 0b1
};

static const Bytecode Keyword_bytecode_manifest[] = {
	
};

#endif
