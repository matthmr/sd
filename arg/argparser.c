/*
 * @file argparser.c
 *
 * @brief common argument parser implementation
 *
 * This file contains a common argparsing
 * interface for programs that receive
 * CLI arguments
 */

#include <string.h>
#include <stdio.h>

#include "argparser.h"

#define FS_SINGLE '\1'
#define FS_DOUBLE '\2'

static bool f_status = '\0';

#define CHAR '\1'
#define STRING '\2'

typedef struct iter {
	const bool as;
	const SizeManifest *man;
} Iter;

static const Iter fs_single[] = {
	{ CHAR, (SizeManifest*)&flag_manifest.flag_single },
	{ STRING, (SizeManifest*)&flag_manifest.flag_singlelong },
	{ CHAR, (SizeManifest*)&flag_manifest.flag_comp },
};

static const Iter fs_double[] = {
	{ STRING, (SizeManifest*)&flag_manifest.flag_double },
};

static const Flag *FLAG = NULL;

// `fbound_def`
#  define nfound 0
#  define npass 1
#  define noob 2

/// @brief bounds the seek area via binary partitioning
/// @note `fbound_def` separates by data type, not by flag type
static bool fbound_def (char c, const Flag *man, uint size,
                        bool manty, uint *start, uint *end) {

	uint l_offset = 0, block = 0;
	char _c;

	// return if oob
	if (manty == CHAR) {
		if (c < man[0]._.as_char || c > man[size]._.as_char)
			return noob;
	}
	else if (c < *man[0]._.as_string || c > *man[size]._.as_string) {
		return noob;
	}

	*start = 0;
	*end = size;

	do {
		block = size >> 1;

		if (manty == CHAR) {
			_c = man[l_offset + block]._.as_char;
		}
		else {
			_c = *man[l_offset + block]._.as_string;
		}

		// too big: set `size` to `block`, set `l_offset` to `block`
		// [ x x x x ] => x x [ x x ]
		if (c > _c) {
			size = block;
			l_offset = (*start += block);
			continue;
		}

		// too small: set `size` to `block`
		// [ x x x x ] => [ x x ] x x
		else if (c < _c) {
			size = block;
			*end = (block + l_offset);
			continue;
		}

		// exact: set `start` to the current index
		else {
			*start = l_offset + block;
			*end = *start;
		}
	} while (block >= BLOCK_SIZE);

	finish: return (c == _c)? nfound: npass;
}

/// @brief flag manifest finder
/// @note `ffind_def` separates by flag type, not by data type
static bool ffind_def (char c, char *arg, bool manty) {

	const SizeManifest *sflag;
	const Flag *flag;

	bool inverse;
	uint f_start = 0, f_end = 0;

	Iter *iter;
	uint indx;

	// quick-handle single flag;
	// `FOUND` just means
	// "don't continue searching"
	if (!c) return FOUND;

	// set the iterator
	if (manty == FS_SINGLE) {
		iter = (Iter*)fs_single;
		indx = BYTES (fs_single);
	}
	else {
		iter = (Iter*)fs_double;
		indx = BYTES (fs_double);
	}

	// this loop is validated by the fact that single characters
	// may have actions defined in the single character
	// manifest, even if that character serves as a compound base
	for (uint i = 0; i < indx; i++) {
		sflag = iter[i].man;
		flag = sflag->this;

		if (flag) {
			bool estatus = fbound_def (c, flag, sflag->len, iter[i].as,
			                           &f_start, &f_end);

			// handle oob
			if (estatus == noob || estatus == nfound) {
				goto notfound;
			}

			char _c;
			uint len;

			// seek if needed
			if (iter[i].as == CHAR) {

				// this is a special case, if we so much as find anything
				// before or after, it means our manifest was most likely
				// a `flag_comp` manifest
				if ((f_start > 0 && flag[f_start-1]._.as_char == c) ||
				    (f_end < (sflag->len-1) && flag[f_end+1]._.as_char == c)) {
					// TODO: no need to implement this as we don't make
					// use of this yet
				}
				else for (uint i = f_start; i <= f_end; i++)
					if (flag[i]._.as_char == c) {
						FLAG = &flag[i];
						return FOUND;
					}

			}
			else {

				// safe back-seek
				_c = *flag[f_start]._.as_string;
				while (f_start && *flag[f_start]._.as_string == _c) {
					f_start--;
				}

				// safe foward-seek
				_c = *flag[f_end]._.as_string;
				len = sflag->len;
				while (f_end < len && *flag[f_end]._.as_string == _c) {
					f_end++;
				}

				// take it from there
				for (uint i = f_start; i <= f_end; i++) {

					if (! strcmp (arg, flag[i]._.as_string)) {
						FLAG = &flag[i];
						return FOUND;
					}

				}
			}
		}
	}

	notfound: return NOTFOUND;
}

/// @brief main argument parser
/// @param proc caller name
/// @param arg caller provided argument
/// @param env caller provided `env`
Astatus parseargs (const char *prog, char *arg, char **env) {

	// TODO: make use of environment variables through `env`

	bool e_status = false;
	char c;

	// main loop
	for (uint i = 0; (c = arg[i]); i++) {

		// seek leading flag prefix
		if (i == 0 && c == '-') {
			f_status = FS_SINGLE;

			// found the first, looking for the second
			if (i++, c = arg[i], c == '-') {
				f_status = FS_DOUBLE;

				// found the second, looking for the third
				if (i++, c = arg[i], c == '-') {
					// found the third: ignore all of the above, go to flag check
					f_status = '\0';
					break;
				}

			}

			// fall-through - go to flag check
			if (! arg[i])
				break;
			else goto get_estatus;

		}

		else {
			get_estatus: e_status = ffind_def (c, arg + f_status, f_status);

			if (e_status == NOTFOUND)
				return ARG_ERR;
		}

		// set any promises if needed
		Astatus ccheck = promise ();

		if (ccheck == ARG_ERR || ccheck == ARG_INFO)
			return ccheck;
		else
			return ARG_OK;
	}

	// if we have a dangling seek after arg iteration,
	// we use default flag handlers
	switch (f_status) {
	case FS_SINGLE:
		sdash (arg, env);
		break;
	case FS_DOUBLE:
		ddash (arg, env);
		break;
	default:
		defarg (arg, env);
		break;
	}

	f_status = 0;

	ok: return ARG_OK;
}
