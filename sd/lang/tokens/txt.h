/**
 * @file txt.h
 *
 * @brief plain-text manifests
 *
 * This file contains manifests for
 * keywords and tokens of the
 * standard written SD language
 */

#ifndef LOCK_TOKENS
#  define LOCK_TOKENS

#    include <sd/intr/txt/tokens/form.h>
#    include <sd/lang/tokens/groups.h>

#    include "utils/types/shared.h"

extern const _Kw keyword_manifest[];
extern const _T token_manifest[];

extern const uint keyword_manifest_len;
extern const uint token_manifest_len;

#  endif
