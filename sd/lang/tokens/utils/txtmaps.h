/**
 * This file contains type definitions
 * for utils for tokens and keywords
 * of text type
 */

#ifndef LOCK_TXTMAPS_KW
#  define LOCK_TXTMAPS_KW

/// TODO: implement `double` data type
/* built-in data types */
#  define _INT 0x0001
#  define _CHAR 0x0002
#  define _FLOAT 0x0003
#  define _LONG 0x0004
#  define _SHORT 0x0005
#  define _BOOL 0x0006

/* qualifiers */
#  define _CONST 0x0007
#  define _STATIC 0x0008
#  define _UNSIGNED 0x0009
#  define _SCOPE 0x000a
#  define _HERE 0x000b

/* modifiers */
#  define _ENUM 0x000c
#  define _ARRAY 0x000d

/* object definition */
#  define _RM 0x000e
#  define _TYPE 0x000f
#  define _TAG 0x0010

/* scope control */
#  define _IMPORT 0x0011
#  define _IMPL 0x0012

/* built-in objects */
#  define _NIL 0x0013
#  define _THIS 0x0014
#  define _TRUE 0x0015
#  define _FALSE 0x0016

/* flow control */
#  define _ASYNC 0x0017
#  define _SYNC 0x0018
#  define _END 0x0019
#  define _JUMP 0x001a
#  define _RET 0x001b
#  define _GOTO 0x001c

/* literal syntax */
#  define _AS 0x001d

/* loops */
#  define _ITER 0x001e

#endif

#ifndef LOCK_TXTMAPS_T
#  define LOCK_TXTMAPS_T

/* reference delimiters */
#  define _OBJ_BEGIN 0x001f
#  define _OBJ_END 0x0020
#  define _MOD_BEGIN 0x0021
#  define _MOD_END 0x0022
#  define _PROC_BEGIN 0x0023
#  define _PROC_END 0x0024
#  define _SEP 0x0025

/* object reference */
#  define _CHILD 0x0026
#  define _DEREF 0x0027
#  define _CAST 0x0028

/* object definition */
#  define _BODY_BEGIN 0x0029
#  define _BODY_END 0x002a
#  define _ASSIGN 0x002b

/* expression control */
#  define _EXPR_END 0x002c
#  define _SELF 0x002d

/* misc syntax */
#  define _STRING 0x002e
#  define _COMMENT 0x002f
#  define _LABEL 0x0030

/* math operation */
#  define _MATH_PLUS 0x0031
#  define _MATH_TIMES 0x0032
#  define _MATH_MINUS 0x0033

/* bool comparison */
#  define _BOOL_EQ 0x0034

/* bool operation */
#  define _BOOL_NEG 0x0035

/* bitwise operation */
#  define _BIT_NEG 0x0036
#  define _BIT_AND 0x0037
#  define _BIT_OR 0x0038

/* piping */
#  define _PIPE 0x0039

#endif
