/**
 * @file sdc.h
 *
 * @brief SD compiler source code entry
 *
 * This file contains the logic
 * for the compiler to bytecode
 *
 * The parser for this format
 * is individually implemented
 * in other units.
 */

#ifndef LOCK_COMP
#  define LOCK_COMP

#  define HELP "\nMade by mH (https://github.com/matthmr)\n"\
               "\tsdc\t\t\t  => The standard SD compiler\n\n"\
               "Usage:\tsdc <files...> -o <file> => compile <files...> into <file>\n"\
               "\tsdread <file> \"<expr>\"\t  => <file> is SD source code\n"\
               "\tsdread -s <file> \"<expr>\" => <file> is SD bytecode code (compiled)\n\n"\
               "Info:\tsdc -h\t\t  => Displays this message and exits\n"\
               "\tsdc -v\t\t  => Displays the version and exits\n\n"\
               "Note:\tif <file> is `-`, then <file> is STDIN\n"\
               "     \t\"<expr>\" is optional but must be used in quotes\n\n"

#endif
