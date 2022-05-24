/**
 * @file vt.c
 *
 * @brief virtual token definition
 *
 * This file contains virtual
 * tokens bundled up using
 * a defined interface
 */

#include <sd/lang/tokens/virtual/vt.h>

const _vT vtoken_manifest = {
	.mask = vtoken_manifest_mask,
	.comp = &vtoken_manifest_comp,
	.match = &vtoken_manifest_match,
};
