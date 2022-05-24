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

#  include <sd/lang/tokens/interface/vti.h>
#  include <sd/lang/tokens/gen/txtmaps.h>
#  include <sd/lang/tokens/groups.h>

#  include <sd/utils/utils.h>

/// @brief plain-text keyword interface
typedef struct _kw {
	const char* kw;
	const Kwid id;
	const Kwty ty;
} _Kw;

/// @brief plain-text token interface
typedef struct _t {
	const char t;
	const Tid id;
	const Vty vty;
	const Tty ty;
} _T;

#endif
