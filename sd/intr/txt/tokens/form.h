/**
 * @file form.h
 *
 * @brief token forms for plain-text SD source code
 *
 * This file contains definition of token
 * forms for plain-text SD source code
 * plus their plain-text interfaces
 */

#ifndef LOCK_LANG_TXT
#  define LOCK_LANG_TXT ///< lock: standard lock

#  include <sd/lang/tokens/interface/vkwi.h>
#  include <sd/lang/tokens/interface/vti.h>
#  include <sd/lang/tokens/gen/txtmaps.h>
#  include <sd/lang/tokens/virtual/vt.h>
#  include <sd/lang/tokens/groups.h>

#  include "utils/macros.h"

/// @brief plain-text keyword interface
struct _kw {
	const char *this; ///< plain-text representation
	const _Kw_common _; ///< @brief common interface
};

typedef struct _kw _Kw;

// `struct _t`
struct __t {
	const char this; ///< @brief plain-text representation
	const _T_common _; ///< @brief common interface
};

/// @brief plain-text token interface
struct _t {
	const struct __t token; ///< @brief proper text inteface
	const _vT vt; ///< @brief virtualisation interface
};

typedef struct _t _T;

#endif
