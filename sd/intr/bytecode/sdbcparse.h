/**
 * This file contains type
 * definitionfor parsing
 * SD bytecode.
 */

#ifndef LOCK_BYTECODE_PARSER
#  define LOCK_BYTECODE_PARSER

#  define WORD_BYTES 2
#  define DWORD_BYTES 4
#  define QWORD_BYTES 8

#  include <sd/utils/types/shared.h>

typedef unsigned short int word;
typedef unsigned int dword;
typedef unsigned long int qword;

void parser_bstream (byte**);
void parse_bc (FILE*, byte*, const uint);

#endif
