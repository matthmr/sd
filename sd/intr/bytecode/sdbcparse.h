/**
 * This file contains type
 * definition for parsing
 * SD bytecode.
 */

#ifndef LOCK_BYTECODE_PARSER
#  define LOCK_BYTECODE_PARSER

#  include <sd/utils/types/shared.h>

/* this is meant for an x86_64 cpu */
#  define WORD_BYTES 2
#  define DWORD_BYTES 4
#  define QWORD_BYTES 8

typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long qword;

void parser_bstream (byte**);
void parse_bc (FILE*, byte*, const uint);

#endif
