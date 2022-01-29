/**
 * This files contains the
 * implementation of utils
 * for parsing plain-text
 * SD source code
 */

#include <string.h>

#include <sd/intr/txt/utils/txtutils.h>
#include <sd/utils/types/shared.h>
#include <sd/lang/tokens/txt.h>
#include <sd/lang/core/obj.h>
#include <sd/utils/utils.h>

#define st_comp(x) dir? (x)<=t_end: (x)>=t_start
#define st_advance(x) dir? (x++): (x--)
#define st_get dir? t_start: t_end

/* `offset_i` starts on whatever
 * triggers it (alpha-numeric
 * or otherwise) and stops
 * right before a delimeter
 * or whitespace */
void offset_i (uint* i,
               char* line,
               const uint lnsize) {

	uint _i = *i;
	uint __i = _i;
	char c = line[_i];

	while (_i < lnsize) {

		if (WHITESPACE (c) || ! VALID (c))
			break;
		else
			_i++;

		c = line[_i];

	}

	if ((*i = _i) == __i) /// fall-through
		return;
	
	--*i; /// ... counting for incremental loop
}

bool nbound_def (char c,
                 uint size,
                 uint* t_start,
                 uint* t_end,
                 bool manifest_t) {

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
	} while (block >= 4); /// maximum block size of 4

	return (c == _c)? nfound: npass;

}

bool tfind_def (char c) {

	if (VALID (c)) /// handle fall-through test
		return not_found;

	uint size = token_manifest_len-1;

	uint t_start = 0;
	uint t_end = size;

	/// looks for out-of-bound chars
	if (
	    c < token_manifest[t_start].t ||
	    c > token_manifest[t_end].t
	) return not_found;


	uint e_status = nbound_def (c, size,
	                            &t_start, &t_end,
	                            TOKEN_MANIFEST);

	if (e_status == nfound)
		return ttoken;

	for (uint st = t_start; st <= t_end; st++) /// token seek
		if (c == token_manifest[st].t) {
			t = st;
			return ttoken;
		}

}

bool nfind_def (char c) {

	bool exit_status;
	bool rep_lock = false;

	static bool _call;

	static uint t_start, t_end;
	static uint offset;

	uint _t = 0;

	if (!_call) {

		H_LOCK (_call);
		H_RESET (t);

		if (UPPER_ALPHA (c)) { /// all default keywords are lowercase
			H_RESET (_call);
			return not_found;
		}

		if (LOWER_ALPHA (c)) {

			t_start = 0;
			t_end = keyword_manifest_len-1;

			/// looks for out-of-bound chars
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

			else c_opt_seek: { /// if (! rep_lock)

				bool dir = (c - *keyword_manifest[t_start].kw)
				        <= (*keyword_manifest[t_end].kw - c);

				uint st;

				for (st = st_get; st_comp (st); st_advance (st)) /// standard seek
					if (c == keyword_manifest[st].kw[offset]) {
						if (!t)
							_t = (t = st);
						else st_advance (_t);
					}
					else if (t) {
						if (!dir) { /// swap `t` and `_t` if backwards-searching
							uint _tcp = _t;
							_t = t;
							t = _tcp;
						}
						break;
					}

				if (!t) /// fall-through
					goto s_not_found;

				c_opt_backward_seek: { /// backward seek

				if (t > t_start)
					goto c_opt_forward_seek;

				for (uint st = (t_start-1); st >= 0; st--)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_forward_seek;
					else
						t--;
				}

				c_opt_forward_seek: { /// foward seek

				if (_t < t_end)
					goto c_opt_ret;

				for (uint st = (t_end+1); st < keyword_manifest_len; st++)
					if (c != keyword_manifest[st].kw[offset])
						goto c_opt_ret;
					else
						_t++;
				}

				c_opt_ret: if (_t - t)
					goto s_repeats;
				else
					goto s_found;

			}

		} else { /// resolute literal or token

			if (c == '\n') /// whitespace
				goto s_not_found;

			if (NUMBER (c)) {
				H_RESET (_call);
				return literal;
			}

			if (tfind_def (c) == ttoken) {
				H_RESET (_call);
				return ttoken;
			}

			goto s_not_found;

		}

	} else { /// resolute `repeats`

		if (! (LOWER_ALPHA (c))) /// up-to-diff fall-through
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
		/* bound `t` between the first matching and the last matching token */
		t_start = t;
		t_end = _t;

		offset++;
		return repeats;
	}

}

