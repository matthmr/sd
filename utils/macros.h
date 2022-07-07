/**
 * @file macros.h
 *
 * @brief generic standard utils; context agnostic
 *
 * This file contains basic / useful
 * functionality that are used throughout
 * the resolution of symbols
 */

#ifndef  LOCK_MACROS
#  define LOCK_MACROS ///< lock: lock macros utils

// numeric utils
#  define NUMBER(x) ((x) >= '0' && (x) <= '9')
#  define NUMBER_UHEX(x) ((x) >= 'A' && (x) <= 'F')
#  define NUMBER_LHEX(x) ((x) >= 'a' && (x) <= 'f')
#  define NUMBER_BIN(x) ((x) == '0' || (x) == '1')
#  define NUMBER_OCT(x) ((x) >= '0' && (x) <= '7')

// alphabetic utils
#  define LOWER_ALPHA(x) ((x) >= 'a' && (x) <= 'z')
#  define UPPER_ALPHA(x) ((x) >= 'A' && (x) <= 'Z')
#  define WHITESPACE(x) (\
	(x) == 0x20 || /* space */ \
	(x) == 0x0a || /* line feed */ \
	(x) == 0x0d || /* carriage return (dos) */ \
	(x) == 0x09)   /* horizontal tab */
#  define ATOI(x) ((!NUMBER(x))? -1: (x) - 48)

// language-specific utils
/// @note this macro does not consider what the index of the character
/// in the identifier's name is, that rule is implemented directly
/// in parsing
#  define VALID(x) (\
	LOWER_ALPHA(x) ||\
	UPPER_ALPHA(x) ||\
	NUMBER(x) ||\
	(x) == '_')

// general purpose utils
#  define POW2(x) (1u << x)
#  define BIT(x) POW2(x)
#  define BYTES(x) sizeof (x) / sizeof (*x)
#  define GET(x,y) ((x) & (y))
#  define ADD(x,y) ((x) | (y))

// string utils
#  define __nl__ "\n"

#endif
