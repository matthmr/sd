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

uint stroffset = 0;
ArgCallback CALLBACK[] = {
	{
		.am = NONE,
		.flag = NULL,
	}
};
static uint CNDX = 0;

static bool f_status = '\0';

/// @brief the flag that was DEFINITELY found
static const Flag *FLAG = NULL;
static const int flag_id = 0;

// `fbound_def`
#define nfound 0
#define npass 1
#define noob 2

static void callback_add (Flag *flag, FlagAmount am) {
	CALLBACK[CNDX].flag = (Flag*) flag;
	CALLBACK[CNDX].am = am;
	CNDX++;
}

/// @brief bounds the seek area via binary partitioning
/// @note `fbound_def` separates by data type, not by flag type
static bool fbound_def (char cc, const Flag *man, uint size,
                        bool manty, uint *start, uint *end) {

	int loffset = 0, roffset = 0;
	int _loffset = 0, _roffset = 0; // NOTE: these serve as {under,over}shot buffers

	uint block = size;
	char mc;

	// return if oob
	if (manty == FS_SINGLE) {
		if (cc < man[0]._.as_char || cc > man[size]._.as_char)
			return noob;
	}
	else if (cc < man[0]._.as_string[stroffset] || cc > man[size]._.as_string[stroffset]) {
		return noob;
	}

	while (block >= BLOCK_SIZE) {
		block = block >> 1;
		FlagData common = man[loffset]._;

		// get the manifest character
		mc = (manty == FS_SINGLE? common.as_char: common.as_string[stroffset]);

		// too big: increase `loffset`
		// [ x x x x y x ] => x x x [ x y x ]
		//   ~         ^   =>     (+3)~   ^
		if (cc > mc) {
			_loffset = loffset;
			loffset += block;
			*start = loffset;
			FlagData common = man[loffset]._;

			// adjust for overshot
			if (cc <
			    (manty == FS_SINGLE? common.as_char: common.as_string[stroffset])) {
				*end = *start;
				loffset = _loffset;
				*start = loffset;
			}

			continue;
		}

		// too small: decrease `roffset`
		// [ x y x x x x ] => [ x y x ] x x x
		//   ~         ^   =>   ~   ^(-3)
		else if (cc < mc) {
			_roffset = size - roffset;
			roffset += block;
			*end = size - roffset;
			FlagData common = man[loffset]._;

			// adjust for undershot
			if (cc >
			    (manty == FS_SINGLE? common.as_char: common.as_string[stroffset])) {
				*start = *end;
				roffset = _roffset;
				*end = _roffset;
			}

			continue;
		}

		// exact: set `start` to the current index
		else {
			*end = *start = loffset;
		}
	}

	finish: return (cc == mc)? nfound: npass;
}

/// @brief flag manifest finder
/// @note `ffind_def` separates by flag type, not by data type
static bool ffind_def (char c, char *arg, bool manty) {

	const SizeManifest *sflag;
	const Flag *flag;
	uint len;

	// set the iterator
	sflag = (manty == FS_SINGLE
		? (&flag_manifest.flag_single)
		: (&flag_manifest.flag_double));

	if (! (flag = sflag->this)) return NOTFOUND;
	else len = sflag->len;

	uint f_start = 0, f_end = sflag->len;

	bool estatus = fbound_def (c, flag, len, manty,
	                           &f_start, &f_end);

	if (estatus != npass) {
		goto notfound;
	}

	char _c;

	// seek(char)
	if (manty == FS_SINGLE) {
		for (uint i = f_start; i <= f_end; i++) { // TODO: `dir`-compliant seek
			if (flag[i]._.as_char == c) {
				callback_add ((Flag*) &flag[i], flag[i].common.comp? COMP: NONE);
				if (flag[i].common.comp)
					return ARGMORE;
				else
					return FOUND;
			}
		}
		return NOTFOUND;
	}

	// seek(string)
	else {
		// safe back-seek
		_c = flag[f_start]._.as_string[stroffset];
		while (f_start && flag[f_start]._.as_string[stroffset] == _c) {
			f_start--;
		}

		// safe foward-seek
		_c = flag[f_end]._.as_string[stroffset];
		len = sflag->len;
		while (f_end < len && flag[f_end]._.as_string[stroffset] == _c) {
			f_end++;
		}

		// take it from there
		for (uint i = f_start; i <= f_end; i++) {
			if (! strcmp (arg, (flag[i]._.as_string + stroffset))) {
				callback_add ((Flag*) &flag[i], flag[i].common.comp? COMP: NONE);
				stroffset++;
				return ARGMORE;
			}
			return FOUND;
		}
	}

	notfound: return NOTFOUND;
}

/// @brief main argument parser
/// @param proc caller name
/// @param arg caller provided argument
/// @param env caller provided `env`
Astatus parseargs (const char *prog, char *arg) {

	// TODO: make use of environment variables

	bool e_status = false;
	char c;
	f_status = 0;

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
			if (! arg[i]) goto dangle;
			else goto find;
		}

		else if (c != '-') goto dangle;

		else find: {
			e_status = ffind_def (c, arg + f_status, f_status);

			if (e_status == NOTFOUND)
				return ARG_ERR;
		}

		// set any promises if needed
		if (e_status != ARGMORE) {
			return promise (FLAG, arg);
		}
		else
			return ARG_MORE;
	}

	// if we have a dangling seek after arg iteration,
	// we use default flag handlers
	dangle: switch (f_status) {
	case FS_SINGLE:
		sdash (arg);
		break;
	case FS_DOUBLE:
		ddash (arg);
		break;
	default:
		defarg (arg);
		break;
	}

	// resolute promises before exiting
	//check ();

	return ARG_OK;
}
