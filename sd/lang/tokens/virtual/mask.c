/**
 * @file mask.c
 *
 * @brief virtual masked token definition
 *
 * This file contains virtual masked
 * token interfaces
 */

#include <sd/lang/tokens/virtual/mask.h>

// [T_ARR_BEGIN] = mask_compound (_BOOL_LT, _BIT_LS),
// [T_ARR_END] = mask_compound (_BOOL_GT, _BIT_RS),
// [T_MATH_PLUS] = mask_compound (_MATH_UPLUS, _MATH_INC),
// [T_MATH_MINUS] = mask_compound (_MATH_UMINUS, _MATH_DEC),
// [T_BOOL_NEG] = mask_compound (_WHILE, _WHILE_TRUE),
