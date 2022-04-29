/**
 * This file contains AST
 * element definition
 */

#ifndef LOCK_AST_ELEM
#  define LOCK_AST_ELEM

#  ifndef LOCK_TXTMAPS_BOUND
#    define LOCK_TXTMAPS_KW
#    define LOCK_TXTMAPS_T
#    include <sd/lang/tokens/gen/txtmaps.h>
#    undef LOCK_TXTMAPS_KW
#    undef LOCK_TXTMAPS_T
#  endif

#  define append(x) _TXTMAPS_BOUND+x

/* compound */
#  define _BIT_LS append (0x0001)
#  define _BIT_RS append (0x0002)
#  define _MATH_DIV append (0x0003)
#  define _MACRO_LIT append (0x0004)
#  define _MACRO_FN append (0x0005)
#  define _MACRO_SYN append (0x0006)
#  define _OBJ_PARENT append (0x0007)
#  define _BIT_XOR append (0x0008)
#  define _MATH_INC append (0x0009)
#  define _MATH_DEC append (0x000a)
#  define _WHILE_TRUE append (0x000b)
#  define _IF_TRUE append (0x000c)
#  define _BOOL_AND append (0x000d)
#  define _BOOL_OR append (0x000e)
#  define _MATH_MOD append (0x000f)

/* mask */
#  define _BOOL_LT append (0x0010)
#  define _BOOL_GT append (0x0011)
#  define _MATH_UPLUS append (0x0012)
#  define _MATH_UMINUS append (0x0013)
#  define _WHILE append (0x0014)

/* indirect compound */

/* <=, >=, != */
#  define _MATH_LTEQ append (0x0015)
#  define _MATH_GTEQ append (0x0016)
#  define _MATH_NEQ append (0x0017)

/* +:, -:, //:, *:, %%:, &&:, ||:, !:, &:, |:, ^^:, ~:, >>:, <<:, <=:, >=:, !=:, =: */
#  define _ASSIGN_PLUS append (0x0018)
#  define _ASSIGN_MINUS append (0x0019)
#  define _ASSIGN_DIV append (0x001a)
#  define _ASSIGN_TIMES append (0x001b)
#  define _ASSIGN_MOD append (0x001c)
#  define _ASSIGN_AND append (0x001d)
#  define _ASSIGN_OR append (0x001e)
#  define _ASSIGN_NOT append (0x001f)
#  define _ASSIGN_BWAND append (0x0020)
#  define _ASSIGN_BWOR append (0x0021)
#  define _ASSIGN_BWXOR append (0x0022)
#  define _ASSIGN_BWNOT append (0x0023)
#  define _ASSIGN_BWRS append (0x0024)
#  define _ASSIGN_BWLS append (0x0025)
#  define _ASSIGN_LTEQ append (0x0026)
#  define _ASSIGN_GTEQ append (0x0027)
#  define _ASSIGN_NEQ append (0x0028)
#  define _ASSIGN_EQ append (0x0029)

#endif
