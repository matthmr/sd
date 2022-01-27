/**
 * This file contains the logic
 * for the compiler to bytecode
 *
 * The parser for this format
 * is individually implemented
 * in other units.
 */

#ifndef LOCK_COMP
#  define LOCK_COMP

static uint word;

// -- `word` value (in bytes) -- //
#  define WORD 2
#  define DWORD 4
#  define QWORD 8

#  include <sd/utils/types/shared.h>

typedef unsigned short int word;
typedef unsigned int dword;
typedef unsigned long int qword;

void bcparser_stream (word*);

#endif
