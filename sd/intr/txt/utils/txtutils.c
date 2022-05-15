/**
 * @file txtutils.c
 *
 * @brief Plain-text source code utilities
 *
 * This file contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#include <string.h>

#include <sd/intr/txt/utils/txtutils.h>

#include <sd/utils/types/shared.h>
#include <sd/utils/err/verr.h>
#include <sd/utils/utils.h>

#include <sd/lang/hooks/txt/txthooks.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/core/obj.h>

#define st_comp(x) dir? (x)<=t_end: (x)>=t_start ///< compares the manifest index according with `dir`
#define st_advance(x) dir? (x++): (x--) ///< advances the manifest index according to `dir`
#define st_get dir? t_start: t_end ///< gets a limit acording to `dir`

/// @brief advances the buffer index, stopping on an invalid character
///
/// the break is decided by
/// @code
/// 	if (WHITESPACE (c) || ! (VALID (c) || NUMBER (c)))
/// @endcode
/// a `uword` cannot start with a number because the number will trigger
/// a literal hook, therefore the `NUMBER` macro is safe in that
/// position
///
/// @param i the buffer index pointer
/// @param line the buffer
/// @param lnsize the buffer size
void offset_i (uint* i, char* line, const uint lnsize) {

	uint _i = *i;
	uint __i = _i;
	char c = line[_i];

	while (_i < lnsize) {

		// offsets by the first index of the next non-valid uword character
		if (WHITESPACE (c) || ! (VALID (c) || NUMBER (c)))
			break;
		else
			_i++;

		c = line[_i];

	}

	if ((*i = _i) == __i) // fall-through
		return;
	
	--*i; // ... counting for incremental loop
}

/// @brief checks if a character is in the character set of a number base
/// @param c the character to test against
/// @param base the number base
/// @return 1 or 0 depeding if `c` is a number base `base`
bool number_base (char c, uint base) {

	switch (base) {
	case 10:
		return NUMBER (c);
		break;
	case 16:
		return NUMBER_UHEX (c) || NUMBER_LHEX (c);
		break;
	case 8:
		return NUMBER_OCT (c);
		break;
	case 2:
		return NUMBER_BIN (c);
		break;
	}

	return NUMBER (c);

}

/// @brief advances the buffer index as per number notation
///
/// the break is decided by the condition
/// @code
/// number_base (c, base) || (c == '.' && !dot)
/// @endcode
/// being false. if @p base was not explicitly defined it defaults to `10`.
/// the loop has two parts:
///   - if `first` is set it gets info if it's a hexadecimal or octal
///   - if `first` is not set if follows with its calls of `number_base`
///
/// @param i the buffer index pointer
/// @param data the buffer
/// @see number_base
void number_offset (uint* i, char* data) {
	uint offset = *i;

	bool first = 1;
	bool dot = 0;
	bool zero_prefix = 0;

	char c = data[offset];

	uint base = 10;

	while (number_base (c, base) || (c == '.' && !dot)) {

		if (first) {

			if (c == '0')
				H_LOCK (zero_prefix);

			H_RESET (first);

			if (!zero_prefix)
				goto _next;
			else {
				offset++;
				c = data[offset];
			}

			if (c == 0x00) // trailing 0
				NO_INFO_ERR (0x05, "");

			if (NUMBER_OCT (c)) {
				base = 8;
				goto _next;
			}

			switch (c) {
			case 'x': base = 16; break;
			case 'b': base = 2; break;
			default: NO_INFO_ERR (0x04, ""); break;
			}

			goto _next;
		}

		else if (c == '.' && (!dot && base == 10)) {
			H_LOCK (dot);
		}
		else if (c == '.')
			NO_INFO_ERR (0x04, "");

		_next: {
			offset++;
			c = data[offset];
		}

	}

	if ((c == '.' && dot) || (c == '.' && base != 10)) // fall-through
		NO_INFO_ERR (0x04, "");

	gs_ctxt.base = (u8) base;
	*i = (offset - 1);
}

/// @brief bounds the seek area via binary partitioning
/// @param c the character to bound against
/// @param size the size of the manifest
/// @param t_start the lower bound pointer
/// @param t_end the upper bound pointer
/// @param manifest_t the manifest type
/// @return `nbound_def` exit status
bool nbound_def (char c, uint size, uint* t_start, uint* t_end, bool manifest_t) {

	uint l_offset = 0;
	uint block = 0;

	char _c;

	do {
		block = size/2;

		switch (manifest_t) {
		case KEYWORD_MANIFEST:
			_c = *keyword_manifest[block + l_offset].kw;
			break;
		case TOKEN_MANIFEST:
			_c = token_manifest[block + l_offset].t;
			break;
		}

		if (c > _c) {
			size = block;
			l_offset = (*t_start += block);
			continue;
		}

		else if (c < _c) {
			size = block;
			*t_end = (block + l_offset);
			continue;
		}

		else if (c == _c) {
			if (manifest_t == TOKEN_MANIFEST)
				t = block+l_offset;
			*t_start = block;
			break;
		}
	} while (block >= BLOCK_SIZE);

	return (c == _c)? nfound: npass;

}

/// @brief searches for a token defined in the manifest
/// @param c the character to search against
/// @return `nfind_def`'s exit status (shortened)
bool tfind_def (char c) {

	if (VALID (c)) // handle fall-through test
		return not_found;

	uint size = token_manifest_len-1;

	uint t_start = 0;
	uint t_end = size;

	// looks for out-of-bound chars
	if (
	    c < token_manifest[t_start].t ||
	    c > token_manifest[t_end].t
	) return not_found;


	uint e_status = nbound_def (c, size,
	                            &t_start, &t_end,
	                            TOKEN_MANIFEST);

	if (e_status == nfound)
		return ttoken;

	for (uint st = t_start; st <= t_end; st++) // token seek
		if (c == token_manifest[st].t) {
			t = st;
			return ttoken;
		}

	return not_found;

}

/// @brief searches for a keyword defined in the manifest
/// @param c the character to search against
///
/// `nfind_def` keeps a static lock @code static bool _call @endcode
/// because it serves as the entry point for manifest searching and
/// can therefore return a repeat status to disambiguate results
///
/// @return `nfind_def`'s exit status (full)
bool nfind_def (char c) {

	bool exit_status;
	bool rep_lock = false;

	static bool _call;

	static uint t_start, t_end;
	static uint offset;

	uint _t = 0;

	if (!_call) { // normal call

		H_LOCK (_call);
		H_RESET (t);

		if (UPPER_ALPHA (c)) { // all default keywords are lowercase
			H_RESET (_call);
			return not_found;
		}

		if (LOWER_ALPHA (c)) {

			t_start = 0;
			t_end = keyword_manifest_len-1;

			// looks for out-of-bound chars
			if (
			    c < *(keyword_manifest[t_start].kw) ||
			    c > *(keyword_manifest[t_end].kw)
			) goto s_not_found;

			if (! rep_lock) {
				uint t_size = keyword_manifest_len-1;
				uint l_offset = 0;

				(void) nbound_def (c, t_size,
				                   &t_start, &t_end,
				                   KEYWORD_MANIFEST);

				H_LOCK (rep_lock);
				goto c_opt_seek;
			}
			else c_opt_seek: { // if (! rep_lock)

				bool dir = (c - *keyword_manifest[t_start].kw)
				        <= (*keyword_manifest[t_end].kw - c);

				uint st;

				for (st = st_get; st_comp (st); st_advance (st)) // standard seek
					if (c == keyword_manifest[st].kw[offset]) {
						if (!t)
							_t = (t = st);
						else st_advance (_t);
					}
					else if (t) {
						if (!dir) { // swap `t` and `_t` if backwards-searching
							uint _tcp = _t;
							_t = t;
							t = _tcp;
						}
						break;
					}

				if (!t) // fall-through
					goto s_not_found;

				c_opt_backward_seek: { // backward seek
				if (t > t_start)
					goto c_opt_forward_seek;

				for (uint st = (t_start-1); st >= 0; st--)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_forward_seek;
					else
						t--;
				}

				c_opt_forward_seek: { // forward seek
				if (_t < t_end)
					goto c_opt_ret;

				for (uint st = (t_end+1); st < keyword_manifest_len; st++)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_ret;
					else
						_t++;
				}

				c_opt_ret:
				if (_t - t)
					goto s_repeats;
				else
					goto s_found;

			}

		}
		else { // resolute literal or token
			if (c == '\n') // whitespace
				goto s_not_found;

			if (NUMBER (c)) {
				H_RESET (_call);
				return number;
			}

			if (tfind_def (c) == ttoken) {
				H_RESET (_call);
				return ttoken;
			}

			goto s_not_found;
		}

	}

	else { // if (_call): resolute `repeats`
		if (! LOWER_ALPHA (c)) // up-to-diff fall-through
			goto s_not_found;

		_t = 0;
		t = t_start;

		bool lock = 0;

		for (uint st = t_start; st <= t_end; st++) {
			if (c != keyword_manifest[st].kw[offset])
				continue;
			else
				if (!lock) {
					H_LOCK (lock);
					_t = t = st;
				}
				else
					_t = st;
		}

		if (!_t)
			goto s_not_found;
		else if (_t - t)
			goto s_repeats;
		else
			goto s_found;
	}

	s_not_found: {
		H_RESET (_call);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		return not_found;
	}

	s_found: {
		H_RESET (_call);
		H_RESET (offset);

		H_RESET (t_start);
		H_RESET (t_end);

		return found;
	}

	s_repeats: {
		// bound `t` between the first matching and the last matching token
		t_start = t;
		t_end = _t;

		offset++;
		return repeats;
	}

}
